// ==================== Knowledge Base ====================

const knowledgeBase = {
    'hello': 'مرحبا! كيف حالك؟ كيف يمكنني مساعدتك اليوم؟',
    'hi': 'أهلا وسهلا! ما الذي يمكنني مساعدتك فيه؟',
    'how are you': 'أنا بخير، شكراً لسؤالك! كيف أنت؟',
    'what is your name': 'أنا ChatBot الذكي، برنامج ذكاء اصطناعي هنا لمساعدتك!',
    'thank you': 'يسعدني أن أكون مفيداً! هل هناك شيء آخر تحتاجه؟',
    'thanks': 'شكراً لاستخدام البرنامج! هل تحتاج لشيء آخر؟',
    'bye': 'وداعاً! أتمنى أن تكون قد استفدت. إلى اللقاء!',
    'goodbye': 'شكراً على المحادثة! أراك قريباً!',
    'help': 'يمكنني مساعدتك في الإجابة على الأسئلة والمحادثة. جرب أن تسأل عن أي موضوع!',
    'who are you': 'أنا برنامج ذكاء اصطناعي متقدم مصمم للمحادثة والمساعدة!',
    'مرحبا': 'مرحبا! كيف حالك؟ كيف يمكنني مساعدتك؟',
    'السلام عليكم': 'وعليكم السلام ورحمة الله وبركاته! كيف حالك؟',
    'كيف حالك': 'أنا بخير، شكراً لسؤالك! وأنت كيف حالك؟',
    'من أنت': 'أنا ChatBot الذكي، برنامج ذكاء اصطناعي هنا لمساعدتك!',
    'شكراً': 'يسعدني أن أكون مفيداً! هل هناك شيء آخر؟',
    'شكرا': 'العفو! هل تحتاج لشيء آخر؟',
    'وداعاً': 'وداعاً! كان سعيداً بمحادثتك معي 👋',
    'ساعدني': 'بكل سرور! ما الذي تحتاج مساعدة فيه؟',
};

const questionResponses = {
    'كيف': 'هذا سؤال جيد! أنا أعمل على فهم هذا بشكل أفضل. هل يمكنك توضيح أكثر؟',
    'ماذا': 'أنا أحاول فهم ما تقصده. يمكنك إعطائي مزيداً من التفاصيل؟',
    'لماذا': 'هذا سؤال عميق! دعني أفكر في الإجابة... هل لديك أي معلومات إضافية؟',
    'متى': 'هذا يعتمد على عوامل كثيرة. هل يمكنك توضيح السياق أكثر؟',
    'أين': 'هذا موضوع مثير للاهتمام! هل يمكنك إعطائي مزيد من التفاصيل؟',
    'how': 'That\'s a great question! Can you tell me more about it?',
    'what': 'I\'m trying to understand what you mean. Can you clarify?',
    'why': 'That\'s a deep question! Let me think about it.',
    'when': 'That depends on many factors. Can you provide more context?',
};

// ==================== DOM Elements ====================

const chatContainer = document.getElementById('chatContainer');
const userInput = document.getElementById('userInput');
const sendBtn = document.getElementById('sendBtn');
const clearBtn = document.getElementById('clearBtn');
const downloadBtn = document.getElementById('downloadBtn');

// ==================== Load Conversations ====================

let conversations = JSON.parse(localStorage.getItem('chatHistory')) || [];

function loadConversations() {
    conversations.forEach(msg => {
        if (msg.type === 'user') {
            addMessage(msg.text, 'user');
        } else {
            addMessage(msg.text, 'bot');
        }
    });
    scrollToBottom();
}

// ==================== Add Message to Chat ====================

function addMessage(text, sender) {
    const messageDiv = document.createElement('div');
    messageDiv.classList.add('message', sender);

    const messageContent = document.createElement('div');
    messageContent.classList.add('message-content');
    messageContent.textContent = text;

    messageDiv.appendChild(messageContent);

    // Add timestamp
    const timeDiv = document.createElement('div');
    timeDiv.classList.add('message-time');
    timeDiv.textContent = new Date().toLocaleTimeString('ar-SA', {
        hour: '2-digit',
        minute: '2-digit'
    });
    messageDiv.appendChild(timeDiv);

    chatContainer.appendChild(messageDiv);
    scrollToBottom();

    // Save to localStorage
    conversations.push({ type: sender, text: text });
    localStorage.setItem('chatHistory', JSON.stringify(conversations));
}

// ==================== Show Typing Indicator ====================

function showTyping() {
    const messageDiv = document.createElement('div');
    messageDiv.classList.add('message', 'bot');
    messageDiv.id = 'typingIndicator';

    const messageContent = document.createElement('div');
    messageContent.classList.add('message-content', 'typing');
    messageContent.innerHTML = '<span></span><span></span><span></span>';

    messageDiv.appendChild(messageContent);
    chatContainer.appendChild(messageDiv);
    scrollToBottom();
}

