#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "DogQuest");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("/System/Library/Fonts/Helvetica.ttc")) {
        std::cerr << "Error: Could not load font!\n";
        return -1;
    }

    sf::Text welcomeText(font, "Welcome to Dog Quest!", 30);
    welcomeText.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = welcomeText.getLocalBounds();
    welcomeText.setPosition({
        (window.getSize().x - textBounds.size.x) / 2,
        (window.getSize().y - textBounds.size.y) / 2 - textBounds.position.y
    });

    while (window.isOpen()) {
        if (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(welcomeText);
        window.display();
    }

    return 0;
}