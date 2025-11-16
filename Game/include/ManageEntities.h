#pragma once
#include <SFML/Graphics.hpp>


void initEntities(sf::RenderWindow& window);
void destroyEntities();
void updateEntities(sf::RenderWindow& window, double deltaTime);
void drawEntities(sf::RenderWindow& window);

void createBullet(double x, double y, double velocityX, double velocityY, int Target);

void createExplosiveBullet(double x, double y, double velocityX, double velocityY);
void createMeteor();
void createCollectible(double x, double y);

int getRandomNumber(int x1, int x2);
void createMob(double y, std::string Type, double hp, double width, double height);
void updateMobWave(double deltaTime);

void resetGame(sf::RenderWindow& window);

