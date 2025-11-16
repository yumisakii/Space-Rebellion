#include "input.h"

bool InputManager::handleInputKeyboard(sf::Keyboard::Key key) const
{
    return sf::Keyboard::isKeyPressed(key);
}

bool InputManager::handleInputMouse(sf::Mouse::Button button) const
{
    return sf::Mouse::isButtonPressed(button);
}


InputManager* InputManager::instance()
{
    static InputManager* instance = new InputManager();
    return instance;
}

