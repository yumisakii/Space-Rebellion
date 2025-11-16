#include <memory>
#include <random>
#include <vector>
#include "ManageEntities.h"
#include "Entity.h"
#include "playerEntity.h"
#include "projectilesEntities.h"
#include "mobEntity.h"
#include "collectibleEntity.h"
#include "Menu.h"

std::vector<std::shared_ptr<Being>> entities;

extern double GameTime = 0;


void initEntities(sf::RenderWindow& window) {
    // create player
    auto player = Player::getInstance();

    player->resetScore();
    player->setX(window.getSize().x / float(2));
    player->setY(window.getSize().y / float(2));
    player->jesus();
    player->setHP(3);
    player->setInvincibilityTime(1);
    player->resetInvTime();
    player->loadFont();
    player->loadImageEntities("Assets/Entities/Character_Main.png");
    
    // add player
    entities.push_back(player);
}

void createBullet(double x, double y, double velocityX, double velocityY,int Target) {
        auto bullet = std::make_shared<Bullet>();
        double width = 80;
        double height = 30;

        bullet->setWidth_(width);
        bullet->setHeight_(height);
        bullet->setObjectRect(width,height); // actualisation de la taille de l'object
        bullet->setX(x); //position
        bullet->setY(y);
        bullet->setVelocity(velocityX, velocityY); //vitesse
        bullet->setBulletType(0);
        if (Target  == 1)
        {
            bullet->setTarget(Bullet::PLAYER);
            bullet->loadImageEntities("Assets/Projectiles/Projectile ennemi base.png");
        }
        else if (Target == 2)
        {
            bullet->setTarget(Bullet::MOB);
            bullet->loadImageEntities("Assets/Projectiles/Projectile joueur.png");
        }


        entities.push_back(bullet);
}


void createExplosiveBullet(double x, double y, double velocityX, double velocityY) {
    auto bullet = std::make_shared<Bullet>();
    double width = 100;
    double height = 30;

    bullet->setWidth_(width);
    bullet->setHeight_(height);
    bullet->setObjectRect(width, height); // actualisation de la taille de l'object
    bullet->setX(x); //position
    bullet->setY(y);
    bullet->setVelocity(velocityX, velocityY); //vitesse
    bullet->setTarget(Bullet::MOB);
    bullet->setBulletType(1);
    bullet->loadImageEntities("Assets/Projectiles/Roquette joueur.png");

    entities.push_back(bullet);
}

void createMeteor() {
    auto meteor = std::make_shared<Meteor>();

    meteor->setWidth_(250);
    meteor->setHeight_(200);
    meteor->setObjectSize();
    meteor->setVelocity(getRandomNumber(0, 50), getRandomNumber(10, 100));
    meteor->setX(getRandomNumber(300, 1800));
    meteor->setY(0);
    meteor->setHP(10);
    meteor->loadImageEntities("Assets/Destructible/Destructible normal.png");

    entities.push_back(meteor);
}

void createCollectible(double x, double y) {
    auto collectible = std::make_shared<Collectible>();

    collectible->setObjectSize();
    collectible->setVelocity(0, 60);
    collectible->setX(x);
    collectible->setY(y);
    collectible->setHP(1);
    collectible->setCollectibleType(getRandomNumber(0, 1));
    if (collectible->getCollectibleType() == 0) {
        collectible->loadImageEntities("Assets/UI_UX/batterie.png");
        collectible->setWidth_(120);
        collectible->setHeight_(90);
    }
    if (collectible->getCollectibleType() == 1) {
        collectible->loadImageEntities("Assets/Projectiles/Roquette joueur.png");
        collectible->setWidth_(90);
        collectible->setHeight_(54);
    }

    entities.push_back(collectible);
}


