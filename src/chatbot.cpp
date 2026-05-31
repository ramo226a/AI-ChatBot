#include "chatbot.h"
#include <iostream>
#include <algorithm>
#include <ctime>

ChatBot::ChatBot() {
    db.initialize();
    nlp.initialize();
    loadConversations();
}

ChatBot::~ChatBot() {
    saveConversation();
}

std::string ChatBot::chat(const std::string& userInput) {
    std::string response = generateResponse(userInput);
    
    // Store in history
    conversationHistory.push_back({userInput, response});
    
    // Learn from this interaction
    learnFromConversation(userInput, response);
    
    // Save to database
    db.saveConversation(userInput, response);
    
    return response;
}

std::string ChatBot::generateResponse(const std::string& input) {
    // Process input through NLP
    std::string processedInput = nlp.processInput(input);
    
    // Try to get pattern-based response first
    std::string patternResponse = nlp.getPatternResponse(processedInput);
    if (!patternResponse.empty()) {
        return patternResponse;
    }
    
    // Generate smart response based on keywords
    return nlp.generateSmartResponse(input);
}

void ChatBot::learnFromConversation(const std::string& input, const std::string& response) {
    // Extract keywords and create patterns
    std::vector<std::string> keywords = nlp.extractKeywords(input);
    
    // Learn this pattern for future use
    for (const auto& keyword : keywords) {
        nlp.learn(keyword, response);
    }
}

std::vector<std::pair<std::string, std::string>> ChatBot::getHistory() const {
    return conversationHistory;
}

void ChatBot::clearHistory() {
    conversationHistory.clear();
    db.clearConversations();
}

void ChatBot::saveConversation() {
    // Already saved in database during chat
}

void ChatBot::loadConversations() {
    conversationHistory = db.getAllConversations();
}
