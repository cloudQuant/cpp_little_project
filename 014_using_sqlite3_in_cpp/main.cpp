#include <iostream>
#include <sqlite3.h>

int main() {
    sqlite3* db;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    char* errMsg = 0;
    const char* createTableSql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);";
    rc = sqlite3_exec(db, createTableSql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    const char* insertSql = "INSERT INTO users (name, age) VALUES ('Alice', 30);";
    rc = sqlite3_exec(db, insertSql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    const char* selectSql = "SELECT * FROM users;";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, selectSql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    } else {
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* name = sqlite3_column_text(stmt, 1);
            int age = sqlite3_column_int(stmt, 2);
            std::cout << "ID: " << id << ", Name: " << name << ", Age: " << age << std::endl;
        }
        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
    return 0;
}