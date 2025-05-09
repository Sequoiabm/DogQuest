#include <SFML/Graphics.hpp>
#include <iostream>
#include <button.hpp>


int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "DogQuest");
    window.setFramerateLimit(60);

    // Load font
    sf::Font font;
    if (!font.openFromFile("/Users/sequoiaboubionmckay/Desktop/DogQuest/Assets/Fonts/SilkscreenRegular.ttf")) { // NOTE: Change PathName
        std::cerr << "Error: Could not load font!\n";
        return -1;
    }

    // generate button
    Button finishButton(font, "Finish", {200, 50}, {300, 450});

    sf::Text endText(font, "You are done with dog quest", 25);
    endText.setFillColor(sf::Color::Yellow);
    endText.setPosition(sf::Vector2f(220, 350));
    bool showEndText = false;



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

            if (event->is<sf::Event::MouseButtonPressed>()) {
                const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>();
                sf::Vector2f mousePos(static_cast<float>(mouse->position.x), static_cast<float>(mouse->position.y));
                if (finishButton.isClicked(mousePos)) {
                    showEndText = true;
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(welcomeText);
        finishButton.draw(window);
        if (showEndText) {
            window.draw(endText);
        }
        window.display();
    }

    return 0;
}