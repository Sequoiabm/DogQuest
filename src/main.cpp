#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include "button.hpp"
#include "Player.hpp"

using json = nlohmann::json;

int main() {

    // render the window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "DogQuest");
    window.setFramerateLimit(60);

    // Load font
    sf::Font font;
    if (!font.openFromFile("/Users/sequoiaboubionmckay/Desktop/DogQuest/Assets/Fonts/SilkscreenRegular.ttf")) {
        std::cerr << "Error: Could not load font!\n";
        return -1;
    }

    // Load story from JSON file
    std::ifstream file("/Users/sequoiaboubionmckay/Desktop/DogQuest/data/story_graph.json");
    json story;
    file >> story;

    // Create player
    Player player("Rufus");

    // Initial message
    std::string currentSentence = "Kenny Vo Presents: Dog Quest";
    sf::Text storyText(font, currentSentence, 25);
    storyText.setFillColor(sf::Color::White);
    storyText.setPosition(sf::Vector2f(50.f, 300.f));

    // create a button vector
    std:: vector<Button> choiceButtons; 

    // Button to continue/start
    Button continueButton(font, "Continue", {200, 50}, {300, 450});
    bool storyStarted = false;

    while (window.isOpen()) {
        if (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::MouseButtonPressed>()) {
                const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>();
                sf::Vector2f mousePos(static_cast<float>(mouse->position.x), static_cast<float>(mouse->position.y));

                if (storyStarted) {
                    const auto& choices = story[player.getCurrentNode()]["choices"];
                    for (std::size_t i = 0; i < choiceButtons.size(); ++i) {
                        if (choiceButtons[i].isClicked(mousePos)) {
                            std::string nextNode = choices[i]["next"];
                            player.setCurrentNode(nextNode);
                            currentSentence = story[nextNode]["sentence"];
                            storyText.setString(currentSentence);

                            // Regenerate buttons
                            const auto& newChoices = story[nextNode]["choices"];
                            choiceButtons.clear();
                            float yOffset = 400.f;
                            for (const auto& choice : newChoices) {
                                Button btn(font, choice["text"], {400, 50}, {200, yOffset});
                                choiceButtons.push_back(btn);
                                yOffset += 60.f;
                            }
                            break;
                        }
                    }
                }

                if (continueButton.isClicked(mousePos)) {
                    if (!storyStarted) {
                        // Show the first real story sentence
                        currentSentence = story[player.getCurrentNode()]["sentence"];
                        storyText.setString(currentSentence);
                        storyStarted = true;

                        // Generate buttons for each choice in the current node
                        const auto& choices = story[player.getCurrentNode()]["choices"];
                        choiceButtons.clear();
                        float yOffset = 400.f;
                        for (const auto& choice : choices) {
                            Button btn(font, choice["text"], {400, 50}, {200, yOffset});
                            choiceButtons.push_back(btn);
                            yOffset += 60.f;
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(storyText);
        if (!storyStarted) {
            continueButton.draw(window);
        } else {
            for (auto& btn : choiceButtons) {
                btn.draw(window);
            }
        }
        window.display();
    }

    return 0;
}