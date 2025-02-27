#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#define CATCH_CONFIG_MAIN  
#include "../include/catch.hpp"

// Functions for the cases that needs to be run

// Adding ints
int add(int a, int b) {
    return a + b;  // Dummy funktion test
}

int insert_product ( const char* sql_statement) {
    int quantity;
    return quantity;
}

TEST_CASE("Addition fungerer korrekt", "[math]") {
    REQUIRE(add(2, 3) == 4);
    REQUIRE(add(-1, 1) == 0);
    REQUIRE(add(10, 5) == 15);
}

TEST_CASE("Adding products with the SQL statement", "[insert_sql]") {
    REQUIRE(insert_product("INSERT INTO PRODUCTS VALUES (PRODUCT_QUANTITY, 10)") == 10);

}