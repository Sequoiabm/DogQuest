#include "../headerFiles/button.hpp"

Button::Button(const sf::Font& font, const std::string& text, sf::Vector2f size, sf::Vector2f position)
    : label(font, text, 20)  // <-- this line initializes label properly
{
    shape.setSize(size);
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(position);

    label.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = label.getLocalBounds();
    label.setPosition(
        sf::Vector2f(
            position.x + (size.x - textBounds.size.x) / 2 - textBounds.position.x,
            position.y + (size.y - textBounds.size.y) / 2 - textBounds.position.y
        )
    );
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(label);
}

bool Button::isClicked(sf::Vector2f mousePos) const {
    return shape.getGlobalBounds().contains(mousePos);
}