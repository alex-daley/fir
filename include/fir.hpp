#ifndef FIR_HPP
#define FIR_HPP

#include <string>
#include <iostream>

namespace fir 
{
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

    private:
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
