#include <SFML/Graphics.hpp>

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "DogQuest");
    window.setFramerateLimit(60);

    // Create a font
    sf::Font font;
    if (!font.openFromFile("/System/Library/Fonts/Helvetica.ttc")) {
        return -1; // Error loading font
    }

    // Create a text object
    sf::Text welcomeText(font, "Welcome to DogQuest!", 30);
    welcomeText.setFillColor(sf::Color::White);
    
    // Center the text
    sf::FloatRect textBounds = welcomeText.getLocalBounds();
    welcomeText.setPosition(
        (window.getSize().x - textBounds.width) / 2,
        (window.getSize().y - textBounds.height) / 2
    );

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        if (auto event = window.pollEvent()) {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw the text
        window.draw(welcomeText);

        // Display what we drew
        window.display();
    }

    return 0;
} 