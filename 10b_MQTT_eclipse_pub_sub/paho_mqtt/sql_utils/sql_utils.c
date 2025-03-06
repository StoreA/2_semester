#include "sql_utils.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool open_database(sqlite3 **db, const char *db_path) {
    if (!db || !db_path) {
        fprintf(stderr, "Invalid database pointer or path.\n");
        return false;
    }

    int rc = sqlite3_open(db_path, db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database '%s': %s\n", db_path, sqlite3_errmsg(*db));
        sqlite3_close(*db);
        *db = NULL;
        return false;
    }
    printf("Database '%s' opened successfully.\n", db_path);
    return true;
}

bool create_tables(sqlite3 *db) {
    if (!db) {
        fprintf(stderr, "Database not open.\n");
        return false;
    }

    const char *sql_measurements = 
        "CREATE TABLE IF NOT EXISTS measurements ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "device TEXT NOT NULL,"
        "value TEXT NOT NULL,"
        "timestamp TEXT NOT NULL);";

    int rc = sqlite3_exec(db, sql_measurements, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create measurements table: %s\n", sqlite3_errmsg(db));
        return false;
    }

    // Optional: Add products table creation if still needed
    const char *sql_products = 
        "CREATE TABLE IF NOT EXISTS products ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "product_name TEXT NOT NULL,"
        "price REAL NOT NULL,"
        "quantity INTEGER NOT NULL);";

    rc = sqlite3_exec(db, sql_products, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create products table: %s\n", sqlite3_errmsg(db));
        return false;
    }

    return true;
}

bool insert_product(sqlite3 *db, const char *product_name, float price, int quantity) {
    if (!db) {
        fprintf(stderr, "Database not open.\n");
        return false;
    }

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO products (product_name, price, quantity) VALUES (?, ?, ?);";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Prepare statement failed: %s\n", sqlite3_errmsg(db));
        return false;
    }

    sqlite3_bind_text(stmt, 1, product_name, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, price);
    sqlite3_bind_int(stmt, 3, quantity);

    rc = sqlite3_step(stmt);
    bool success = (rc == SQLITE_DONE);
    if (!success) {
        fprintf(stderr, "Insert failed: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return success;
}

bool insert_measurement(sqlite3 *db, const char *device, const char *value, const char *timestamp) {
    if (!db) {
        fprintf(stderr, "Database not open.\n");
        return false;
    }

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO measurements (device, value, timestamp) VALUES (?, ?, ?);";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Prepare statement failed: %s\n", sqlite3_errmsg(db));
        return false;
    }

    sqlite3_bind_text(stmt, 1, device, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, value, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, timestamp, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    bool success = (rc == SQLITE_DONE);
    if (!success) {
        fprintf(stderr, "Insert failed: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return success;
}

bool close_database(sqlite3 *db) {
    if (!db) {
        fprintf(stderr, "No database to close.\n");
        return false;
    }

    int rc = sqlite3_close(db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to close database: %s\n", sqlite3_errmsg(db));
        return false;
    }
    printf("Database closed successfully.\n");
    return true;
}