#include "buttons.h"

//словарь команд!
std::map <std::string, std::string > commands = 
{                                           //push up long      push up short     push down
    {"0", "\x05\x83\x02\x57\x7A"},          //05 83 01 57 C1    05 83 02 57 7A    05 83 00 57 A8
    {"1", "\x05\x89\x02\x57\x24"},          //05 89 01 57 9F    05 89 02 57 24    05 89 00 57 F6
    {"2", "\x05\x84\x02\x57\xB5"},          //05 84 01 57 0E    05 84 02 57 B5    05 84 02 57 67
    {"3", "\x05\x8A\x02\x57\xB4"},          //05 8A 01 57 0F    05 8A 02 57 B4    05 8A 00 57 66
    {"4", "\x05\x85\x02\x57\xC5"},          //05 85 01 57 7E    05 85 02 57 C5    05 85 00 57 17

    {"7", "\x05\x54\x01\x57\xA4"},          //05 54 01 57 A4                                            button_light
    {"8", "\x05\x81\x01\x57\x21"},          //05 81 01 57 21                                            button_home
    {"9", "\x05\x84\x02\x57\xB5"},                                                                    //button_power
    {"10", "\x05\x94\x01\x57\xED"},         //05 94 01 57 ED                      05 94 00 57 84        button_emergency

    {"5", "\x05\x04\x01\x57\xF5"},          //05 04 01 57 F5                                            button_arrow_left
    {"6", "\x05\x04\xFF\x57\xCC"}           //05 04 FF 57 CC                                            button_arrow_right
};


void buttons_create(std::vector<Button*>& buttons) 
{
    for (int butt = 0; butt < 5; butt++)
        buttons.push_back(new ButtonRect(sf::Vector2f(300 + butt * 240, 500), sf::Vector2f(180, 60), "images/point.png", ""));
    buttons.push_back(new ButtonRect (sf::Vector2f(1450, 250), sf::Vector2f(200, 70), "images/arrow_.png", "")); //button_arrow_left);
    buttons.push_back(new ButtonRect (sf::Vector2f(1650, 250), sf::Vector2f(200, 70), "images/arrow.png", "")); //button_arrow_right);
    buttons.push_back(new ButtonCircle (sf::Vector2f(200, 100), 50, "images/light.png", "")); //button_light
    buttons.push_back(new ButtonCircle (sf::Vector2f(200, 300), 50,  "images/home.jpg",  "")); //button_home
    buttons.push_back(new ButtonCircle (sf::Vector2f(200, 500), 50, "images/power.png", "")); //button_power
    buttons.push_back(new ButtonCircle (sf::Vector2f(1750, 150), 60, "images/emergency.png", "")); //button_emergency

}