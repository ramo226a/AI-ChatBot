#include "nlp.h"
#include <algorithm>
#include <sstream>
#include <cctype>
#include <cmath>

NLP::NLP() {}

NLP::~NLP() {}

void NLP::initialize() {
    // Initialize with basic knowledge base patterns
    knowledgeBase["hello"] = "مرحبا! كيف حالك؟ كيف يمكنني مساعدتك اليوم؟";
    knowledgeBase["hi"] = "أهلا وسهلا! ما الذي يمكنني مساعدتك فيه؟";
    knowledgeBase["how are you"] = "أنا بخير، شكراً لسؤالك! كيف أنت؟";
    knowledgeBase["what is your name"] = "أنا ChatBot الذكي، برنامج ذكاء اصطناعي هنا لمساعدتك!";
    knowledgeBase["thank you"] = "يسعدني أن أكون مفيداً! هل هناك شيء آخر تحتاجه؟";
    knowledgeBase["thanks"] = "شكراً لاستخدام البرنامج! هل تحتاج لشيء آخر؟";
    knowledgeBase["bye"] = "وداعاً! أتمنى أن تكون قد استفدت. إلى اللقاء!";
    knowledgeBase["goodbye"] = "شكراً على المحادثة! أراك قريباً!";
    knowledgeBase["help"] = "يمكنني مساعدتك في الإجابة على الأسئلة والمحادثة. جرب أن تسأل عن أي موضوع!";
    knowledgeBase["who are you"] = "أنا برنامج ذكاء اصطناعي متقدم مصمم للمحادثة والمساعدة!";
}

std::string NLP::toLowercase(const std::string& text) {
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

std::vector<std::string> NLP::tokenize(const std::string& text) {
    std::vector<std::string> tokens;
    std::stringstream ss(text);
    std::string word;
    
    while (ss >> word) {
        tokens.push_back(word);
    }
    
    return tokens;
}

std::string NLP::removePunctuation(const std::string& text) {
    std::string result = text;
    result.erase(std::remove_if(result.begin(), result.end(),
                                [](unsigned char c) { return std::ispunct(c); }),
                 result.end());
    return result;
}

std::string NLP::processInput(const std::string& input) {
    std::string processed = toLowercase(input);
    processed = removePunctuation(processed);
    return processed;
}

std::vector<std::string> NLP::extractKeywords(const std::string& text) {
    std::vector<std::string> keywords;
    std::vector<std::string> tokens = tokenize(processInput(text));
    
    // Simple keyword extraction - words longer than 3 characters
    for (const auto& token : tokens) {
        if (token.length() > 3) {
            keywords.push_back(token);
            wordFrequency[token]++;
        }
    }
    
    return keywords;
}

double NLP::calculateSimilarity(const std::string& text1, const std::string& text2) {
    std::vector<std::string> tokens1 = tokenize(processInput(text1));
    std::vector<std::string> tokens2 = tokenize(processInput(text2));
    
    int commonWords = 0;
    for (const auto& t1 : tokens1) {
        for (const auto& t2 : tokens2) {
            if (t1 == t2) {
                commonWords++;
                break;
            }
        }
    }
    
    int maxSize = std::max(tokens1.size(), tokens2.size());
    if (maxSize == 0) return 0.0;
    
    return static_cast<double>(commonWords) / maxSize;
}

void NLP::learn(const std::string& pattern, const std::string& response) {
    knowledgeBase[toLowercase(pattern)] = response;
}

std::string NLP::getPatternResponse(const std::string& input) {
    std::string processedInput = processInput(input);
    
    // Check for exact match
    if (knowledgeBase.find(processedInput) != knowledgeBase.end()) {
        return knowledgeBase[processedInput];
    }
    
    // Check for partial match with highest similarity
    double maxSimilarity = 0.0;
    std::string bestMatch;
    
    for (const auto& pair : knowledgeBase) {
        double similarity = calculateSimilarity(processedInput, pair.first);
        if (similarity > maxSimilarity && similarity > 0.5) {
            maxSimilarity = similarity;
            bestMatch = pair.second;
        }
    }
    
    return bestMatch;
}

std::string NLP::generateSmartResponse(const std::string& input) {
    std::string processedInput = processInput(input);
    
    // Check for question words
    if (processedInput.find("كيف") != std::string::npos) {
        return "هذا سؤال جيد! أنا أعمل على فهم هذا بشكل أفضل. هل يمكنك توضيح أكثر؟";
    }
    
    if (processedInput.find("ماذا") != std::string::npos) {
        return "أنا أحاول فهم ما تقصده. يمكنك إعطائي مزيداً من التفاصيل؟";
    }
    
    if (processedInput.find("لماذا") != std::string::npos) {
        return "هذا سؤال عميق! دعني أفكر في الإجابة... هل لديك أي معلومات إضافية؟";
    }
    
    if (processedInput.find("متى") != std::string::npos) {
        return "هذا يعتمد على عوامل كثيرة. هل يمكنك توضيح السياق أكثر؟";
    }
    
    // Extract keywords and generate response
    std::vector<std::string> keywords = extractKeywords(input);
    
    if (!keywords.empty()) {
        return "أنا أفهم أنك تتحدث عن " + keywords[0] + ". هذا موضوع مثير للاهتمام! قل لي المزيد.";
    }
    
    // Default response
    return "هذا تعليق مثير للاهتمام! هل يمكنك توضيح أكثر؟ أنا أتعلم من كل محادثة معك.";
}
