cmake_minimum_required(VERSION 3.10)
project(DogQuest VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add all source files
add_executable(DogQuest 
        src/main.cpp 
        src/button.cpp
        src/Player.cpp)

# Include paths
target_include_directories(DogQuest PRIVATE
    ${CMAKE_SOURCE_DIR}/headerFiles
    /opt/homebrew/include
)

# Link SFML manually
target_link_libraries(DogQuest
    /opt/homebrew/lib/libsfml-graphics.dylib
    /opt/homebrew/lib/libsfml-window.dylib
    /opt/homebrew/lib/libsfml-system.dylib
    /opt/homebrew/lib/libsfml-audio.dylib
    /opt/homebrew/lib/libsfml-network.dylib
)