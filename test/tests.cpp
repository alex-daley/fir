#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <fir.hpp>

TEST_CASE("console::readln reads line of text from std::cin", "[console]")
{
    // Redirect `std::cin` to `in` controlled by us.
    const auto initial_cin = std::cin.rdbuf();
    std::stringstream in;
    std::cin.rdbuf(in.rdbuf());

    // Testing...
    constexpr auto expected = "Hello world!"; 
    in << expected;
    REQUIRE(fir::console::readln().string() == expected);

    // Restore default `std::cin`.
    std::cin.rdbuf(initial_cin);
}

TEST_CASE("readln::trim trims whitespace", "[readln]") 
{
    constexpr auto expected = "Hello,niceweathertoday!";

    SECTION("trims leading whitespace")
    {
        const auto result = fir::readln_result("  Hello,niceweathertoday!");
        REQUIRE(result.trim().string() == expected);
    }
    SECTION("trims trailing whitespace")
    {
        const auto result = fir::readln_result("Hello,niceweathertoday!  ");
        REQUIRE(result.trim().string() == expected);
    }
    SECTION("trims intermediate whitespace")
    {
        const auto result = fir::readln_result("Hello, nice weather today!");
        REQUIRE(result.trim().string() == expected);
    }
}
