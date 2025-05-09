#pragma once

#include <SFML/Graphics.hpp>

class Button {
public:
    Button(const sf::Font& font, const std::string& text, sf::Vector2f size, sf::Vector2f position);

    void draw(sf::RenderWindow& window);
    bool isClicked(sf::Vector2f mousePos) const;

private:
    sf::RectangleShape shape;
    sf::Text label;
};