#include <iostream>
#include <format>
#include <string>
#include <unordered_map>
#include <chrono>


std::string getLocalizedFormatString(const std::string& key, const std::string& language) {
    static std::unordered_map<std::string, std::unordered_map<std::string, std::string>> translations = {
        {"en", {{"greeting", "Hello, {}! You have {} new messages. Task took {:.2f} seconds."}}},  // English
        {"fr", {{"greeting", "Bonjour, {}! Vous avez {} nouveaux messages. La tâche a pris {:.2f} secondes."}}},  // French
        {"de", {{"greeting", "Sie haben {1} neue Nachrichten, {0}. Die Aufgabe dauerte {2:.2f} Sekunden."}}}  // German
    };

    return translations[language][key];
}

int main() {
    std::string langs[] = {"en", "fr", "de"};
    std::string name = "Anna";
    int messageCount = 5;
    double timeTaken = 1.23;
    for (auto language : langs) {
        std::string fmt = getLocalizedFormatString("greeting", language);
        // use std::vformat when the format string is dynamically computed
        // The error reporting of std::vformat is unusable, for example if you swap the float and the int:
        // std::cout << std::vformat(fmt, std::make_format_args(name, timeTaken, messageCount))
        // You get the error message (it doesn't even tell you which arg has a problem):
        // libc++abi: terminating due to uncaught exception of type std::__1::format_error: The format specifier should consume the input or end with a '}'
        std::cout << std::vformat(fmt, std::make_format_args(name, messageCount, timeTaken))
                  << std::endl;
    }

    // You can use std::format when the format string is known at compile-time:
    // Using std::format
    std::string output1 = std::format("Hello, {}! You have {} new messages. Task took {:.2f} seconds.",
        name, messageCount, timeTaken);
    std::cout << "Using std::format: " << output1 << std::endl;

    // Using std::format_to an std::string
    std::string output2;
    output2.reserve(100);  // Preallocate space
    std::format_to(std::back_inserter(output2), "Hello, {}! You have {} new messages. Task took {:.2f} seconds.",
        name, messageCount, timeTaken);
    std::cout << "Using std::format_to std::string: " << output2 << std::endl;

    // Using std::format_to an std::vector
    std::vector<char> output3;
    output3.reserve(100);  // Preallocate space
    std::format_to(std::back_inserter(output3), "Hello, {}! You have {} new messages. Task took {:.2f} seconds.",
        name, messageCount, timeTaken);
    output3.push_back('\0');
    std::cout << "Using std::format_to std::vector: " << output3.data() << std::endl;

    return 0;
}
