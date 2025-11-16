#pragma once
#include "Entity.h"

class Collectible : public Being {
public:
	Collectible();
	virtual ~Collectible() {}

	Vector velocity() const { return velocity_; }
	void setVelocity(double velX, double velY);

	void setObjectSize() { object = sf::RectangleShape(sf::Vector2f(getWidth_(), getHeight_())); };
	
	void updatePosition(sf::RenderWindow& window, double deltaTime);

	void getHit(std::shared_ptr<Being>  object) override;
	void update(sf::RenderWindow& window, double deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	int getCollectibleType() const { return collectibleType; }
	void setCollectibleType(int newCollectibleType);


private:
	int collectibleType = 0;// 0 =  heal, 1 = reset cd explosion
	Vector velocity_ = Vector(0, 0);
	sf::RectangleShape object = sf::RectangleShape(sf::Vector2f(getWidth_(), getHeight_()));
};