# DogQuest

A pixel-art, story-driven SFML adventure game where you’re a dog trying to survive, escape, and maybe even befriend others in a canine post-apocalyptic world.

## **🎮 Overview**

**DogQuest** is a C++/SFML-based interactive narrative game where your choices—and your skills—determine the story path. You begin locked in a kennel, and your journey unfolds through a branching story loaded from a JSON file, with choices, skill checks, and consequences.

## **🧠 How It Works**

### **Story System**

* **Written in JSON (**data/story_graph.json**)**
* Each story node includes:
  * A **sentence** to display
  * An **image** for the background
  * An array of **choices** (buttons)
  * Optional **requirement** (skill checks)
  * **failText** fallback if check fails

### **Gameplay Flow**

1. You launch into the **intro screen**
2. Clicking “Continue” starts the first story node
3. The background image and story text update based on JSON
4. You make choices that either:
   * Change the current node
   * Require a skill check
   * Lead to death or victory

## **✏️ Key Features**

✅ Text-based narrative via JSON

✅ SFML-rendered UI buttons

✅ Basic skill check system

✅ Dynamic background updates

✅ Supports 1920x1080 resolution

✅ Modular CMake project

## Prerequisites

- CMake (version 3.10 or higher)
- C++ compiler with C++17 support
- SFML 2.5 or higher

## Building the Project

1. Create a build directory:

```bash
mkdir build
cd build
```

2. Generate build files:

```bash
cmake ..
```

3. Build the project:

```bash
cmake --build .
```

4. Run the executable:

```bash
./DogQuest
```

## Development

## **✅ Current Features Implemented**

* Scene loading and rendering
* JSON-driven branching dialogue
* Buttons and mouse interaction
* Skill-based branching paths (bite, bark, etc.)
* Intro, death, and ending scenes
* Pause and resume menu scaffolding

## **🛠️ TODO / Roadmap**

| **Feature**          | **Status** |
| -------------------------- | ---------------- |
| Save/Load system           | ⏳ In Progress   |
| Character creation screen  | ⏳ In Progress   |
| Skill point allocator UI   | ⏳ In Progress   |
| Background music & SFX     | 🔜 Planned       |
| Story branching fixes      | 🔜 Planned       |
| More JSON flexibility      | 🔜 Planned       |
| Victory + multiple endings | 🔜 Planned       |

## **💡 Dev Notes**

* UI positioning is currently hardcoded but centered for 1920x1080
* Backgrounds scale to match the full screen
* Add new nodes or scenes to the **story_graph.json** file
* Story text is centered and displayed above buttons
* Each **.png** corresponds to a node or cutscene
