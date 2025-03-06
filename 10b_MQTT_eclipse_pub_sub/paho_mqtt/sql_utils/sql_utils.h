#ifndef SQL_UTILS_H
#define SQL_UTILS_H

#include <sqlite3.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool open_database(sqlite3 **db, const char *db_path);
bool create_tables(sqlite3 *db);  // New function to ensure tables exist
bool insert_product(sqlite3 *db, const char *product_name, float price, int quantity);
bool insert_measurement(sqlite3 *db, const char *device, const char *value, const char *timestamp);
bool close_database(sqlite3 *db);

#ifdef __cplusplus
}
#endif

#endif /* SQL_UTILS_H */