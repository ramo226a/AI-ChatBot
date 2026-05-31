#ifndef NLP_H
#define NLP_H

#include <string>
#include <vector>
#include <map>

class NLP {
private:
    std::map<std::string, std::string> knowledgeBase;
    std::map<std::string, int> wordFrequency;
    
    // Convert text to lowercase
    std::string toLowercase(const std::string& text);
    
    // Tokenize text
    std::vector<std::string> tokenize(const std::string& text);
    
    // Remove punctuation
    std::string removePunctuation(const std::string& text);
    
public:
    NLP();
    ~NLP();
    
    // Initialize NLP engine with knowledge base
    void initialize();
    
    // Process user input
    std::string processInput(const std::string& input);
    
    // Generate smart response
    std::string generateSmartResponse(const std::string& input);
    
    // Extract keywords
    std::vector<std::string> extractKeywords(const std::string& text);
    
    // Calculate similarity between two texts
    double calculateSimilarity(const std::string& text1, const std::string& text2);
    
    // Learn new patterns
    void learn(const std::string& pattern, const std::string& response);
    
    // Get response based on patterns
    std::string getPatternResponse(const std::string& input);
};

#endif // NLP_H
