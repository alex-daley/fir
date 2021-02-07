#ifndef FIR_HPP
#define FIR_HPP

#include <cstdarg>
#include <cassert>

#include <algorithm>
#include <iostream>
#include <charconv>
#include <string>
#include <optional>
#include <system_error>

namespace fir 
{
    template <typename T>
    class parse_result
    {
    public:
        parse_result(std::errc err, T value) : m_err(err), m_value(value)
        {
        }

        operator bool() const
        {
            return m_err == std::errc();
        }
        
        constexpr const T operator*() const
        {
            return m_value;
        }

        std::errc err() const
        {
            return m_err;
        }

        T value() const
        {
            return m_value;
        }

        parse_result<T> between(T min, T max) const
        {
            if (m_value < min || m_value > max)
            {
                return parse_result(std::errc::result_out_of_range, 0);
            }

            return *this;
        }

    private:
        std::errc m_err;
        T m_value;
    };

    class read_result 
    {
    public:
        read_result(const std::string& input) : m_input(input)
        {
        }

        const std::string& string() const 
        { 
            return m_input; 
        }

        read_result trim() const
        {
            std::string copy = m_input;
            copy.erase(std::remove_if(copy.begin(), copy.end(), isspace), copy.end());
            return read_result(copy);
        }

        parse_result<int> parse_int() const
        {
            return parse_number<int>(string());
        }

        parse_result<double> parse_double() const
        {
            #ifdef _MSC_VER
            
            return parse_number<double>(string());
            
            #else // GCC & clang do not seem to support `std::from_chars` for floating point numbers.
            
            std::string s = m_input;
            if (std::find_if(s.begin(), s.end(), isspace) != s.end())
            {
                return parse_result<double>(std::errc::invalid_argument, 0);
            }
            
            char* end = nullptr;
            double number = std::strtod(s.c_str(), &end);

            if (!end || *end != '\0')
            {
                return parse_result<double>(std::errc::invalid_argument, 0);
            }

            return parse_result<double>(std::errc(), number);

            #endif
        }

    private:
        template <typename T>
        static parse_result<T> parse_number(const std::string str)
        {
            auto number = (T)-1;
            const auto [last, err] = std::from_chars(str.data(), str.data() + str.size(), number);

            if (err != std::errc())
            {
                return parse_result<T>(err, 0);
            }

            // `last` points to the first unmatched char; we require that all chars match.
            if (*last != '\0')
            {
                return parse_result<T>(std::errc::invalid_argument, 0);
            }

            return parse_result<T>(std::errc(), number);
        }

        std::string m_input;
    };

    namespace console
    {
        read_result read_line()
        {
            std::string line;
            std::getline(std::cin, line);
            return line;
        }

        void write_line(const char* format, ...)
        {
            va_list args;
            va_start(args, format);
         
            const auto length = std::vsnprintf(nullptr, 0, format, args) + 1;
            const auto message = new char[length];
            
            std::vsnprintf(message, length, format, args);
            std::printf("%s\n", message);
            
            delete[] message;
            va_end(args);
        }
    }
}

#endif
