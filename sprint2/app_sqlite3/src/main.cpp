#include <iostream>
#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>

using SqLite3Ptr = std::unique_ptr<sqlite3, decltype([](sqlite3* db) { sqlite3_close(db); })>;
using SqLite3StmtPtr = std::unique_ptr<sqlite3_stmt, decltype([](sqlite3_stmt* stmt) { sqlite3_finalize(stmt); })>;

// Функция для выполнения SQL-запроса
void execute_statement(sqlite3* db, const std::string& sql) {
    SqLite3StmtPtr stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, std::out_ptr(stmt), nullptr) != SQLITE_OK) {
        throw std::runtime_error("Не удалось подготовить запрос: " + std::string(sqlite3_errmsg(db)));
    }

    if (sqlite3_step(stmt.get()) != SQLITE_DONE) {
        throw std::runtime_error("Не удалось выполнить запрос: " + std::string(sqlite3_errmsg(db)));
    }
}

// Функция для вставки данных с использованием транзакции
void insert_data(sqlite3* db, const std::vector<std::pair<std::string, int>>& data) {
    execute_statement(db, "BEGIN TRANSACTION;");

    SqLite3StmtPtr stmt;
    std::string sql = "INSERT INTO users (name, age) VALUES (?, ?);";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, std::out_ptr(stmt), nullptr) != SQLITE_OK) {
        throw std::runtime_error("Не удалось подготовить запрос на вставку: " + std::string(sqlite3_errmsg(db)));
    }

    for (const auto& [name, age] : data) {
        sqlite3_reset(stmt.get());
        sqlite3_bind_text(stmt.get(), 1, name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt.get(), 2, age);

        if (sqlite3_step(stmt.get()) != SQLITE_DONE) {
            throw std::runtime_error("Не удалось вставить данные: " + std::string(sqlite3_errmsg(db)));
        }
    }

    execute_statement(db, "COMMIT;");
}

// Функция для чтения данных из базы
void read_data(sqlite3* db) {
    SqLite3StmtPtr stmt;
    std::string sql = "SELECT id, name, age FROM users;";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, std::out_ptr(stmt), nullptr) != SQLITE_OK) {
        throw std::runtime_error("Не удалось подготовить запрос на выборку: " + std::string(sqlite3_errmsg(db)));
    }

    while (sqlite3_step(stmt.get()) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt.get(), 0);
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 1));
        int age = sqlite3_column_int(stmt.get(), 2);

        // std::print("ID пользователя: {}, Имя: {}, Возраст: {}\n", id, name, age);
        std::printf("ID пользователя: %d, Имя: %s, Возраст: %d\n", id, name, age);
    }
}

int main() {
    sqlite3* db = nullptr;

    try {
        if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
            throw std::runtime_error("Не удалось открыть базу данных: " + std::string(sqlite3_errmsg(db)));
        }

        // Создание таблицы
        execute_statement(db, "CREATE TABLE users (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);");

        // Вставка данных
        std::vector<std::pair<std::string, int>> users = {{"Алиса", 25}, {"Боб", 30}, {"Чарли", 22}};
        insert_data(db, users);

        // Чтение данных
        read_data(db);

    } catch (const std::exception& e) {
        // std::print(stderr, "Ошибка: {}\n", e.what());
        std::fprintf(stderr, "Ошибка: %s\n", e.what());
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    sqlite3_close(db);
    return EXIT_SUCCESS;
}