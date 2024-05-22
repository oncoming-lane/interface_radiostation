#include <SFML/Graphics.hpp>
#include <iostream>

class Button {
public:
    Button(sf::Vector2f position, sf::Vector2f size, std::string texturePath, std::string text)
        : m_position(position), m_size(size), m_text(text) {
        
        m_texture.loadFromFile(texturePath);
        m_rectangle.setSize(size);
        m_rectangle.setPosition(position);
        m_rectangle.setTexture(&m_texture);

        m_font.loadFromFile("/home/alexey/Documents/Project/Times New Roman.ttf");
        m_buttonText.setFont(m_font);
        m_buttonText.setString(text);
        m_buttonText.setCharacterSize(20);
        m_buttonText.setFillColor(sf::Color::Black);
        m_buttonText.setPosition(position.x + size.x / 3 - m_buttonText.getLocalBounds().width / 3, 
                                  position.y + size.y / 3 - m_buttonText.getLocalBounds().height / 3);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(m_rectangle);
        window.draw(m_buttonText);
    }

    bool isMouseOver(sf::RenderWindow& window) {
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
        if (mousePos.x >= m_position.x && mousePos.x <= m_position.x + m_size.x &&
            mousePos.y >= m_position.y && mousePos.y <= m_position.y + m_size.y) {
            return true;
        }
        return false;
    }

private:
    sf::RectangleShape m_rectangle;
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    sf::Text m_buttonText;
    sf::Font m_font;
    std::string m_text;
    sf::Texture m_texture;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Button Example");

    Button button(sf::Vector2f(100, 100), sf::Vector2f(200, 50), "Button.jpg", "Click me!");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (button.isMouseOver(window)) {
                    std::cout << "Button clicked!" << std::endl;
                }
            }
        }

        window.clear(sf::Color::White);

        button.draw(window);

        window.display();
    }

    return 0;
}