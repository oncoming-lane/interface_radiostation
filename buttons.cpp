#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "buttons.h"


ButtonRect* bottons_create() {

    std::vector <ButtonRect*> buttons_rect;    
    for (int butt = 0; butt < 5; butt++)
        buttons_rect.push_back(new ButtonRect(sf::Vector2f(300 + butt * 240, 500), sf::Vector2f(180, 60), "images/point.png", ""));

    buttons_rect.push_back(new ButtonRect (sf::Vector2f(1450, 250), sf::Vector2f(200, 70), "images/arrow.png", "")); //button_arrow_left_p
    buttons_rect.push_back(new ButtonRect (sf::Vector2f(1650, 250), sf::Vector2f(200, 70), "images/arrow.png", "")); //button_arrow_right_p

    //std::vector <ButtonCircle*> buttons_circle;    

    //buttons_circle.push_back(new ButtonCircle (sf::Vector2f(200, 100), 50, "images/light.png", "")); //button_light
    //buttons_circle.push_back(new ButtonRect (sf::Vector2f(1450, 250), sf::Vector2f(200, 70), "images/arrow.png", "")); //button_home_p
    //buttons_circle.push_back(new ButtonRect (sf::Vector2f(1450, 250), sf::Vector2f(200, 70), "images/arrow.png", "")); //button_power_p
    //buttons_circle.push_back(new ButtonRect (sf::Vector2f(1450, 250), sf::Vector2f(200, 70), "images/arrow.png", "")); //button_emergency_p


    //ButtonCircle (sf::Vector2f(200, 100), 50, "images/light.png", "");
    //ButtonCircle (sf::Vector2f(200, 300), 50,  "images/home.jpg",      "");
    //ButtonCircle (sf::Vector2f(200, 500), 50, "images/power.png", "");
    //ButtonCircle (sf::Vector2f(1750, 150), 60, "images/emergency.png", "");
    
    //return buttons_rect; 
}
