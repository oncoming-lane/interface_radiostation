#include <iostream>
#include <vector>
#include <map>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <errno.h>

#include <SFML/Graphics.hpp>

#include "buttons.h"
#include "screen.h"
#include "TxRx.h"
#include "TxRxEth.h"



int main() 
{
    sf::RenderWindow window(sf::VideoMode(1900, 700), "Interface Radiostation Project!!!", sf::Style::Default);
    
    //screen
    Screen_main main_screen(sf::Vector2f(300, 70), sf::Vector2f(1150, 350), "images/white.png", "SCREEN!");


    int color_choice = 0; //по дефолту - белый
    std::vector <ButtonRect*> buttons_bottom;    
    for (int butt = 0; butt < 5; butt++)
        buttons_bottom.push_back(new ButtonRect(sf::Vector2f(300 + butt * 240, 500), sf::Vector2f(180, 60), "images/point.png", ""));

    ButtonRect button_arrow_left( sf::Vector2f(1450, 250), sf::Vector2f(200, 70), "images/arrow_.png", "");
    ButtonRect button_arrow_right(sf::Vector2f(1650, 250), sf::Vector2f(200, 70), "images/arrow.png", "");
    
    //ButtonRect button_arrow_left, button_arrow_right = *bottons_create();

    ButtonCircle button_light(sf::Vector2f(200, 100), 50, "images/light.png", "");
    ButtonCircle button_home(sf::Vector2f(200, 300), 50,  "images/home.jpg",      "");
    ButtonCircle button_power(sf::Vector2f(200, 500), 50, "images/power.png", "");

    ButtonCircle button_emergency(sf::Vector2f(1750, 150), 60, "images/emergency.png", "");

    //словарь команд!
    std::map <std::string, std::string > commands = 
    {                                           //push up long      push up short     push down
        {"0", "\x05\x83\x02\x57\x7A"},          //05 83 01 57 C1    05 83 02 57 7A    05 83 00 57 A8
        {"1", "\x05\x89\x02\x57\x24"},          //05 89 01 57 9F    05 89 02 57 24    05 89 00 57 F6
        {"2", "\x05\x84\x02\x57\xB5"},          //05 84 01 57 0E    05 84 02 57 B5    05 84 02 57 67
        {"3", "\x05\x8A\x02\x57\xB4"},          //05 8A 01 57 0F    05 8A 02 57 B4    05 8A 00 57 66
        {"4", "\x05\x85\x02\x57\xC5"},          //05 85 01 57 7E    05 85 02 57 C5    05 85 00 57 17

        {"light", "\x05\x54\x01\x57\xA4"},      //05 54 01 57 A4
        {"home", "\x05\x81\x01\x57\x21"},       //05 81 01 57 21    
        {"power", "\x05\x84\x02\x57\xB5"},
        {"emergency", "\x05\x94\x01\x57\xED"},  //05 94 01 57 ED                      05 94 00 57 84

        {"left", "\x05\x04\x01\x57\xF5"},       //05 04 01 57 F5
        {"right", "\x05\x04\xFF\x57\xCC"}       //05 04 FF 57 CC
    };

   

    while (window.isOpen()) 
    {
        
        sf::Event event;
        receive_eth();
        
        //transmit_eth("START");

        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed){
                window.close();
                break;
            }
                

            if (event.type == sf::Event::MouseButtonPressed) 
            { //кнопка нажата - значит, будет отправка команды
                //find_ttyUSB_port();
                for (int butt = 0; butt < buttons_bottom.size(); butt++)
                    if (buttons_bottom[butt]->isMouseOver(window))
                        transmit_eth(commands[std::to_string(butt)]);

                if (button_light.isMouseOver(window))       color_choice++;
                //в силу ненадобности настройки яркости на самой станции заменим ее на смену цвета интерфейса

                if (button_home.isMouseOver(window))        transmit_eth(commands["home"]);
                if (button_power.isMouseOver(window))       transmit_eth(commands["power"]);
                if (button_emergency.isMouseOver(window))   transmit_eth(commands["light"]);

                if (button_arrow_left.isMouseOver(window))  transmit_eth(commands["left"]);
                if (button_arrow_right.isMouseOver(window)) transmit_eth(commands["right"]);
                    
            button_home.change_color(window, color_choice%4);
            button_light.change_color(window, color_choice%4);
            button_power.change_color(window, color_choice%4);
            button_arrow_left.change_color(window, color_choice%4);
            button_arrow_right.change_color(window, color_choice%4);
            
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

        
        //std::string str = receive_eth();

        //printf("%s", str);
        //std::cout << str << std::endl;
        //main_screen.change_text(str);
        
        main_screen.draw(window);
        
        window.display();

    }


    for (int butt = 0; butt < buttons_bottom.size(); butt++)
        delete buttons_bottom[butt];

    return 0;
}
