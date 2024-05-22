#include <sstream>
#include <cctype>

#include "message.h"
#include "screen.h"


void message(std::string data, std::vector<std::string> *texts)
{
    (*texts).clear();

    std::istringstream iss(data);
    std::string token;

    while (std::getline(iss, token, '^')) // Разбиваем строку по символу '^'
    { 
        std::cout << token << std::endl; // Выводим подстроку

        (*texts).push_back(token);
    }        

    std::cout << "Результат: ";
    for (const char &c : data) 
        if (std::isalnum(c))
            std::putchar(c); // Если да, добавляем его к результату
}