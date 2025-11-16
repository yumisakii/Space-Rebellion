#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class InputManager
{
    static InputManager* instance_;

public:
    InputManager() {}

    static InputManager* instance();

    bool handleInputKeyboard(sf::Keyboard::Key key) const;
    bool handleInputMouse(sf::Mouse::Button button) const;
};