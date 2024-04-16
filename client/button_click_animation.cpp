#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Button Animation");

    // Создание кнопки
    sf::RectangleShape button(sf::Vector2f(200, 100));
    button.setFillColor(sf::Color::Blue);
    button.setPosition(300, 250);

    // Исходные размеры кнопки
    sf::Vector2f initialSize = button.getSize();
    // Уменьшенные размеры кнопки при нажатии
    sf::Vector2f pressedSize(180, 80);

    bool isPressed = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Обработка нажатия и отпускания кнопки мыши
            if (event.type == sf::Event::MouseButtonPressed) {
                if (button.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    // Если кнопка нажата, начать анимацию уменьшения
                    isPressed = true;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                // Если кнопка отпущена, начать анимацию увеличения
                isPressed = false;
            }
        }

        // Обновление размеров кнопки в зависимости от того, нажата ли она
        if (isPressed) {
            button.setSize(button.getSize() - sf::Vector2f(2, 2)); // Уменьшение размера
        } else {
            button.setSize(button.getSize() + sf::Vector2f(2, 2)); // Увеличение размера
        }

        // Ограничение размеров кнопки, чтобы она не становилась слишком маленькой или слишком большой
        if (button.getSize().x < pressedSize.x)
            button.setSize(pressedSize);
        else if (button.getSize().x > initialSize.x)
            button.setSize(initialSize);

        window.clear();
        window.draw(button);
        window.display();
    }

    return 0;
}

