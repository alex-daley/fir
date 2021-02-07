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
    REQUIRE(fir::console::read_line().string() == expected);

    // Restore default `std::cin`.
    std::cin.rdbuf(initial_cin);
}

TEST_CASE("readln_result::trim trims whitespace", "[readln_result]") 
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

TEST_CASE("readln_result::parse_int parses integer", "[readln_result]")
{
    SECTION("parses positive integers")
    {
        constexpr auto expected = 42;
        const auto result = fir::readln_result("42");
        REQUIRE(result.parse_int() == true);
        REQUIRE(result.parse_int().value() == expected);
    }
    SECTION("parses negative integers")
    {
        constexpr auto expected = -42;
        const auto result = fir::readln_result("-42");
        REQUIRE(result.parse_int() == true);
        REQUIRE(result.parse_int().value() == expected);
    }
    SECTION("does not parse strings with whitespace")
    {
        const auto result1 = fir::readln_result(" 42");
        REQUIRE(result1.parse_int() == false);

        const auto result2 = fir::readln_result("42 ");
        REQUIRE(result2.parse_int() == false);

        const auto result3 = fir::readln_result("4 2");
        REQUIRE(result3.parse_int() == false);
    }
    SECTION("does not parse strings with non-numeric characters")
    {
        const auto result = fir::readln_result("fourty42two");
        REQUIRE(result.parse_int() == false);
    }
}

TEST_CASE("readln_result::parse_double parses double", "[readln_result]")
{
    SECTION("parses positive double")
    {
        constexpr auto expected = 3.14159265359;
        const auto result = fir::readln_result("3.14159265359");
        REQUIRE(result.parse_double() == true);
        REQUIRE(result.parse_double().value() == expected);
    }
    SECTION("parses negative double")
    {
        constexpr auto expected = -3.14159265359;
        const auto result = fir::readln_result("-3.14159265359");
        REQUIRE(result.parse_double() == true);
        REQUIRE(result.parse_double().value() == expected);
    }
    SECTION("does not parse strings with whitespace")
    {
        const auto result1 = fir::readln_result("  3.14159265359");
        REQUIRE(result1.parse_double() == false);

        const auto result2 = fir::readln_result("3.14159265359 ");
        REQUIRE(result2.parse_double() == false);

        const auto result3 = fir::readln_result("3. 14159265359");
        REQUIRE(result3.parse_double() == false);
    }
    SECTION("does not parse strings with non-numeric characters")
    {
        const auto result = fir::readln_result("pipipipi3.14159265359");
        REQUIRE(result.parse_double() == false);
    }
}

TEST_CASE("parse_result::between return indicates error when values are out of range")
{
    SECTION("errc::result_out_of_range when value is less than lower bound")
    {
        const auto result = fir::parse_result(std::errc(), 42).between(43, 100);
        REQUIRE(result.err() == std::errc::result_out_of_range);
    }
    SECTION("errc::result_out_of_range when value is greater than upper bound")
    {
        const auto result = fir::parse_result(std::errc(), 42).between(0, 41);
        REQUIRE(result.err() == std::errc::result_out_of_range);
    }
}

TEST_CASE("parse_result::between returns success result when integer is in range")
{
    SECTION("no error and same value when integer is inside range")
    {
        constexpr auto expected = 42;
        const auto result = fir::parse_result(std::errc(), expected)
            .between(0, 100);

        REQUIRE(result);
        REQUIRE(*result == expected);
    }
    SECTION("no error and same value when integer is at bounds")
    {
        constexpr auto expected = 42;
        const auto result = fir::parse_result(std::errc(), expected)
            .between(expected, expected);

        REQUIRE(result);
        REQUIRE(*result == 42);
    }
}


TEST_CASE("parse_result::between returns success result when double is in range")
{
    SECTION("no error and same value when double is inside range")
    {
        constexpr auto expected = 3.14159265359;
        const auto result = fir::parse_result(std::errc(), expected)
            .between(expected, 100);

        REQUIRE(result);
        REQUIRE(*result == expected);
    }
    SECTION("no error and same value when double is at bounds")
    {
        constexpr auto expected = 3.14159265359;
        const auto result = fir::parse_result(std::errc(), expected)
            .between(expected, expected);

        REQUIRE(result);
        REQUIRE(*result == expected);
    }
}
