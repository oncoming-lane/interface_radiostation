#include "buttons.h"


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