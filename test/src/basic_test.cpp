#include <catch2/catch_test_macros.hpp>

auto multiply(int a, int b) { return a * b; }

TEST_CASE("Multiply using global function") {
	auto a =multiply(2,3);
    REQUIRE(a == 6);
}
