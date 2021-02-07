#include <fir.hpp>

int main()
{
    using namespace fir;

    auto result = console::readln()
        .trim()
        .parse_int().between(0, 3);

    if (result)
    {
        console::writeln("%i", *result);
    }
    
    return 0;
}
