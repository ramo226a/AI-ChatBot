# تعليمات التثبيت

## المتطلبات الأساسية

### على Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install g++ cmake sqlite3 libsqlite3-dev
```

### على macOS:
```bash
brew install cmake sqlite3
```

### على Windows:
- تحميل Visual Studio مع C++ support
- تحميل CMake من https://cmake.org
- تحميل SQLite3

---

## خطوات التثبيت والتشغيل

### 1. استنساخ المستودع
```bash
git clone https://github.com/ramo226a/AI-ChatBot.git
cd AI-ChatBot
```

### 2. إنشاء مجلد البناء
```bash
mkdir build
cd build
```

### 3. تشغيل CMake
```bash
cmake ..
```

### 4. بناء البرنامج
```bash
make
```

### 5. تشغيل البرنامج
```bash
./bin/chatbot
```

---

## الاستخدام

بعد تشغيل البرنامج:

1. **ابدأ المحادثة** - اكتب رسالتك والبرنامج سيرد عليك
2. **عرض السجل** - اكتب `history` أو `سجل`
3. **مسح السجل** - اكتب `clear` أو `مسح`
4. **الخروج** - اكتب `exit` أو `خروج`

---

## استكشاف الأخطاء

### المشكلة: "cannot find -lsqlite3"
```bash
# على Ubuntu
sudo apt-get install libsqlite3-dev

# على macOS
brew install sqlite3
```

### المشكلة: "cmake: command not found"
```bash
# على Ubuntu
sudo apt-get install cmake

# على macOS
brew install cmake
```

---

## الدعم
إذا واجهت مشكلة، يرجى فتح Issue على GitHub!
