 #include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath> // For math operations

using namespace std; // Use standard namespace

// Namespace for utility functions
namespace Utils {
    // Function to convert text to lowercase
    string toLowerCase(const string &input) {
        string lower = input;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        return lower;
    }

    // Function to check if a string contains a keyword
    bool contains(const string &input, const string &keyword) {
        return input.find(keyword) != string::npos;
    }
}

// Namespace for sentiment analysis
namespace Sentiment {
    // Function to perform basic sentiment analysis
    string analyze(const string &input) {
        if (Utils::contains(input, "happy") || Utils::contains(input, "good") || Utils::contains(input, "great") || Utils::contains(input, "joy")) {
            return "Positive Sentiment Detected!";
        }
        if (Utils::contains(input, "sad") || Utils::contains(input, "bad") || Utils::contains(input, "angry") || Utils::contains(input, "upset")) {
            return "Negative Sentiment Detected!";
        }
        return "Neutral Sentiment.";
    }
}

// Namespace for complex question handling
namespace Questions {
    // Function to handle math questions
    string handleMath(const string &input) {
        // Extract numbers and operators
        stringstream ss(input);
        double num1, num2;
        char op;

        // Match pattern like "What is 5 + 3?" or "5+3"
        if (ss >> num1 >> op >> num2) {
            switch (op) {
                case '+': return "The result is: " + to_string(num1 + num2);
                case '-': return "The result is: " + to_string(num1 - num2);
                case '*': return "The result is: " + to_string(num1 * num2);
                case '/':
                    if (num2 == 0) return "Error: Division by zero is undefined.";
                    return "The result is: " + to_string(num1 / num2);
                default: return "I couldn't calculate that. Please provide a valid math expression.";
            }
        }
        return "I couldn't calculate that. Please provide a valid math expression.";
    }

    // Function to answer general knowledge questions
    string handleGeneral(const string &input) {
        // Geology
        if (Utils::contains(input, "rock")) {
            return "A rock is a naturally occurring solid composed of minerals or mineraloids.";
        }

        // History
        if (Utils::contains(input, "discovered america")) {
            return "Christopher Columbus is credited with discovering America in 1492.";
        }

        // Biology
        if (Utils::contains(input, "dna")) {
            return "DNA, or deoxyribonucleic acid, is the molecule that carries genetic information in living organisms.";
        }

        // Computer Science
        if (Utils::contains(input, "computer")) {
            return "A computer is an electronic device that processes data according to instructions to produce meaningful output.";
        }

        // Social Studies
        if (Utils::contains(input, "democracy")) {
            return "Democracy is a system of government where citizens exercise power by voting.";
        }

        return "I don't have information on that. Could you try asking another question?";
    }

    // Main function to handle all complex questions
    string answer(const string &input) {
        // Check for math questions
        if (Utils::contains(input, "+") || Utils::contains(input, "-") || Utils::contains(input, "*") || Utils::contains(input, "/")) {
            return handleMath(input);
        }

        // Check for general knowledge questions
        return handleGeneral(input);
    }
}

// Namespace for chatbot dialogue management
namespace Chatbot {
    // Function to handle dialogue responses
    string handleDialogue(const string &input) {
        string lowerInput = Utils::toLowerCase(input);

        if (lowerInput.find("hello") != string::npos || lowerInput.find("hi") != string::npos) {
            return "Hello! How can I assist you today?";
        }
        if (lowerInput.find("how are you") != string::npos) {
            return "I'm just a program, but I'm functioning as expected. How about you?";
        }
        if (lowerInput.find("what is your name") != string::npos) {
            return "I'm an AI chatbot created to assist you.";
        }
        if (lowerInput.find("bye") != string::npos) {
            return "Goodbye! Have a great day!";
        }

        return "I'm sorry, I didn't understand that. Could you please elaborate?";
    }
}

int main() {
    string userInput;

    cout << "AI Chatbot: Hello! I'm your assistant. Type 'bye' to exit.\n";

    while (true) {
        cout << "\nYou: ";
        getline(cin, userInput);

        // Check if the user wants to exit
        if (Utils::toLowerCase(userInput) == "bye") {
            cout << "AI Chatbot: Goodbye! Have a great day!\n";
            break;
        }

        // Perform sentiment analysis
        string sentiment = Sentiment::analyze(userInput);
        cout << "AI Chatbot (Sentiment Analysis): " << sentiment << "\n";

        // Handle complex questions
        string complexAnswer = Questions::answer(userInput);
        if (complexAnswer != "I don't have information on that. Could you try asking another question?") {
            cout << "AI Chatbot: " << complexAnswer << "\n";
            continue; // Skip to the next iteration if a complex question was handled
        }

        // Handle dialogue responses
        string response = Chatbot::handleDialogue(userInput);
        cout << "AI Chatbot: " << response << "\n";
    }

    return 0;
}
