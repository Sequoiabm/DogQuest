cmake_minimum_required(VERSION 3.10)
project(DogQuest VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(DogQuest main.cpp)

# Set SFML paths
set(SFML_INCLUDE_DIR "/opt/homebrew/include")
set(SFML_LIB_DIR "/opt/homebrew/lib")

# Include directories
target_include_directories(DogQuest PRIVATE ${SFML_INCLUDE_DIR})

# Link SFML libraries
target_link_libraries(DogQuest
    ${SFML_LIB_DIR}/libsfml-graphics.dylib
    ${SFML_LIB_DIR}/libsfml-window.dylib
    ${SFML_LIB_DIR}/libsfml-system.dylib
) 