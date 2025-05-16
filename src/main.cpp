#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include "button.hpp"
#include "Player.hpp"

using json = nlohmann::json;

int main() {
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "DogQuest");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("/Users/sequoiaboubionmckay/Desktop/DogQuest/Assets/Fonts/SilkscreenRegular.ttf")) {
        std::cerr << "Error: Could not load font!\n";
        return -1;
    }

    std::ifstream file("/Users/sequoiaboubionmckay/Desktop/DogQuest/data/story_graph.json");
    json story;
    file >> story;

    Player player("Rufus");

    std::string currentSentence = "Kenny Vo Presents: Dog Quest";
    sf::Text storyText(font, currentSentence, 25);
    storyText.setFillColor(sf::Color::White);
    storyText.setPosition(sf::Vector2f(50.f, 300.f));

    sf::Texture backgroundTexture;
    std::string introImagePath = story["intro_menu"]["image"].get<std::string>();
    if (!backgroundTexture.loadFromFile(introImagePath)) {
        std::cerr << "Failed to load intro image: " << introImagePath << "\n";
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    std::vector<Button> choiceButtons;
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
                            const auto& choice = choices[i];
                            bool passedCheck = true;

                            if (choice.contains("requirement")) {
                                std::string stat = choice["requirement"]["stat"];
                                int value = choice["requirement"]["value"];
                                passedCheck = player.performSkillCheck(stat, value);
                            }

                            if (passedCheck) {
                                std::string nextNode = choice["next"];
                                player.setCurrentNode(nextNode);
                                currentSentence = story[nextNode]["sentence"];
                                storyText.setString(currentSentence);

                                if (story[nextNode].contains("image")) {
                                    std::string imagePath = story[nextNode]["image"].get<std::string>();
                                    if (!backgroundTexture.loadFromFile(imagePath)) {
                                        std::cerr << "Failed to load image: " << imagePath << "\n";
                                    }
                                    backgroundSprite.setTexture(backgroundTexture);
                                }

                                choiceButtons.clear();
                                float yOffset = 700.f;
                                for (const auto& newChoice : story[nextNode]["choices"]) {
                                    Button btn(font, newChoice["text"], {500, 50}, {550, yOffset});
                                    choiceButtons.push_back(btn);
                                    yOffset += 60.f;
                                }
                            } else if (choice.contains("failText")) {
                                storyText.setString(choice["failText"].get<std::string>());
                            }
                            break;
                        }
                    }
                }

                if (!storyStarted && continueButton.isClicked(mousePos)) {
                    std::string nodeId = player.getCurrentNode();
                    currentSentence = story[nodeId]["sentence"];
                    storyText.setString(currentSentence);
                    storyStarted = true;

                    if (story[nodeId].contains("image")) {
                        std::string imagePath = story[nodeId]["image"].get<std::string>();
                        if (!backgroundTexture.loadFromFile(imagePath)) {
                            std::cerr << "Failed to load image: " << imagePath << "\n";
                        }
                        backgroundSprite.setTexture(backgroundTexture);
                    }

                    choiceButtons.clear();
                    float yOffset = 700.f;
                    for (const auto& choice : story[nodeId]["choices"]) {
                        Button btn(font, choice["text"], {500, 50}, {500, yOffset});
                        choiceButtons.push_back(btn);
                        yOffset += 60.f;
                    }
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
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