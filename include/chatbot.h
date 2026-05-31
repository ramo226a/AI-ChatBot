#ifndef CHATBOT_H
#define CHATBOT_H

#include <string>
#include <vector>
#include <map>
#include "database.h"
#include "nlp.h"

class ChatBot {
private:
    Database db;
    NLP nlp;
    std::vector<std::pair<std::string, std::string>> conversationHistory;
    
public:
    ChatBot();
    ~ChatBot();
    
    // Main chat function
    std::string chat(const std::string& userInput);
    
    // Response generation
    std::string generateResponse(const std::string& input);
    
    // Learning from conversations
    void learnFromConversation(const std::string& input, const std::string& response);
    
    // Get conversation history
    std::vector<std::pair<std::string, std::string>> getHistory() const;
    
    // Clear conversation
    void clearHistory();
    
    // Save conversation
    void saveConversation();
    
    // Load previous conversations
    void loadConversations();
};

#endif // CHATBOT_H