function removeTyping() {
    const typing = document.getElementById('typingIndicator');
    if (typing) typing.remove();
}

// ==================== NLP Processing ====================

function processInput(text) {
    return text.toLowerCase().trim().replace(/[.,!?;:]/g, '');
}

function extractKeywords(text) {
    const words = processInput(text).split(' ');
    return words.filter(word => word.length > 3);
}

function calculateSimilarity(text1, text2) {
    const tokens1 = processInput(text1).split(' ');
    const tokens2 = processInput(text2).split(' ');

    let commonWords = 0;
    tokens1.forEach(t1 => {
        if (tokens2.includes(t1)) commonWords++;
    });

    const maxSize = Math.max(tokens1.length, tokens2.length);
    return maxSize === 0 ? 0 : commonWords / maxSize;
}

function findBestMatch(input) {
    let maxSimilarity = 0;
    let bestMatch = null;

    for (let key in knowledgeBase) {
        const similarity = calculateSimilarity(input, key);
        if (similarity > maxSimilarity && similarity > 0.5) {
            maxSimilarity = similarity;
            bestMatch = knowledgeBase[key];
        }
    }

    return bestMatch;
}

// ==================== Generate Response ====================

function generateResponse(input) {
    const processed = processInput(input);

    // Check for exact match
    if (knowledgeBase[processed]) {
        return knowledgeBase[processed];
    }

    // Check for question words
    for (let word in questionResponses) {
        if (processed.includes(word)) {
            return questionResponses[word];
        }
    }

    // Try to find similar pattern
    const bestMatch = findBestMatch(input);
    if (bestMatch) return bestMatch;

    // Extract keywords and generate custom response
    const keywords = extractKeywords(input);
    if (keywords.length > 0) {
        return `أنا أفهم أنك تتحدث عن ${keywords[0]}. هذا موضوع مثير للاهتمام! قل لي المزيد.`;
    }

    // Default responses
    const defaultResponses = [
        'هذا تعليق مثير للاهتمام! هل يمكنك توضيح أكثر؟',
        'أنا أحاول فهم ما تقصده. يمكنك إعطائي مزيداً من التفاصيل؟',
        'هذا فكرة جيدة! خبرني أكثر عن هذا.',
        'أنا متأكد أن هذا مهم لك. هل يمكنك توضيح أكثر؟',
        'سؤال رائع! دعني أفكر في الأمر... ما رأيك؟'
    ];

    return defaultResponses[Math.floor(Math.random() * defaultResponses.length)];
}

// ==================== Send Message ====================

function sendMessage() {
    const message = userInput.value.trim();

    if (!message) return;

    // Add user message
    addMessage(message, 'user');
    userInput.value = '';
    userInput.focus();

    // Show typing indicator
    showTyping();

    // Generate and send bot response
    setTimeout(() => {
        removeTyping();
        const response = generateResponse(message);
        addMessage(response, 'bot');
    }, 800);
}

// ==================== Clear Chat ====================

function clearChat() {
    if (confirm('هل تريد فعلاً مسح جميع المحادثات؟')) {
        chatContainer.innerHTML = `
            <div class="welcome-message">
                <h2>👋 مرحباً بك!</h2>
                <p>أنا ChatBot الذكي، برنامج ذكاء اصطناعي هنا لمساعدتك</p>
                <p style="font-size: 12px; color: #888; margin-top: 10px;">ابدأ المحادثة معي الآن 💬</p>
            </div>
        `;
        conversations = [];
        localStorage.removeItem('chatHistory');
        scrollToBottom();
    }
}

// ==================== Download Chat ====================

function downloadChat() {
    let content = 'سجل المحادثات\n';
    content += '================\n\n';

    conversations.forEach(msg => {
        const sender = msg.type === 'user' ? '👤 أنت' : '🤖 البرنامج';
        content += `${sender}: ${msg.text}\n\n`;
    });

    content += `\n================\nتم الحفظ في: ${new Date().toLocaleString('ar-SA')}`;

    const blob = new Blob([content], { type: 'text/plain;charset=utf-8' });
    const link = document.createElement('a');
    link.href = URL.createObjectURL(blob);
    link.download = `chatbot-history-${Date.now()}.txt`;
    link.click();
}

// ==================== Scroll to Bottom ====================

function scrollToBottom() {
    chatContainer.scrollTop = chatContainer.scrollHeight;
}

// ==================== Event Listeners ====================

sendBtn.addEventListener('click', sendMessage);
userInput.addEventListener('keypress', (e) => {
    if (e.key === 'Enter') sendMessage();
});

clearBtn.addEventListener('click', clearChat);
downloadBtn.addEventListener('click', downloadChat);

// ==================== Initialize ====================

window.addEventListener('load', () => {
    if (conversations.length === 0) {
        scrollToBottom();
    } else {
        loadConversations();
    }
});

// Auto-focus on input
userInput.focus();
