// #define CATCH_CONFIG_MAIN
// #include "../include/catch.hpp"
// #include <sqlite3.h>
// #include "../sql_utils/sql_utils.h" // Include the header with insert_product
// #include <stdio.h>

// // Function to open the database
// bool open_database() {
//     sqlite3 *db;
//     int rc = sqlite3_open("../products.db", &db);
//     if (rc) {
//         fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
//         sqlite3_close(db);
//         return false;
//     }
//     sqlite3_close(db);
//     return true;
// }



// TEST_CASE("Opening the products database", "[database]") {
//     REQUIRE(open_database() == true);
// }

// TEST_CASE("Adding a product to the database", "[insert]") {
//     const char *product_name = "SimpleProduct";
//     float price = 19.99;
//     int quantity = 5.5;
//     REQUIRE(insert_product(product_name, price, quantity) == true);
// }