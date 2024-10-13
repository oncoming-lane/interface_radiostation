#pragma once

#include <iostream>
#include <string>

#include <math.h>
#include <SFML/Graphics.hpp>

class Screen_main {
public:
    Screen_main(sf::Vector2f position, sf::Vector2f size, std::string texturePath, std::string text):
            m_position(position), m_size(size), m_text(text) {
        m_texture.loadFromFile(texturePath);
        m_rectangle.setSize(size);
        m_rectangle.setPosition(position);
        m_screenText.setFillColor(sf::Color::White);
        m_rectangle.setTexture(&m_texture);
        m_font.loadFromFile("assets/troika.otf");
        m_screenText.setFont(m_font);
        m_screenText.setString(text);
        m_screenText.setCharacterSize(30);
        m_screenText.setFillColor(sf::Color::Black);
        m_screenText.setPosition(position.x, position.y);
        // m_screenText.setPosition(position.x + size.x / 3 - m_screenText.getLocalBounds().width / 3,
        //                          position.y + size.y / 3 - m_screenText.getLocalBounds().height / 3);
    }

    void change_text(std::string new_text, sf::Vector2f new_text_position) {
        m_screenText.setString(new_text);
        m_screenText.setPosition(new_text_position);
    }

    void draw(sf::RenderWindow &window) {
        window.draw(m_rectangle);
        window.draw(m_screenText);
    }

private:
    sf::RectangleShape m_rectangle;
    sf::Vector2f       m_position;
    sf::Vector2f       m_size;
    sf::Text           m_screenText;
    sf::Font           m_font;
    std::string        m_text;
    sf::Texture        m_texture;
};