#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class ParallaxLayer {
public:
    // Constructeur avec la texture, la vitesse de défilement et le scale
    ParallaxLayer(const sf::Texture& texture, float layerSpeed, const sf::Vector2f& scale = sf::Vector2f(1.0f, 1.0f));

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite;
    sf::Sprite spriteCopy;
    float speed;
};

void updateBg(float deltaTime, ParallaxLayer& layer1, ParallaxLayer& layer2, ParallaxLayer& layer3);
void drawBg(sf::RenderWindow& window, ParallaxLayer& layer1, ParallaxLayer& layer2, ParallaxLayer& layer3);
