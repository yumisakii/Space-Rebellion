#include "playerEntity.h"
#include "projectilesEntities.h"
#include "Menu.h"
#include "Image.h"

std::shared_ptr<Player> Player::instance = nullptr;

Player::Player() : velocity_(0, 0) { type = beingType::PLAYER; }

void Player::inputDetection() {
    if (InputManager::instance()->handleInputKeyboard(sf::Keyboard::Z)) {
        setVelocity(velocity().x, -600);
    }
    if (InputManager::instance()->handleInputKeyboard(sf::Keyboard::Q)) {
        setVelocity(-1000, velocity().y);
    }
    if (InputManager::instance()->handleInputKeyboard(sf::Keyboard::S)) {
        setVelocity(velocity().x, 600);
    }
    if (InputManager::instance()->handleInputKeyboard(sf::Keyboard::D)) {
        setVelocity(750, velocity().y);
    }
    if (InputManager::instance()->handleInputKeyboard(sf::Keyboard::J) && !alwaysClick) {
        alwaysClick = true;
        shoot();
    }
    if (InputManager::instance()->handleInputKeyboard(sf::Keyboard::K)) {
        shootExplosive();
    }
 
    //si touche relachee
    if (!InputManager::instance()->handleInputKeyboard(sf::Keyboard::Z) &&
        !InputManager::instance()->handleInputKeyboard(sf::Keyboard::S)) {
        setVelocity(velocity().x, 0.0);
    }
    if (!InputManager::instance()->handleInputKeyboard(sf::Keyboard::Q) &&
        !InputManager::instance()->handleInputKeyboard(sf::Keyboard::D)) {
        setVelocity(0.0, velocity().y);
    }

    if (!InputManager::instance()->handleInputKeyboard(sf::Keyboard::J)) {
        alwaysClick = false;
    }
}

void Player::setVelocity(double velocityx, double velocityy) {
    velocity_.x = velocityx; velocity_.y = velocityy;
}

void Player::updatePosition(sf::RenderWindow& window, double deltaTime) {
    setX(x() + velocity().x * deltaTime);
    setY(y() + velocity().y * deltaTime);

    if (x() < 0.0f) setX(0.0f);
    if (x() + getWidth_() > window.getSize().x) setX(window.getSize().x - getWidth_());
    if (y() < 0.0f) setY(0.0f);
    if (y() + getHeight_() > window.getSize().y) setY(window.getSize().y - getHeight_());
}

void Player::draw(sf::RenderWindow& window) {

    drawImageEntities(window, x(), y());

    //DRAW HP JOUEUR
    drawDisplayHP(window);
    drawExplosiveBulletCD(window);
    drawPlayerScore(window);
}

void Player::atkSpeedHandler(double deltaTime) {
    if (getShootTimer() > 0) {
        setShootTimer(getShootTimer() - deltaTime);
    }
    if (getExplosionTimer() > 0) {
        setExplosionTimer(getExplosionTimer() - deltaTime);
    }
}

void Player::shoot() {
    if (getShootTimer() <= 0) {
        createBullet(x() + getWidth_(), y() + getHeight_() / 2, 1500, 0,Bullet::MOB);
        resetShootTimer();
    }
    audio.playSound("shoot");
}

void Player::shootExplosive() {
    if (getExplosionTimer() <= 0) {
        createExplosiveBullet(x() + getWidth_(), y() + getHeight_() / 2, 1500, 0);
        resetExplosionTimer();
    }
}

void Player::update(sf::RenderWindow& window, double deltaTime) {
    if (!isDead()) {
        inputDetection();
        updatePosition(window, deltaTime);
        updateInvTime(deltaTime);
        atkSpeedHandler(deltaTime);
    }
}

bool Player::loadImagePV(std::string filePath) {
    if (!texturePV.loadFromFile(filePath)) {
        std::cerr << "Erreur de chargement de l'image ! " << std::endl;
        return false;
    }
    return true;
}

//DISPLAY HP JOUEUR, FAIT UN VECTEUR CONTENANT DES RECTS ET DESSINANT DES RECTS BASER SUR LE NOMBRE DE HP
std::vector<sf::Sprite> Player::displayHP() {
    std::vector<sf::Sprite> hpBlocs;

    loadImagePV("Assets/UI_UX/batterie.png");

    int hpCount = hp();

    int gap = 80;

    for (int i = 0; i < hpCount; ++i) {

        spritePV.setTexture(texturePV);
        spritePV.setScale(getPVWidth() / texturePV.getSize().x, getPVHeight() / texturePV.getSize().y);
        spritePV.setPosition(i * gap, 10);

        hpBlocs.push_back(spritePV);
    }
    return hpBlocs;
}


void Player::getHit(std::shared_ptr<Being> object) {
    if (object->getType() == Being::MOB) {
        this->takeDmg(1);
    }
    else if (object->getType() == Being::BULLET) {
        std::shared_ptr<Bullet> bulletPtr = std::dynamic_pointer_cast<Bullet>(object);
        if (bulletPtr->getTarget() == 1 || !bulletPtr->getTarget()) {  // rappel: 1 si la cible est le joueur, 2 les monstres et 0 pour les deux
            this->takeDmg(1);
        }
    }
    else if (object->getType() == Being::METEOR) {
        this->takeDmg(1);
    }
    else if (object->getType() == Being::COLLECTIBLE) {
        if (object->invTime() == 0) { // invTime représente le type du collectible
            this->takeDmg(-1);
        }
        else {
            this->setExplosionTimer(0);
        }
    }
}

//Fonction pour display UI HP
void Player::drawDisplayHP(sf::RenderWindow& window) {
    std::vector<sf::Sprite> hpBlocs = displayHP();
    for (const auto& block : hpBlocs) {

        window.draw(block);
    }
}

void Player::drawTextOnTheScren(sf::RenderWindow& window, const std::string& text, int fontSize, float x, float y) {
    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(fontSize);
    sfText.setPosition(x, y);
    window.draw(sfText);
}

void Player::drawExplosiveBulletCD(sf::RenderWindow& window) {
    int intCD = static_cast<int>(getExplosionTimer());
    std::string cooldown = std::to_string(intCD);
    drawTextOnTheScren(window, cooldown, 45, 100, window.getSize().y - 200);
}

void Player::loadFont() {
    font.loadFromFile("Assets/Fonts/SourGummy-LightItalic.ttf");
}

void Player::addScore(int addValue) {
    score += addValue;
}

void Player::drawPlayerScore(sf::RenderWindow& window) {
    std::string displayScore = "Score : ";
    displayScore += std::to_string(getScore());
    drawTextOnTheScren(window, displayScore, 45, 300, window.getSize().y - 200);
}