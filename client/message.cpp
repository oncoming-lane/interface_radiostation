#include "message.h"

std::string message(std::string data)
{
    std::string hexString = data;
    std::string asciiString;

    // Проходим по строке с шестнадцатеричными символами и конвертируем каждые два символа в символ ASCII
    for (size_t i = 0; i < hexString.length(); i += 2) {
        std::string byte = hexString.substr(i, 2);
        char chr = (char)std::stoul(byte, nullptr, 16); // Конвертируем два символа в число в 16-ричной СС
        //if (isalpha(chr) or isdigit(chr) ) 
        asciiString.push_back(chr); // Добавляем ASCII символ к строке
    }

    //std::cout << "ASCII строка: " << asciiString << std::endl;
    
    return asciiString;
}