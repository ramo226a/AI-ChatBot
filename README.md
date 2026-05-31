# AI ChatBot

برنامج ذكاء اصطناعي شبيه بـ ChatGPT مكتوب بلغة C++

## المميزات

✨ **الميزات الرئيسية:**
- محادثة ذكية مع المستخدم
- معالجة اللغة الطبيعية
- حفظ السجل التاريخي للمحادثات
- التعلم من التفاعلات السابقة
- واجهة سهلة الاستخدام (Command Line)
- قاعدة بيانات محلية

## المتطلبات

- C++17 أو أحدث
- CMake 3.10+
- SQLite3

## التثبيت

```bash
git clone https://github.com/ramo226a/AI-ChatBot.git
cd AI-ChatBot
mkdir build
cd build
cmake ..
make
```

## الاستخدام

```bash
./chatbot
```

ثم ابدأ في الكتابة والحوار مع البرنامج!

## الملفات الرئيسية

- `main.cpp` - نقطة البداية
- `chatbot.h` و `chatbot.cpp` - محرك الذكاء الاصطناعي
- `database.h` و `database.cpp` - إدارة قاعدة البيانات
- `nlp.h` و `nlp.cpp` - معالجة اللغة الطبيعية

## الرخصة

MIT License

---

**تم الإنشاء بواسطة:** ramo226a
