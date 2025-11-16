#include <SFML/Audio.hpp>
#include "Entity.h"
#include "playerEntity.h"
#include "mobEntity.h"
#include "projectilesEntities.h"
#include "vfx.h"
//#define _USE_MATH_DEFINES // ki a mis ça ? jsp a quoi ça sert  // tqt je l'avais mis pour avoie pie mais sa marche pas donc j'ai fait a la mano // ah ok cool

extern std::shared_ptr<VFXSprite> vfxSprite;

bool Being::loadImageEntities(const std::string& filePath) {

    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Erreur de chargement de l'image ! " << std::endl;
        return false;
    }
    sprite.setTexture(texture);
    return true;

}


void Being::drawImageEntities(sf::RenderWindow& window, float x, float y) {

    if (texture.getSize().x == 0 || texture.getSize().y == 0) {
        std::cerr << "Erreur : La texture ne charge pas correctement." << std::endl;
        return;
    }

    // Calcul de l'échelle à partir de la taille cible
    sprite.setScale(getWidth_() / texture.getSize().x, getHeight_() / texture.getSize().y);
    sprite.setPosition(x, y);
    window.draw(sprite);

}

void Being::takeDmg(float damage) {
    if (invTime() <= 0) {
        setHP(hp() - damage);
        resetInvTime();
    }
    if (areTheBoss && hp() <= 0) {
        Menu::getInstance().setVictory(true);
    }
    if (hp() <= 0) {
        die();
        if (this->getType() != Being::BULLET && this->getType() != Being::COLLECTIBLE) {
            vfxSprite->addEffect(sf::Vector2f(x(), y()));

            if (this->getType() != Being::PLAYER && this->getType() != Being::METEOR) {
                auto player = Player::getInstance();
                if (areTheBoss) {
                    auto player = Player::getInstance();
                    player->addScore(500);
                }
                else {
                    player->addScore(100);
                }
            }
        }
    }
}
void Being::setAreTheBoss() {
    areTheBoss = true; 
    theBossJustSpawn = true;
}

void Being::updateInvTime(double deltaTime) {
    if (invTime() > 0) {
        setInvTime(invTime() - deltaTime);
    }
}

void Being::checkCollision(std::shared_ptr<Being> being1, std::shared_ptr<Being> being2) {
    sf::FloatRect rect1(x(), y(), width_, height_);
    sf::FloatRect rect2(being2->x(), being2->y(), being2->width_, being2->height_);

    if (rect1.intersects(rect2)) {
        this->getHit(being2);
        being2->getHit(being1);
    }

}