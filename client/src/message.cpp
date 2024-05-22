#include <regex>

#include "message.h"
#include "screen.h"

void message(std::string &data, std::vector<std::string> *texts) {
    (*texts).clear();

    std::string ascii_data;
    for (auto &symbol : data)
        if (std::isprint(symbol))
            ascii_data += symbol;

    std::cout << "ASCII Data: `" << ascii_data << "`\n";

    std::regex                 re("[ ^\"9]");
    std::sregex_token_iterator first {ascii_data.begin(), ascii_data.end(), re, -1}, last;

    for (auto it = first; it != last; it++) {
        auto token = *it;

        if (token.length() > 0) {
            std::cout << "[TOKEN]: `" << token << "`\n";

            texts->push_back(*it);
        }
    }
}