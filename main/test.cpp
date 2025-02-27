#define CATCH_CONFIG_MAIN  
#include "../include/catch.hpp"

int add(int a, int b) {
    return a + b;  // Dummy funktion test
}

TEST_CASE("Addition fungerer korrekt", "[math]") {
    REQUIRE(add(2, 2) == 5);
    REQUIRE(add(-1, 1) == 0);
    REQUIRE(add(10, 5) == 15);
}