void destroyEntities() {
    entities.erase(
        std::remove_if(
            entities.begin(),
            entities.end(),
            [](const std::shared_ptr<Being>& entity) {
                // Vérification si l'entité est un joueur et qu'elle est morte
                if (entity->isDead() && std::dynamic_pointer_cast<Player>(entity)) {
                    game_over = true; // Mettre game_over à true si un joueur est détruit
                }

                // Vérification si l'entité est un mob et si le mob est un boss
                if (entity->isDead() && std::dynamic_pointer_cast<Mob>(entity)) {
                    if (std::shared_ptr<Mob> mob = std::dynamic_pointer_cast<Mob>(entity)) {
                        if (mob->getMobType() == "Boss") {
                            // Ajoutez ici ce que vous souhaitez faire si un Boss est mort
                            // Par exemple, on pourrait mettre game_over à true aussi.
                            victory = true;
                        }
                    }
                }
                return entity->isDead();
            }),
        entities.end()
    );
}


void updateEntities(sf::RenderWindow& window, double deltaTime) {
    for (size_t i = 0; i < entities.size(); ++i) {
        if (!entities[i]) {
            continue;
        }
        for (size_t j = 0; j < entities.size() - 1; j++) {
            if (i != j) { // pour eviter qu'il verifie si un object a une collision avec lui meme
                entities[i]->checkCollision(entities[i], entities[j]);
            }
        }
        entities[i]->update(window, deltaTime);
    }
    destroyEntities();
}

void drawEntities(sf::RenderWindow& window) {
    for (auto& entity : entities) {
        entity->draw(window);
    }
}

int getRandomNumber(int x1, int x2) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(x1, x2);
    int randomNumber = dist(gen);

    return randomNumber;
}

void createMob(double y, std::string Type, double hp, double width, double height) {
    auto mob = std::make_shared<Mob>();

    mob->setWidth_(width);
    mob->setHeight_(height);
    mob->setObjectRect(width, height); // doit etre fait manuellement
    mob->setX(1920);
    mob->setSpawnPosY(y);
    mob->setY(y); //le d�placement kamikaze a besoin d'�tre set manuellement donc faut laisser cette ligne
    mob->setMobType(Type);
    mob->setHP(hp);
    if (Type == "Tireur") {
        mob->loadImageEntities("Assets/Entities/Ennemi 1.png");
        mob->setWidth_(mob->getWidth_() * 2.2);
        mob->setHeight_(mob->getHeight_() * 1.8);
    }
    if (Type == "Kamikaze") {
        mob->loadImageEntities("Assets/Entities/Ennemi 2.png");
        mob->setWidth_(mob->getWidth_() * 2.5);
        mob->setHeight_(mob->getHeight_() * 1.8);
    }
    if (Type == "Chenille") {
        mob->loadImageEntities("Assets/Entities/Ennemi 3.png");
        mob->setWidth_(mob->getWidth_() * 2.2);
        mob->setHeight_(mob->getHeight_() * 1.8);
    }
    if (Type == "Boss") {
        Audio& audio = Audio::getInstance();
        audio.pauseAllSounds();
        audio.playSound("bossMusic");
        mob->loadImageEntities("Assets/Entities/boss.png");
        mob->setWidth_(mob->getWidth_() * 2.3);
        mob->setHeight_(mob->getHeight_() * 1.8);
    }
    

    entities.push_back(mob);
}

struct SpawnInfo {
    double spawnTime;   // Temps auquel le mob doit appara�tre
    std::string type;   // Type du mob ("Tireur", "Chenille", "Kamikaze")
    double y;           // Position Y du spawn
    double hp;
    double widht; // necessaire pour definir la taille du boss
    double height;
};

