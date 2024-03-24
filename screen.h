#include <iostream>
#include <string>

#include <math.h>   
#include <SFML/Graphics.hpp>

class Screen{
public:
    Screen(sf::Vector2f position, sf::Vector2f size, std::string texturePath, std::string text):
         m_position(position), m_size(size), m_text(text) {
        
        m_texture.loadFromFile(texturePath);
        m_rectangle.setSize(size);
        m_rectangle.setPosition(position);
        m_buttonText.setFillColor(sf::Color::White);
        m_rectangle.setTexture(&m_texture);
        m_font.loadFromFile("troika.otf");
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


private:
    sf::RectangleShape m_rectangle;
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    sf::Text m_buttonText;
    sf::Font m_font;
    std::string m_text;
    sf::Texture m_texture;
};