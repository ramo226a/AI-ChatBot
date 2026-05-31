#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <sqlite3.h>

class Database {
private:
    sqlite3* db;
    std::string dbPath;
    
    bool executeSQL(const std::string& sql);
    
public:
    Database(const std::string& path = "chatbot.db");
    ~Database();
    
    // Initialize database
    bool initialize();
    
    // Save conversation
    bool saveConversation(const std::string& userInput, const std::string& botResponse);
    
    // Get all conversations
    std::vector<std::pair<std::string, std::string>> getAllConversations();
    
    // Get conversations by keyword
    std::vector<std::pair<std::string, std::string>> searchConversations(const std::string& keyword);
    
    // Clear all conversations
    bool clearConversations();
    
    // Get database size
    int getConversationCount();
    
    // Close database
    void close();
    
    // Check if database is open
    bool isOpen() const;
};

#endif // DATABASE_H
