#pragma once
#include "Entity.h"

class Bullet : public Being {
public:
	Bullet();
	virtual ~Bullet() {}
	enum TargetedBeing {
		ALL,
		PLAYER,
		MOB
	};

	Vector velocity() const { return velocity_; }

	void setVelocity(double velocityx, double velocityy);

	void updatePosition(sf::RenderWindow& window, double deltaTime);
	

	void update(sf::RenderWindow& window, double deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	void setTarget(Bullet::TargetedBeing newTarget) { targetedBeing = newTarget; }
	TargetedBeing getTarget() { return targetedBeing; }

	int getBulletType() const { return bulletType; }
	void setBulletType(int newBulletType);
	void explode();
	void getHit(std::shared_ptr<Being> object);

	int specialBullet() const { return _specialBullet; }
	void setSpecialBullet(int specialBullet) { _specialBullet = specialBullet; }
	int getSpecialBullet() const { return bulletType; }

	std::vector<sf::RectangleShape> displaySBullet();
	void drawSpecialBulletsUI(sf::RenderWindow& window);

private:
	Vector velocity_ = Vector(700, 0);
	int bulletType = 0; // 0 = normal, 1 = explosionnn

	int _specialBullet = 3; //nb balle speciales

	TargetedBeing targetedBeing = ALL;
};


class Meteor : public Being {
public:
	Meteor();
	virtual ~Meteor() {}

	Vector velocity() const { return velocity_; }
	void setVelocity(double velX, double velY);

	void setObjectSize() { object = sf::RectangleShape(sf::Vector2f(getWidth_(), getHeight_())); };

	void getHit(std::shared_ptr<Being>  object) override;

	void updatePosition(sf::RenderWindow& window, double deltaTime);
	void update(sf::RenderWindow& window, double deltaTime) override;
	void draw(sf::RenderWindow& window) override;


private:
	Vector velocity_ = Vector(0, 0);
	sf::RectangleShape object = sf::RectangleShape(sf::Vector2f(getWidth_(), getHeight_()));
};

///////////////////////////////////////

class MeteorSpawn {
public:
	MeteorSpawn();
	virtual ~MeteorSpawn() {}

	int getMeteorSpawn();
	void setMeteorSpawn(int newMeteorSpawn);
	void resetMeteorSpawn();

private:
	int meteorSpawn = 2;
};