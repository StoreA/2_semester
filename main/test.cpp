#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "../sql_utils/sql_utils.h" // Adjust path

#define CATCH_CONFIG_MAIN
#include "../include/catch.hpp"

// Dummy function for testing
int add(int a, int b) {
    return a + b;
}

// Updated insert_product wrapper for testing
int insert_product(const char *product_name, float price, int quantity) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc = sqlite3_open("products.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    rc = insert_product(db, product_name, price, quantity, &zErrMsg); // Call the modular function
    sqlite3_close(db);
    return rc;
}

TEST_CASE("Addition works correctly", "[math]") {
    REQUIRE(add(2, 3) == 5); // Fixed: 2+3=5, not 4
    REQUIRE(add(-1, 1) == 0);
    REQUIRE(add(10, 5) == 15);
}

TEST_CASE("Adding products to the database", "[insert_sql]") {
    REQUIRE(insert_product("TestProduct", 29.99, 10) == 10);
    // Optionally, add more assertions to verify DB state
}