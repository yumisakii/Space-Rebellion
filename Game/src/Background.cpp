#include "Background.h"

ParallaxLayer::ParallaxLayer(const sf::Texture& texture, float layerSpeed, const sf::Vector2f& scale)
    : sprite(texture), spriteCopy(texture), speed(layerSpeed) {
    // Positionner le premier sprite à 0
    sprite.setPosition(0, 0);

    // Positionner le deuxième sprite à la fin du premier
    spriteCopy.setPosition(sprite.getGlobalBounds().width, 0);

    // Appliquer le scale
    sprite.setScale(scale);
    spriteCopy.setScale(scale);
}

void ParallaxLayer::update(float deltaTime) {
    // Déplacer les sprites
    sprite.move(-speed * deltaTime, 0);
    spriteCopy.move(-speed * deltaTime, 0);

    // Si le premier sprite dépasse la fenêtre à gauche, repositionner
    if (sprite.getPosition().x + sprite.getGlobalBounds().width < 0) {
        sprite.setPosition(spriteCopy.getPosition().x + spriteCopy.getGlobalBounds().width, sprite.getPosition().y);
    }

    // Si le deuxième sprite dépasse la fenêtre à gauche, repositionner
    if (spriteCopy.getPosition().x + spriteCopy.getGlobalBounds().width < 0) {
        spriteCopy.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width, spriteCopy.getPosition().y);
    }
}

void ParallaxLayer::draw(sf::RenderWindow& window) {
    // Dessiner les deux sprites
    window.draw(sprite);
    window.draw(spriteCopy);
}

void updateBg(float deltaTime, ParallaxLayer& layer1, ParallaxLayer& layer2, ParallaxLayer& layer3) {
    layer1.update(deltaTime);
    layer2.update(deltaTime);
    layer3.update(deltaTime);
}

void drawBg(sf::RenderWindow& window, ParallaxLayer& layer1, ParallaxLayer& layer2, ParallaxLayer& layer3) {
    layer3.draw(window);
    layer2.draw(window);
    layer1.draw(window);
}

