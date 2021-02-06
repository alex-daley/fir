#ifndef FIR_HPP
#define FIR_HPP

#include <string>
#include <iostream>
#include <charconv>
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

        std::errc err() const
        {
            return m_err;
        }

        T value() const
        {
            return m_value;
        }

    private:
        std::errc m_err;
        T m_value;
    };

    class readln_result 
    {
    public:
        readln_result(const std::string& input) : m_input(input)
        {
        }

        const std::string& string() const 
        { 
            return m_input; 
        }

        readln_result trim() const
        {
            std::string copy = m_input;
            copy.erase(std::remove_if(copy.begin(), copy.end(), isspace), copy.end());
            return readln_result(copy);
        }

        parse_result<int> parse_int() const
        {
            return parse_number<int>(string());
        }

        parse_result<double> parse_double() const
        {
            return parse_number<double>(string());
        }

    private:
        template <typename T>
        static parse_result<T> parse_number(const std::string str)
        {
            T number = (T)-1;
            auto [last, err] = std::from_chars(str.data(), str.data() + str.size(), number);

            if (err != std::errc()) 
                return parse_result<T>(err, 0);

            // `last` points to the first unmatched char; we require that all chars match.
            if (*last != '\0') 
                return parse_result<T>(std::errc::invalid_argument, 0);

            return parse_result<T>(std::errc(), number);
        }

        std::string m_input;
    };

    namespace console
    {
        readln_result readln()
        {
            std::string line;
            std::getline(std::cin, line);
            return line;
        }
    }
}

#endif
