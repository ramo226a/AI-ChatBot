#include <iostream>
#include <string>
#include "chatbot.h"

void printWelcome() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════╗\n";
    std::cout << "║         مرحباً بك في برنامج ذكاء اصطناعي          ║\n";
    std::cout << "║           Welcome to AI ChatBot Program            ║\n";
    std::cout << "╚════════════════════════════════════════════════════╝\n";
    std::cout << "\n";
    std::cout << "💬 ابدأ المحادثة معي! (Start chatting with me!)\n";
    std::cout << "📝 اكتب 'exit' أو 'خروج' للخروج من البرنامج\n";
    std::cout << "📚 اكتب 'history' أو 'سجل' لعرض السجل\n";
    std::cout << "🗑️  اكتب 'clear' أو 'مسح' لحذف السجل\n";
    std::cout << "════════════════════════════════════════════════════\n\n";
}

void printHistory(const ChatBot& bot) {
    auto history = bot.getHistory();
    if (history.empty()) {
        std::cout << "\n❌ لا يوجد سجل محادثات حتى الآن\n\n";
        return;
    }
    
    std::cout << "\n════════════════════════════════════════════════════\n";
    std::cout << "📋 سجل المحادثات (Conversation History):\n";
    std::cout << "══════════════════════════════════���═════════════════\n\n";
    
    int count = 1;
    for (const auto& pair : history) {
        std::cout << count << ". YOU: " << pair.first << "\n";
        std::cout << "   BOT: " << pair.second << "\n";
        std::cout << "───────────────────────────────────────────────────\n";
        count++;
    }
    std::cout << "\n";
}

int main() {
    ChatBot bot;
    printWelcome();
    
    std::string userInput;
    
    while (true) {
        std::cout << "👤 You: ";
        std::getline(std::cin, userInput);
        
        // Check for exit commands
        if (userInput == "exit" || userInput == "خروج" || userInput == "quit") {
            std::cout << "\n🎉 شكراً لاستخدام برنامج الذكاء الاصطناعي! وداعاً!\n";
            std::cout << "Thank you for using AI ChatBot! Goodbye!\n\n";
            break;
        }
        
        // Check for history command
        if (userInput == "history" || userInput == "سجل") {
            printHistory(bot);
            continue;
        }
        
        // Check for clear command
        if (userInput == "clear" || userInput == "مسح") {
            bot.clearHistory();
            std::cout << "\n✅ تم مسح السجل بنجاح (History cleared successfully)\n\n";
            continue;
        }
        
        // Empty input check
        if (userInput.empty()) {
            continue;
        }
        
        // Get response from chatbot
        std::string response = bot.chat(userInput);
        
        std::cout << "🤖 Bot: " << response << "\n\n";
    }
    
    return 0;
}
