#include "collectibleEntity.h"

Collectible::Collectible() { type = beingType::COLLECTIBLE; }

void Collectible::setVelocity(double velX, double velY) {
    velocity_.x = velX; velocity_.y = velY;
}

void Collectible::updatePosition(sf::RenderWindow& window, double deltaTime) {
    setX(x() + velocity().x * deltaTime);
    setY(y() + velocity().y * deltaTime);

    int windowWidth = window.getSize().x;
    int windowHeight = window.getSize().y;

    if (x() < 0.0f) die();
    if (x() + getWidth_() > windowWidth)  die();
    if (y() < 0.0f)  die();
    if (y() + getHeight_() > windowHeight)  die();
}

void Collectible::update(sf::RenderWindow& window, double deltaTime) {
    updatePosition(window, deltaTime);
}

void Collectible::draw(sf::RenderWindow& window) {
    if (collectibleType == 0) {
        drawImageEntities(window, x(), y());
    }
    else if (collectibleType == 1) {
        drawImageEntities(window, x(), y());
    };
}


void Collectible::getHit(std::shared_ptr<Being>  object) {
    if (object->getType() == Being::PLAYER) {
        this->takeDmg(1);
    }
}

void Collectible::setCollectibleType(int newCollectibleType) {
    collectibleType = newCollectibleType;
    setInvincibilityTime(newCollectibleType);
}