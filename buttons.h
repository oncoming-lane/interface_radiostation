#pragma once

#include <iostream>
#include <string>

#include <math.h>   
#include <SFML/Graphics.hpp>

class ButtonRect {
public:
    ButtonRect(sf::Vector2f position, sf::Vector2f size, std::string texturePath, std::string text):
         m_position(position), m_size(size), m_text(text) {
        
        m_texture.loadFromFile(texturePath);
        m_rectangle.setSize(size);
        //m_rectangle.setFillColor(sf::Color::Green);
        m_rectangle.setPosition(position);
        m_rectangle.setTexture(&m_texture);
        m_font.loadFromFile("troika.otf");
        m_buttonText.setFont(m_font);
        m_buttonText.setString(text);
        m_buttonText.setCharacterSize(20);
        m_buttonText.setFillColor(sf::Color(127, 127, 127));
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

class ButtonCircle {
public:
    ButtonCircle(sf::Vector2f position, float radius, std::string texturePath, std::string text):
        m_position(position), m_radius(radius), m_text(text) {
        
        m_texture.loadFromFile(texturePath);
        m_circle.setRadius(radius);
        m_circle.setPosition(position);
        //m_circle.setFillColor(sf::Color::Green);
        m_circle.setTexture(&m_texture);
        m_font.loadFromFile("troika.otf");
        m_buttonText.setFont(m_font);
        m_buttonText.setString(text);
        m_buttonText.setCharacterSize(20);
        m_buttonText.setFillColor(sf::Color::White);
        m_buttonText.setPosition(position.x + radius / 3 - m_buttonText.getLocalBounds().width / 3, 
                                 position.y + radius / 3 - m_buttonText.getLocalBounds().height / 3);
        m_circle.setOrigin(radius, radius);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(m_circle);
        window.draw(m_buttonText);
    }

    void change_color(sf::RenderWindow& window, int color_num) {
        switch (color_num){
            case 1:{ m_circle.setFillColor(sf::Color::Green);  break; }
            case 2:{ m_circle.setFillColor(sf::Color::Red);  break; }
            case 3:{ m_circle.setFillColor(sf::Color::Blue);  break; }
            default: { m_circle.setFillColor(sf::Color::White); }
            
        } 
    
    }

    bool isMouseOver(sf::RenderWindow& window) {
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
        float distance = sqrt(pow(mousePos.x - m_position.x, 2) + pow(mousePos.y - m_position.y, 2));
        if (distance <= m_radius) {
            return true;
        }
        return false;
    }

private:
    sf::CircleShape m_circle;
    sf::Vector2f m_position;
    float m_radius;
    sf::Text m_buttonText;
    sf::Font m_font;
    std::string m_text;
    sf::Texture m_texture;
};





ButtonRect* bottons_create();