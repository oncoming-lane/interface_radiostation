
#include <vector>
#include <map>
#include <thread> 

#include <X11/Xlib.h>
#undef None

#include "buttons.h"
#include "screen.h"  
#include "message.h"     
#include "TxRx.h"
#include "TxRxEth.h"

std::vector <Button*> buttons;

// Функция прослушивания Ethernet соединения
void* ethernetListener(Screen_main* main_screen) 
{
    while (true) 
    {
        std::string data = receive_eth();
        std::cout << data << std::endl;
        message(data); // Функция обработки сообщения и вывода на экран 
        main_screen->change_text(data);
    }
    return NULL;
}


// Функция обработки нажатий кнопок
void* buttonListener(sf::RenderWindow& window, std::vector<Button*>& buttons) 
{
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
                return NULL;
            }
            if (event.type == sf::Event::MouseButtonPressed) 
            { //кнопка нажата - отправка команды
                for (int butt = 0; butt < buttons.size(); butt++)
                
                    if (buttons[butt]->isMouseOver(window))
                    {
                        transmit_eth(commands[std::to_string(butt)]);
                        if (butt == 7) 
                            std::cout << "change color" << std::endl;
                    }
            }
            // Обработка других событий кнопок...
        }
    }
    return NULL;
}



int main() 
{
    XInitThreads();
    sf::RenderWindow window(sf::VideoMode(1900, 700), "Interface Radiostation Project!!!");
    
    Screen_main main_Screen(sf::Vector2f(300, 70), sf::Vector2f(1150, 350), "images/white.png", "Screen_main!");

    buttons_create(buttons);

    // Создание потока для прослушивания Ethernet соединения
    std::thread ethernetThread(ethernetListener, &main_Screen);

    // Создание потока для обработки нажатий кнопок
    std::thread buttonThread(buttonListener, std::ref(window), std::ref(buttons));
    
    // Основной цикл программы
    while (window.isOpen()) 
    {
        // Обработка событий окна и кнопок
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            // Обработка событий окна
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
        } 
        window.clear(sf::Color::Black);
        main_Screen.draw(window);
        for (int butt = 0; butt < buttons.size(); butt++)
            buttons[butt]->draw(window);
      
        window.display();
    }   

    // Ожидание завершения потоков
    ethernetThread.join();
    buttonThread.join();

    // Освобождение памяти выделенной для кнопок
    for (auto button : buttons) 
        delete button;

    return 0;
}
