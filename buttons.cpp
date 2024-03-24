#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "buttons.h"


void bottons_create() {
    ButtonRect button_arrow_left( sf::Vector2f(1450, 250), sf::Vector2f(200, 70), "images/arrow.png", "");
    ButtonRect button_arrow_right(sf::Vector2f(1650, 250), sf::Vector2f(200, 70), "images/arrow.png", "");

    ButtonCircle button_light(sf::Vector2f(200, 100), 50, "images/light.png", "");
    ButtonCircle button_home(sf::Vector2f(200, 300), 50,  "images/home.jpg",      "");
    ButtonCircle button_power(sf::Vector2f(200, 500), 50, "images/power.png", "");
    ButtonCircle button_emergency(sf::Vector2f(1750, 150), 60, "images/emergency.png", "");
}