// Liste des spawns pour la vague actuelle
//tireur met 6.46s a traverser l ecran
//kamikaze met 4.55s a traverser l ecran
//chenille met 6.34s a traverser l ecran
//mettre 0.13s entre chaque chenille
std::vector<SpawnInfo> spawnWave = {
    
    {1.0, "Tireur", 270, 1, 80, 50},       
    {1.1, "Tireur", 810, 1, 80, 50},
    
    {8.0, "Kamikaze", 100, 1, 80, 50},

    {13.00, "Chenille", 540, 1, 60, 60},
    {13.13, "Chenille", 540, 1, 60, 60},
    {13.26, "Chenille", 540, 1, 60, 60},

    {20, "Tireur", 540, 1, 80, 50},
    {21, "Tireur", 810, 1, 80, 50},
    {21.1, "Tireur", 270, 1, 80, 50},

    {30, "Chenille", 380, 1, 60, 60},
    {30.13, "Chenille", 380, 1, 60, 60}, {30.26, "Chenille", 380, 1, 60, 60}, {30.39, "Chenille", 380, 1, 60, 60}, {30.52, "Chenille", 380, 1, 60, 60},
    {30.65, "Chenille", 380, 1, 60, 60}, {30.78, "Chenille", 380, 1, 60, 60}, {30.91, "Chenille", 380, 1, 60, 60}, {31.04, "Chenille", 380, 1, 60, 60},
    {31.17, "Chenille", 380, 1, 60, 60}, {31.3, "Chenille", 380, 1, 60, 60},  {31.43, "Chenille", 380, 1, 60, 60}, {31.56, "Chenille", 380, 1, 60, 60},
    {31.69, "Chenille", 380, 1, 60, 60}, {31.82, "Chenille", 380, 1, 60, 60}, {31.95, "Chenille", 380, 1, 60, 60}, {32.08, "Chenille", 380, 1, 60, 60},
    {32.21, "Chenille", 380, 1, 60, 60}, {32.34, "Chenille", 380, 1, 60, 60}, {32.47, "Chenille", 380, 1, 60, 60}, {32.6, "Chenille", 380, 1, 60, 60},
    {32.73, "Chenille", 380, 1, 60, 60}, {32.86, "Chenille", 380, 1, 60, 60},
    {32.99, "Chenille", 380, 1, 60, 60},

    {38.0, "Chenille", 100, 1, 60, 60},
    {38.13, "Chenille", 100, 1, 60, 60}, {38.26, "Chenille", 100, 1, 60, 60}, {38.39, "Chenille", 100, 1, 60, 60}, {38.52, "Chenille", 100, 1, 60, 60},
    {38.65, "Chenille", 100, 1, 60, 60}, {38.78, "Chenille", 100, 1, 60, 60}, {38.91, "Chenille", 100, 1, 60, 60}, {39.04, "Chenille", 100, 1, 60, 60},
    {39.17, "Chenille", 100, 1, 60, 60}, {39.3, "Chenille", 100, 1, 60, 60},  {39.43, "Chenille", 100, 1, 60, 60}, {39.56, "Chenille", 100, 1, 60, 60},
    {39.69, "Chenille", 100, 1, 60, 60}, {39.82, "Chenille", 100, 1, 60, 60}, {39.95, "Chenille", 100, 1, 60, 60}, {40.08, "Chenille", 100, 1, 60, 60},
    {40.21, "Chenille", 100, 1, 60, 60}, {40.34, "Chenille", 100, 1, 60, 60}, {40.47, "Chenille", 100, 1, 60, 60}, {40.6, "Chenille", 100, 1, 60, 60},
    {40.73, "Chenille", 100, 1, 60, 60}, {40.86, "Chenille", 100, 1, 60, 60},
    {40.99, "Chenille", 100, 1, 60, 60},

    {41.0, "Chenille", 900, 1, 60, 60},
    {41.13, "Chenille", 900, 1, 60, 60}, {41.26, "Chenille", 900, 1, 60, 60}, {41.39, "Chenille", 900, 1, 60, 60}, {41.52, "Chenille", 900, 1, 60, 60},
    {41.65, "Chenille", 900, 1, 60, 60}, {41.78, "Chenille", 900, 1, 60, 60}, {41.91, "Chenille", 900, 1, 60, 60}, {42.04, "Chenille", 900, 1, 60, 60},
    {42.17, "Chenille", 900, 1, 60, 60}, {42.3, "Chenille", 900, 1, 60, 60},  {42.43, "Chenille", 900, 1, 60, 60}, {42.56, "Chenille", 900, 1, 60, 60},
    {42.69, "Chenille", 900, 1, 60, 60}, {42.82, "Chenille", 900, 1, 60, 60}, {42.95, "Chenille", 900, 1, 60, 60}, {43.08, "Chenille", 900, 1, 60, 60},
    {43.21, "Chenille", 900, 1, 60, 60}, {43.34, "Chenille", 900, 1, 60, 60}, {43.47, "Chenille", 900, 1, 60, 60}, {43.6, "Chenille", 900, 1, 60, 60},
    {43.73, "Chenille", 900, 1, 60, 60}, {43.86, "Chenille", 900, 1, 60, 60}, {43.99, "Chenille", 900, 1, 60, 60},
    {44.12, "Chenille", 900, 1, 60, 60},


    {58.5, "Kamikaze", 540, 1, 80, 50},
    {59, "Kamikaze", 700, 1, 80, 50},
    {59.5, "Kamikaze", 350, 1, 80, 50},
    {60, "Kamikaze", 800, 1, 80, 50},
    {60.5, "Kamikaze", 250, 1, 80, 50},
    {61, "Kamikaze", 900, 1, 80, 50},
    {61.5, "Kamikaze", 160, 1, 80, 50},
    {62, "Kamikaze", 1000, 1, 80, 50},
    {62.5, "Kamikaze", 80, 1, 80, 50},

    {70.85, "Chenille", 380, 1, 60, 60},
    {70.98, "Chenille", 380, 1, 60, 60}, {71.11, "Chenille", 380, 1, 60, 60}, {71.24, "Chenille", 380, 1, 60, 60}, {71.37, "Chenille", 380, 1, 60, 60},
    {71.5, "Chenille", 380, 1, 60, 60},

    {74.00, "Chenille", 700, 1, 60, 60},
    {74.13, "Chenille", 700, 1, 60, 60}, {74.26, "Chenille", 700, 1, 60, 60}, {74.39, "Chenille", 700, 1, 60, 60}, {74.52, "Chenille", 700, 1, 60, 60},
    {74.65, "Chenille", 700, 1, 60, 60},

    {76.00, "Tireur", 400, 1, 80, 50},
    {79.00, "Tireur", 600, 1, 80, 50},

    {80.5, "Kamikaze", 270, 1, 80, 50},     
    {81.5, "Kamikaze", 810, 1, 80, 50},

    {82.35, "Chenille", 540, 1, 60, 60},    
    {82.48, "Chenille", 540, 1, 60, 60}, {82.61, "Chenille", 540, 1, 60, 60}, {82.74, "Chenille", 540, 1, 60, 60}, {82.87, "Chenille", 540, 1, 60, 60},
    {83.00, "Chenille", 540, 1, 60, 60},
    
    {88.00, "Boss", 540, 80, 200, 200 },
    //120 si je sais compter
};

size_t nextSpawnIndex = 0; // Index du prochain mob � spawner

const double epsilon = 0.2; // Tolerance pour compenser les impr�cisions temporelles

void updateMobWave(double deltaTime) {
    GameTime += deltaTime;
    // V�rifie s'il reste des spawns dans la vague
    while (nextSpawnIndex < spawnWave.size() &&
        GameTime >= spawnWave[nextSpawnIndex].spawnTime - epsilon) {

        // Recupere les infos du spawn
        const auto& spawn = spawnWave[nextSpawnIndex];

        // Cree le mob
        createMob(spawn.y, spawn.type, spawn.hp, spawn.widht, spawn.height);

        // Passe au prochain spawn
        nextSpawnIndex++;
    }
}


void resetGame(sf::RenderWindow& window) {
    entities.clear();
    GameTime = 0;
    nextSpawnIndex = 0;
    initEntities(window);
}