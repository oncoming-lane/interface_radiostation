#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "buttons.h"
#include "screen.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(1900, 700), "Example", sf::Style::Default);
    
    //screen
    Screen main_screen(sf::Vector2f(300, 70), sf::Vector2f(1150, 350), "images/white.png", "Hello, world!");

    //rect buttons
    std::vector<ButtonRect*> buttons_bottom;    
    for (int butt = 0; butt < 5; butt++)
        buttons_bottom.push_back(new ButtonRect(sf::Vector2f(300 + butt * 240, 500), sf::Vector2f(180, 60), "images/point.png", ""));

    ButtonRect button_arrow_left( sf::Vector2f(1450, 250), sf::Vector2f(200, 70), "images/arrow.png", "");
    ButtonRect button_arrow_right(sf::Vector2f(1650, 250), sf::Vector2f(200, 70), "images/arrow.png", "");

    bottons_create();

    //circle buttons
    ButtonCircle button_light(sf::Vector2f(200, 100), 50, "images/light.png", "");
    ButtonCircle button_home(sf::Vector2f(200, 300), 50,  "images/home.jpg",      "");
    ButtonCircle button_power(sf::Vector2f(200, 500), 50, "images/power.png", "");

    ButtonCircle button_emergency(sf::Vector2f(1750, 150), 60, "images/emergency.png", "");


    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                    
                for (int butt = 0; butt < buttons_bottom.size(); butt++)
                    if (buttons_bottom[butt]->isMouseOver(window))
                        std::cout << "bottom" << butt + 1 << " clicked!" << std::endl;
                if (button_light.isMouseOver(window)) 
                    std::cout << "Light" << std::endl;
                if (button_home.isMouseOver(window)) 
                    std::cout << "Home" << std::endl;
                if (button_power.isMouseOver(window)) 
                    std::cout << "Power" << std::endl;
                if (button_emergency.isMouseOver(window)) 
                    std::cout << "Emergency" << std::endl;

                if (button_arrow_left.isMouseOver(window)) 
                    std::cout << "Left" << std::endl;
                if (button_arrow_right.isMouseOver(window)) 
                    std::cout << "Right" << std::endl;

                button_home.change_color(window, 3);
            }
        }

        window.clear(sf::Color::Black);

        for (int butt = 0; butt < buttons_bottom.size(); butt++)
            buttons_bottom[butt]->draw(window);

        button_light.draw(window);
        button_home.draw(window);
        button_power.draw(window);
        button_emergency.draw(window);
        
        button_arrow_left.draw(window);
        button_arrow_right.draw(window);


        main_screen.draw(window);

        window.display();
    }

    for (int butt = 0; butt < buttons_bottom.size(); butt++)
        delete buttons_bottom[butt];

    return 0;
}