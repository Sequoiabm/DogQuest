#include "Player.hpp"

// Constructor initializes player's name, sets the starting node,
// and defines default values for skills
Player::Player(const std::string& name)
    : playerName(name), currentNode("kennel_start")
{
    skills["bark"] = 3;
    skills["bite"] = 2;
    skills["smell"] = 1;
}

// Returns the player's name
const std::string& Player::getName() const {
    return playerName;
}

// Returns the current story node the player is on
const std::string& Player::getCurrentNode() const {
    return currentNode;
}

// Set current node function
void Player::setCurrentNode(const std::string& nodeId) {
    currentNode = nodeId;
}

// Performs a skill check: returns true if the player's skill meets or exceeds the threshold
bool Player::performSkillCheck(const std::string& skillType, int threshold) const {
    auto it = skills.find(skillType);
    if (it != skills.end()) {
        return it->second >= threshold;
    }
    return false;
}