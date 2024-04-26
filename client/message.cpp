#include <sstream>
#include <cctype>

#include "message.h"
#include "screen.h"


std::vector<sf::Text*> message(std::string data)
{

    std::istringstream iss(data);
    std::string token;
    std::string result = "";
    std::string message = "";

    
    sf::Font font;
    font.loadFromFile("troika.otf");

    std::vector<sf::Text*> texts;
    int i = 0;
    while (std::getline(iss, token, '^')) 
    { // Разбиваем строку по символу '^'
        //main_screen->change_text(token, sf::Vector2f(s + 200 * i, 300));
        i++;
        sf::Text* text = new sf::Text(token, font, 24);
        text->setPosition(300 + 200 * i, 300);
        texts.push_back(text);
        
        std::cout << token << std::endl; // Выводим подстроку
    }        



    
    for (char c : data) 
    {
    // Проверяем, является ли символ буквой или цифрой в ASCII
        if (std::isalnum(c))
            result += c; // Если да, добавляем его к результату
    }

    std::cout << "Результат: " << result << std::endl;


    
    return texts;
}