#include "projectilesEntities.h"

Bullet::Bullet() { type = beingType::BULLET;}

void Bullet::setVelocity(double velocityx, double velocityy) {
    velocity_.x = velocityx; velocity_.y = velocityy;
}

void Bullet::setBulletType(int newBulletType) {
    bulletType = newBulletType;
}

void Bullet::updatePosition(sf::RenderWindow& window, double deltaTime) {
    setX(x() + velocity().x * deltaTime);
    setY(y() + velocity().y * deltaTime);

    // Verification apres mise a jour
    int windowWidth = window.getSize().x;
    int windowHeight = window.getSize().y;

    if (x() < 0.0f) die();
    if (x() + getWidth_() > windowWidth)  die();
    if (y() < 0.0f)  die();
    if (y() + getHeight_() > windowHeight)  die();
}

void Bullet::draw(sf::RenderWindow& window) {
    drawImageEntities(window, x(), y());
}

void Bullet::update(sf::RenderWindow& window, double deltaTime) {
    updatePosition(window, deltaTime);
}

void Bullet::explode() {
    double x = this->x() - 20; // Ajustement si necessaire
    double y = this->y() - 20;

    int numBullets = 8; // Nombre de balles
    double speed = 500; // Vitesse de la balle

    for (int i = 0; i < numBullets; i++) {
        double angle = (2 * 3.14159265358979323846 / numBullets) * i;
        double velX = speed * cos(angle);
        double velY = speed * sin(angle);
        createBullet(x, y, velX, velY, Bullet::MOB);
    }
}

void Bullet::getHit(std::shared_ptr<Being> object) {
    if (object->getType() == Being::PLAYER) {
        if (this->getTarget() == PLAYER || this->getTarget() == ALL) {
            this->takeDmg(1);
        }
    }
    else if (object->getType() == Being::MOB) {
        if (this->getTarget() == MOB || this->getTarget() == ALL) {
            this->takeDmg(1);
            if (this->getBulletType() == 1) {
                this->explode();
            }
        }
    }
    else if (object->getType() == Being::METEOR) {
        this->takeDmg(1);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Meteor::Meteor() { type = beingType::METEOR; }

void Meteor::setVelocity(double velX, double velY) {
    velocity_.x = velX; velocity_.y = velY;
}

void Meteor::updatePosition(sf::RenderWindow& window, double deltaTime) {
    setX(x() + velocity().x * deltaTime);
    setY(y() + velocity().y * deltaTime);

    int windowWidth = window.getSize().x;
    int windowHeight = window.getSize().y;

    if (x() < 0.0f) die();
    if (x() + getWidth_() > windowWidth)  die();
    if (y() < 0.0f)  die();
    if (y() + getHeight_() > windowHeight)  die();
}

void Meteor::update(sf::RenderWindow& window, double deltaTime) {
    updatePosition(window, deltaTime);
}

void Meteor::draw(sf::RenderWindow& window) {
    drawImageEntities(window, x(), y());
}


void Meteor::getHit(std::shared_ptr<Being>  object) {
    if (object->getType() == Being::BULLET) {
        this->takeDmg(1);
        
        if (this->hp() <= 0) {
            createCollectible(x() + (getWidth_()/2), y() + (getHeight_() / 2));
        }
    }
}


////////////////////////////////
MeteorSpawn::MeteorSpawn() {}

int MeteorSpawn::getMeteorSpawn() {
    return meteorSpawn;
}

void MeteorSpawn::setMeteorSpawn(int newMeteorSpawn) {
    meteorSpawn = newMeteorSpawn;
}
void MeteorSpawn::resetMeteorSpawn() {
    meteorSpawn = 20;
}