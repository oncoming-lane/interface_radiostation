#pragma once

#include <iostream>
#include <string>

#include <math.h>
#include <SFML/Graphics.hpp>

#include "config.h"

class Button {  // TODO: Transfer all class functions realisations to buttons.cpp
public:
    Button(sf::Vector2f position, std::string texturePath, std::string command, std::string text):
            m_command(command), m_position(position), m_text(text) {
        m_texture.loadFromFile(texturePath);
        m_font.loadFromFile("assets/troika.otf");
        m_buttonText.setFont(m_font);
        m_buttonText.setString(text);
        m_buttonText.setCharacterSize(button_text_size);
        m_buttonText.setFillColor(sf::Color::White);
    }

    std::string m_command;

    virtual ~Button() {}

    virtual void draw(sf::RenderWindow &window) = 0;

    virtual bool isMouseOver(sf::RenderWindow &window) = 0;

    virtual void change_color(int color_num) = 0;

protected:
    sf::Vector2f m_position;
    sf::Text     m_buttonText;
    sf::Font     m_font;
    sf::Texture  m_texture;
    std::string  m_text;
};

class ButtonCircle : public Button {
public:
    ButtonCircle(sf::Vector2f position, float radius, std::string texturePath, std::string command, std::string text):
            Button(position, texturePath, command, text), m_radius(radius) {
        m_circle.setRadius(radius);
        m_circle.setPosition(position);
        m_circle.setTexture(&m_texture);
        m_buttonText.setPosition(position.x - button_text_size / 2, position.y - button_text_size / 2);
        m_circle.setOrigin(radius, radius);
    }

    void draw(sf::RenderWindow &window) override {
        window.draw(m_circle);
        window.draw(m_buttonText);
    }

    bool isMouseOver(sf::RenderWindow &window) override {
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
        float        distance = std::sqrt(std::pow(mousePos.x - m_position.x, 2) + std::pow(mousePos.y - m_position.y, 2));

        if (distance <= m_radius) {
            change_color(2);

            return true;
        }

        return false;
    }

    void change_color(int color_num) {
        switch (color_num) {
            case 1: {
                m_circle.setFillColor(sf::Color::Green);
                break;
            }
            case 2: {
                m_circle.setFillColor(sf::Color::Red);
                break;
            }
            case 3: {
                m_circle.setFillColor(sf::Color::Blue);
                break;
            }
            case 4: {
                m_circle.setFillColor(sf::Color::Magenta);
                break;
            }
            case 5: {
                m_circle.setFillColor(sf::Color::Cyan);
                break;
            }
            case 6: {
                m_circle.setFillColor(sf::Color::Yellow);
                break;
            }
            default: {
                m_circle.setFillColor(sf::Color::White);
            }
        }
    }

private:
    sf::CircleShape m_circle;
    float           m_radius;
};

void buttons_create(std::vector<Button *> &buttons);