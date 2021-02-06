#include <fir.hpp>

int main()
{
    using namespace fir;

    auto result = console::readln()
        .trim()
        .parse_int();

    if (result)
    {
        console::writeln("%i", *result);
    }
    
    return 0;
}
