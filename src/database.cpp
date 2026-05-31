#include "database.h"
#include <iostream>

Database::Database(const std::string& path) : db(nullptr), dbPath(path) {}

Database::~Database() {
    close();
}

bool Database::initialize() {
    int rc = sqlite3_open(dbPath.c_str(), &db);
    
    if (rc) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    // Create conversations table
    const char* sql = "CREATE TABLE IF NOT EXISTS conversations("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "user_input TEXT NOT NULL,"
                      "bot_response TEXT NOT NULL,"
                      "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP"
                      ");"
    ;
    
    return executeSQL(sql);
}

bool Database::executeSQL(const std::string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &errMsg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    
    return true;
}

bool Database::saveConversation(const std::string& userInput, const std::string& botResponse) {
    std::string sql = "INSERT INTO conversations(user_input, bot_response) VALUES('"
                      + userInput + "', '" + botResponse + "');";
    
    return executeSQL(sql);
}

std::vector<std::pair<std::string, std::string>> Database::getAllConversations() {
    std::vector<std::pair<std::string, std::string>> conversations;
    sqlite3_stmt* stmt;
    
    const char* sql = "SELECT user_input, bot_response FROM conversations ORDER BY timestamp DESC LIMIT 100;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string userInput = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string botResponse = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            conversations.push_back({userInput, botResponse});
        }
        sqlite3_finalize(stmt);
    }
    
    return conversations;
}

std::vector<std::pair<std::string, std::string>> Database::searchConversations(const std::string& keyword) {
    std::vector<std::pair<std::string, std::string>> conversations;
    sqlite3_stmt* stmt;
    
    std::string sql = "SELECT user_input, bot_response FROM conversations WHERE user_input LIKE '%"
                      + keyword + "%' OR bot_response LIKE '%" + keyword + "%';";
    
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string userInput = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string botResponse = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            conversations.push_back({userInput, botResponse});
        }
        sqlite3_finalize(stmt);
    }
    
    return conversations;
}

bool Database::clearConversations() {
    return executeSQL("DELETE FROM conversations;");
}

int Database::getConversationCount() {
    sqlite3_stmt* stmt;
    int count = 0;
    
    if (sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM conversations;", -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            count = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    
    return count;
}

void Database::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool Database::isOpen() const {
    return db != nullptr;
}
