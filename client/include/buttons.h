#pragma once

#include <iostream>
#include <string>

#include <math.h>   
#include <SFML/Graphics.hpp>




//extern int color_num;

class Button 
{
public:
    Button(sf::Vector2f position, std::string texturePath, std::string text):
        m_position(position), m_text(text) 
    {
        
        m_texture.loadFromFile(texturePath);
        m_font.loadFromFile("troika.otf");
        m_buttonText.setFont(m_font);
        m_buttonText.setString(text);
        m_buttonText.setCharacterSize(20);
        m_buttonText.setFillColor(sf::Color::White);
    }

    virtual void draw(sf::RenderWindow& window) = 0;

    virtual bool isMouseOver(sf::RenderWindow& window) = 0;

    virtual void change_color(sf::RenderWindow& window, int color_num) = 0;

protected:
    sf::Vector2f m_position;
    sf::Text m_buttonText;
    sf::Font m_font;
    std::string m_text;
    sf::Texture m_texture;
};

class ButtonRect : public Button 
{
public:
    ButtonRect(sf::Vector2f position, sf::Vector2f size, std::string texturePath, std::string text):
        Button(position, texturePath, text), m_size(size) 
    {
        
        m_rectangle.setSize(size);
        m_rectangle.setPosition(position);
        m_rectangle.setTexture(&m_texture);
        m_buttonText.setPosition(position.x + size.x / 3 - m_buttonText.getLocalBounds().width / 3, 
                                  position.y + size.y / 3 - m_buttonText.getLocalBounds().height / 3);
    }

    void draw(sf::RenderWindow& window) override 
    {
        window.draw(m_rectangle);
        window.draw(m_buttonText);
    }

    bool isMouseOver(sf::RenderWindow& window) override 
    {
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
        if (mousePos.x >= m_position.x && mousePos.x <= m_position.x + m_size.x &&
            mousePos.y >= m_position.y && mousePos.y <= m_position.y + m_size.y) 
                return true;
        return false;
    }

    void change_color(sf::RenderWindow& window, int color_num) 
    {
        switch (color_num)  
        {
            case 1:{ m_rectangle.setFillColor(sf::Color::Green);  break; }
            case 2:{ m_rectangle.setFillColor(sf::Color::Red);    break; }
            case 3:{ m_rectangle.setFillColor(sf::Color::Blue);   break; }
            case 4:{ m_rectangle.setFillColor(sf::Color::Magenta);   break; }
            case 5:{ m_rectangle.setFillColor(sf::Color::Cyan);   break; }
            case 6:{ m_rectangle.setFillColor(sf::Color::Yellow);   break; }
            default: { m_rectangle.setFillColor(sf::Color::White); }
            
        } 
    
    }



private:
    sf::RectangleShape m_rectangle;
    sf::Vector2f m_size;
};

class ButtonCircle : public Button 
{
public:
    ButtonCircle(sf::Vector2f position, float radius, std::string texturePath, std::string text):
                   Button(position, texturePath, text), m_radius(radius)  
    {    
        m_circle.setRadius(radius);
        m_circle.setPosition(position);
        m_circle.setTexture(&m_texture);
        m_buttonText.setPosition(position.x + radius / 3 - m_buttonText.getLocalBounds().width / 3, 
                                 position.y + radius / 3 - m_buttonText.getLocalBounds().height / 3);
        m_circle.setOrigin(radius, radius);
    }

    void draw(sf::RenderWindow& window) override 
    {
        window.draw(m_circle);
        window.draw(m_buttonText);
    }

    bool isMouseOver(sf::RenderWindow& window) override 
    {
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
        float distance = std::sqrt(std::pow(mousePos.x - m_position.x, 2) + std::pow(mousePos.y - m_position.y, 2));
        if (distance <= m_radius) 
            return true;
        return false;
    }

    void change_color(sf::RenderWindow& window, int color_num) 
    {
        switch (color_num)  
        {
            case 1:{ m_circle.setFillColor(sf::Color::Green);  break; }
            case 2:{ m_circle.setFillColor(sf::Color::Red);    break; }
            case 3:{ m_circle.setFillColor(sf::Color::Blue);   break; }
            case 4:{ m_circle.setFillColor(sf::Color::Magenta);   break; }
            case 5:{ m_circle.setFillColor(sf::Color::Cyan);   break; }
            case 6:{ m_circle.setFillColor(sf::Color::Yellow);   break; }
            default: { m_circle.setFillColor(sf::Color::White); }
            
        } 
    }


private:
    sf::CircleShape m_circle;
    float m_radius;
};


void buttons_create(std::vector<Button*>& buttons);