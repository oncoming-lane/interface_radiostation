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
#include "TxRxEth.h"

#include "config.h"

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

    sf::RenderWindow window(sf::VideoMode(resolution_x, resolution_y), "Interface Radiostation Project");
    window.setActive(false);

    Screen_main main_Screen(sf::Vector2f(left_border + button_offset, bottom_border),
                            sf::Vector2f(main_screen_width, main_screen_height), "assets/white.png", "Main Screen");

    std::vector<Button *> buttons;
    buttons_create(buttons);

    std::vector<std::string> texts;
    sf::Thread               ethernetThread(&ethernetListener, &texts);
    ethernetThread.launch();

    sf::Font font;
    font.loadFromFile("assets/troika.otf");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {  // Button is pressed -> Sending command
                for (const auto &button : buttons)
                    if (button->isMouseOver(window))
                        transmit_eth(button->m_command);
            }

            window.clear(sf::Color::Black);
            main_Screen.draw(window);

            for (const auto &button : buttons)
                button->draw(window);

            for (size_t i = 0; i < texts.size(); i++) {
                sf::Text text(texts[i], font);
                text.setPosition(450 + i * 100, 300);
                text.setFillColor(sf::Color::Black);
                window.draw(text);
            }
            window.display();
        }
    }

    for (auto &button : buttons)
        delete button;

    ethernetThread.terminate();

    return 0;
}