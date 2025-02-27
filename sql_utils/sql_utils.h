#ifndef SQL_UTILS_H
#define SQL_UTILS_H

#include <sqlite3.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool insert_product(const char *product_name, float price, int quantity);

#ifdef __cplusplus
}
#endif

#endif