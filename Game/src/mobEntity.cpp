#include "mobEntity.h"
#include "playerEntity.h"
#include "projectilesEntities.h"


auto player = Player::getInstance();
MeteorSpawn meteorSpawn;

Mob::Mob() { type = beingType::MOB;}

void Mob::atkSpeedHandler(double deltaTime) {
    if (getShootTimer() > 0) {
        setShootTimer(getShootTimer() - deltaTime);
    }
}

void Mob::shoot() {
    if (getShootTimer() <= 0) {        
        createBullet(x(), y() + getHeight_() / 2, -1500, 0, Bullet::PLAYER);
        resetShootTimer();
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Attack du boss

void Mob::bossPaternDashAttackOne(sf::RenderWindow& window, double deltaTime) {
    Vector direction;

    if (x() > window.getSize().x / 1.28 && lockTimeBoss < (1 * phaseTwoReducer))
    {
        setVelocity(-300, player->y() - y());
    }
    else if (x() < window.getSize().x / 1.28 && lockTimeBoss < (1 * phaseTwoReducer))
    {
        setVelocity(0, 0);
        playerPos = Vector(player->x(), player->y());
        mobPos = Vector(x(), y());
        lockTimeBoss += deltaTime;
    }
    else if (x() < window.getSize().x / 1.28 && lockTimeBoss > (1 * phaseTwoReducer))
    {
        direction = playerPos - mobPos;
        direction = direction.Normalize();
        setVelocity(direction.x * (2000 * phaseTwoIncrease), direction.y * (2000 * phaseTwoIncrease));
    }


    setX(x() + velocity().x * deltaTime);
    setY(y() + velocity().y * deltaTime);

    if (x() + getWidth_() < 0) {
        setX(window.getSize().x);
        setY(window.getSize().y / 2);
        dashAttackNumber--;
        lockTimeBoss = 0;
    }
    if (dashAttackNumber <= 0) {
        dashAttackNumber = 3;
        onDashAttack = false;
        onRangeAttack = true;
    }
}

void Mob::resetRangedAttackBoss() {
    timeBeforeRangedAttackZone = 0;
    xzone = 0;
    yzone = 0;
    rangedAttackNbr--;
    if (rangedAttackNbr <= 0) {
        onDashAttack = true;
        onRangeAttack = false;
        rangedAttackNbr = 3; 
    }
}

void Mob::bossPaternRangeAttackOne(sf::RenderWindow& window, double deltaTime) {

    setY(SpawnPosY + 100 * std::sin(2 * 3.141592653589793 * 1 * x() / 800));
    if (!timeBeforeRangedAttackZone) { // lancer uniquement une fois
        rangedAttackZone.setRadius(150);
        xzone = player->x() - 100;
        yzone = player->y() - 100;
        side = 100 * std::sqrt(2);
        rangedAttackZone.setPosition(xzone, yzone);
        rangedAttackZone.setFillColor(sf::Color(255, 0, 0, 128));
        comingRangedAttackZone.setFillColor(sf::Color(255,0,0,150));
    }
    timeBeforeRangedAttackZone += deltaTime ;
    comingRangedAttackZone.setRadius(150 * timeBeforeRangedAttackZone  * phaseTwoIncrease);
    comingRangedAttackZone.setOrigin(comingRangedAttackZone.getRadius(), comingRangedAttackZone.getRadius());
    comingRangedAttackZone.setPosition(xzone + rangedAttackZone.getRadius(), yzone + rangedAttackZone.getRadius());


    if (timeBeforeRangedAttackZone > 1 * phaseTwoReducer) {
        sf::FloatRect rect1((xzone + 100) - side / 2, (yzone + 100) - side / 2, side, side); // un carr� contenu dans le cercle (chaque point touche le bord du cercle, il y a donc une marge d'erreur � l'avantage du joueur) 

        sf::FloatRect rect2(player->x(), player->y(), player->getWidth_(), player->getHeight_());

        if (rect1.intersects(rect2)) {
            player->takeDmg(1);
        }
        resetRangedAttackBoss();
    }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mob::updatePosition(sf::RenderWindow& window, double deltaTime) {

    if (MobType == "Tireur")
    {
        //mouvement sinusoidale
        double amplitutde = 200;
        double frequence = 1;
        setX(x() + velocity().x * deltaTime);
        setY(SpawnPosY + amplitutde * std::sin(2 * 3.141592653589793 * frequence * x() / 800));

        shoot();

        if (x() + getWidth_() < 0) {
            die();
        }
    }
    else if (MobType == "Chenille")
    {
        //mouvement �ratique
        double amplitude = 300; // Rayon du cercle
        double frequence = 0.5; // Fr?quence du cercle (tour par seconde)
        this->setVelocity(-5,0);
        // Mise jour de l'angle
        this->angle += 2 * 3.141592653589793 * frequence * deltaTime; // deltaTime = temps ecoule depuis la derniere frame
        this->centreX += this->velocity().x;

        // Calcul des nouvelles coordonn?es
        this->setX(this->centreX + amplitude * std::cos(angle));
        this->setY(this->SpawnPosY + amplitude * std::sin(angle));

        if (this->x() + getWidth_() < 0) {
            die();
        }
    }
    else if (MobType == "Kamikaze")
    {
        //mouvement kamikaze
        Vector direction;
        if (x() > window.getSize().x / 2 && lockTime < 1)
        {
            setVelocity(-1000, (player->y() - y())/2);
        }
        else if (x() < window.getSize().x / 2 && lockTime < 1)
        {
            setVelocity(0, 0);
            playerPos = Vector(player->x(), player->y());
            mobPos = Vector(x(), y());
            lockTime += deltaTime;
        }
        else if (x() < window.getSize().x / 2 && lockTime > 1)
        {
            direction = playerPos - mobPos;
            direction = direction.Normalize();
            setVelocity(direction.x * 2000, direction.y * 2000);
        }


        setX(x() + velocity().x * deltaTime);
        setY(y() + velocity().y * deltaTime);

        if (x() + getWidth_() < 0 || y() + getHeight_() < 0 || y() > window.getSize().y) {
            die();
        }
        if (x() > window.getSize().x && deathTimer >= 2)
        {
            die();
        }
        else if (x() > window.getSize().x)
        {
            deathTimer += deltaTime;
        }

    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Boss

    else if (MobType == "Boss") { // oui j'ai repris le code du kamikaze, mais voila c'etait sur en faite c'etait sur ( bruit de clavier qui se casse ) x 3
        setAreTheBoss();
        if (x() > window.getSize().x / 1.1294) {  // aproximativement 1700 avec 1920 en largeur d'ecran
            setVelocity(-300, y());
            setX(x() + velocity().x * deltaTime);
        }
        if (hp() < 50 / 2) {
            phaseTwoIncrease = 1.7;
            phaseTwoReducer = 0.7;
        }
        if (onDashAttack) {  // alterne entre deux patterns
            bossPaternDashAttackOne(window,deltaTime);
        }
        else if (onRangeAttack) {
            bossPaternRangeAttackOne(window,deltaTime);
            setY(window.getSize().y / 2 - getHeight_() / 2 + 300 * std::sin(2 * 3.141592653589793 * (300 * phaseTwoIncrease )* timerDeplacementY / 800));
        }
        timerDeplacementY += deltaTime;
    }    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}



void Mob::update(sf::RenderWindow& window, double deltaTime) {

    if (!isDead()) {
        updatePosition(window, deltaTime);
        atkSpeedHandler(deltaTime);
        if (getTheBossJustSpawn()) {
            setTheBossJustSpawn(false);
        }
    }
}

void Mob::draw(sf::RenderWindow& window) {
    drawImageEntities(window, x(), y());
    if (MobType == "Boss" && onRangeAttack) {
        window.draw(comingRangedAttackZone);
        window.draw(rangedAttackZone);
    }
}

void Mob::getHit(std::shared_ptr<Being> object) {
    if (object->getType() == Being::BULLET) {
        std::shared_ptr<Bullet> bulletPtr = std::dynamic_pointer_cast<Bullet>(object);
        if (bulletPtr->getTarget() == 2 || !bulletPtr->getTarget()) { // rappel: 1 si la cible est le joueur, 2 les monstres et 0 pour les deux
            this->takeDmg(1);
        
        if (meteorSpawn.getMeteorSpawn() <= 0) {
            createMeteor();
            meteorSpawn.resetMeteorSpawn();
        }
        meteorSpawn.setMeteorSpawn(meteorSpawn.getMeteorSpawn() - 1);
        }
        
    }
}