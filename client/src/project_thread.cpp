#include <vector>
#include <map>
#include <thread>
#include <iostream>
#include <functional>
#include <atomic>

#include <X11/Xlib.h>
#undef None

#include "buttons.h"
#include "screen.h"
#include "message.h"
#include "TxRx.h"
#include "TxRxEth.h"

//словарь команд!
std::map<std::string, std::string> commands = {
    // push up long      push up short     push down
    {"0", "\x05\x83\x02\x57\x7A"},  // 05 83 01 57 C1    05 83 02 57 7A    05 83 00 57 A8
    {"1", "\x05\x89\x02\x57\x24"},  // 05 89 01 57 9F    05 89 02 57 24    05 89 00 57 F6
    {"2", "\x05\x84\x02\x57\xB5"},  // 05 84 01 57 0E    05 84 02 57 B5    05 84 02 57 67
    {"3", "\x05\x8A\x02\x57\xB4"},  // 05 8A 01 57 0F    05 8A 02 57 B4    05 8A 00 57 66
    {"4", "\x05\x85\x02\x57\xC5"},  // 05 85 01 57 7E    05 85 02 57 C5    05 85 00 57 17

    {"7", "\x05\x54\x01\x57\xA4"},   // 05 54 01 57 A4                                            button_light
    {"8", "\x05\x81\x01\x57\x21"},   // 05 81 01 57 21                                            button_home
    {"9", "\x05\x84\x02\x57\xB5"},   // button_power
    {"10", "\x05\x94\x01\x57\xED"},  // 05 94 01 57 ED                      05 94 00 57 84        button_emergency

    {"5", "\x05\x04\x01\x57\xF5"},  // 05 04 01 57 F5                                            button_arrow_left
    {"6", "\x05\x04\xFF\x57\xCC"}   // 05 04 FF 57 CC                                            button_arrow_right
};

bool __listener_thread_running = true;

// Функция прослушивания Ethernet соединения
void ethernetListener(std::vector<std::string> *texts) {
    while (__listener_thread_running) {
        std::string data = receive_eth();
        std::cout << "[RECEIVE]: {" << data << std::endl;
        message(data, texts);
        std::cout << "}\n\n";
        std::cout << data << "\n";
        std::cout << texts << "\n";
    }
}

int main() {
    XInitThreads();

    sf::RenderWindow window(sf::VideoMode(1900, 700), "Interface Radiostation Project");
    window.setActive(false);

    // Создание экрана
    Screen_main main_Screen(sf::Vector2f(300, 70), sf::Vector2f(1150, 350), "assets/white.png", "Main Screen");

    // Создание кнопок
    std::vector<Button *> buttons;
    buttons_create(buttons);

    // Создание потока для прослушивания Ethernet соединения
    std::vector<std::string> texts;
    sf::Thread               ethernetThread(&ethernetListener, &texts);
    ethernetThread.launch();

    sf::Font font;
    font.loadFromFile("assets/troika.otf");

    // Основной цикл программы
    while (window.isOpen()) {
        // Обработка событий окна и кнопок
        sf::Event event;
        while (window.pollEvent(event))  // Обработка событий окна
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {  //кнопка нажата - отправка команды
                for (size_t butt = 0; butt < buttons.size(); butt++)
                    if (buttons[butt]->isMouseOver(window)) {
                        transmit_eth(commands[std::to_string(butt)]);

                        if (butt == 7)
                            std::cout << "[INFO]: Color change\n";
                    }
            }

            window.clear(sf::Color::Black);
            main_Screen.draw(window);

            for (size_t butt = 0; butt < buttons.size(); butt++)
                buttons[butt]->draw(window);

            for (size_t i = 0; i < texts.size(); i++) {
                sf::Text text(texts[i], font);
                text.setPosition(450 + i * 100, 300);
                text.setFillColor(sf::Color::Black);
                window.draw(text);
            }

            window.display();
        }
    }

    // Освобождение памяти выделенной для кнопок
    for (auto button : buttons)
        delete button;

    // Остановка потока
    ethernetThread.terminate();

    return 0;
}