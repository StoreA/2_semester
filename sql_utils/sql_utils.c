#include "sql_utils.h"
#include <stdio.h>
#include <stdbool.h>

bool insert_product(const char *product_name, float price, int quantity) {
    sqlite3 *db;
    int rc = sqlite3_open("../products.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return false;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO products (product_name, price, quantity) VALUES ('%s', %.2f, %d);",
             product_name, price, quantity);
    
    char *errMsg = 0;
    rc = sqlite3_exec(db, sql, NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);
    return true;
}