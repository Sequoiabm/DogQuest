#pragma once
#include <string>
#include <unordered_map>

class Player {
public:
    Player(const std::string& name); // constructor with name

    // Access and update current node
    void setCurrentNode(const std::string& nodeId);
    const std::string& getCurrentNode() const;

    // Access player name
    const std::string& getName() const;

    // Skill check function
    bool performSkillCheck(const std::string& skillType, int threshold) const;

    // Save/load later
    std::unordered_map<std::string, int> skills;
    

private:
    std::string currentNode;
    std::string playerName;
};