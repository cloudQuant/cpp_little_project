#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <sqlite3.h>

const std::string csvFilePath = "../data/所有品种合约的数据.csv";
const std::string dbFilePath = "contract_data.db";

std::vector<std::vector<std::string> > readCSV(const std::string& filePath) {
    std::vector<std::vector<std::string> > data;
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    return data;
}

void writeToSQLite(const std::vector<std::vector<std::string> > & data, const std::string& dbFilePath) {
    sqlite3* db;
    int rc = sqlite3_open(dbFilePath.c_str(), &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    char* errMsg = 0;
    const char* createTableSql = "CREATE TABLE IF NOT EXISTS securities ("
                                 "order_book_id TEXT PRIMARY KEY, "
                                 "symbol TEXT, "
                                 "abbrev_symbol TEXT, "
                                 "type TEXT, "
                                 "listed_date TEXT, "
                                 "de_listed_date TEXT);";
    rc = sqlite3_exec(db, createTableSql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    for (const auto& row : data) {
        std::string insertSql = "INSERT INTO securities (order_book_id, symbol, abbrev_symbol, type, listed_date, de_listed_date) "
                                "VALUES ('" + row[0] + "', '" + row[1] + "', '" + row[2] + "', '" + row[3] + "', '" + row[4] + "', '" + row[5] + "');";
        rc = sqlite3_exec(db, insertSql.c_str(), 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }

    sqlite3_close(db);
}

void readFromSQLite(const std::string& dbFilePath) {
    sqlite3* db;
    int rc = sqlite3_open(dbFilePath.c_str(), &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    const char* selectSql = "SELECT * FROM securities;";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, selectSql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    } else {
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            std::string order_book_id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string symbol = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string abbrev_symbol = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            std::string listed_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            std::string de_listed_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

            std::cout << "Order Book ID: " << order_book_id << ", Symbol: " << symbol << ", Abbrev Symbol: " << abbrev_symbol
                      << ", Type: " << type << ", Listed Date: " << listed_date << ", De-Listed Date: " << de_listed_date << std::endl;
        }
        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
}

int main() {
    // 读取 CSV 文件
    std::vector<std::vector<std::string> > data = readCSV(csvFilePath);
    // std::cout << "read csv succeed" << std::endl;
    // 将数据写入 SQLite3 数据库
    writeToSQLite(data, dbFilePath);

    // 从 SQLite3 数据库中读取数据
    readFromSQLite(dbFilePath);

    return 0;
}