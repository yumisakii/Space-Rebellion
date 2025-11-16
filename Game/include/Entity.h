#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <vector>
#include "input.h"
#include "vector.h"
#include "ManageEntities.h"
#include "Menu.h"
#include "vfx.h"

using namespace std;

class Entity {
public:
	Entity() : x_(0), y_(0){}
	virtual ~Entity() {}

	virtual void update(sf::RenderWindow& window, double deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	double x() const { return x_; }
	double y() const { return y_; }

	void setX(double x) { x_ = x; }
	void setY(double y) { y_ = y; }

private:
	double x_, y_;
};

class Being : public Entity {
public:
	enum beingType {
		UNKNOWN,
		PLAYER,
		MOB,
		BULLET,
		METEOR,
		COLLECTIBLE
	};

	Being() : hp_(1), invincibilityTimer_(0), invTime_(0), isDead_(false) {}

	double hp() const { return hp_; }
	double invTime() const { return invTime_; }
	bool isDead() const { return isDead_; }

	virtual void getHit(std::shared_ptr<Being>  object) = 0;

	void setHP(double hp) { hp_ = hp; }
	void setInvincibilityTime(double inv) { invincibilityTimer_ = inv; }
	void setInvTime(double invTime) { invTime_ = invTime; }
	void resetInvTime() { invTime_ = invincibilityTimer_; }
	
	void die() { isDead_ = true; }
	void jesus() { isDead_ = false; } //easter egg
	
	void checkCollision(std::shared_ptr<Being> being1, std::shared_ptr<Being> being2);

	void setWidth_(double newWidth_) { width_ = newWidth_; }
	double getWidth_() const { return width_; }

	void setHeight_(double newHeight) { height_ = newHeight; }
	double getHeight_() const { return height_; }

	void updateInvTime(double deltaTime);
	void takeDmg(float damage);

	void setObjectRect(double newWidth, double newHeight) { objectRect = sf::RectangleShape(sf::Vector2f(newWidth, newHeight)); }
	sf::RectangleShape getRect() { return objectRect; }

	beingType getType() { return type; }

	void setAreTheBoss();
	bool getTheBossJustSpawn() { return theBossJustSpawn; }
	void setTheBossJustSpawn(bool newValue) { theBossJustSpawn = newValue; }





	bool loadImageEntities(const std::string& filePath);
	void drawImageEntities(sf::RenderWindow& window, float x, float y);

	

protected:
	struct Effect {
		sf::Sprite sprite;
		float currentTime;  // Temps actuel de l'animation
		size_t currentFrame; // Cadre actuel de l'animation
		bool finished;       // Indique si l'animation est termin�e
	};

	double hp_;
	bool isDead_;
	double invincibilityTimer_;
	double invTime_;
	bool isInvincible = true;
	double width_ = 200;
	double height_ = 90;
	sf::RectangleShape objectRect = sf::RectangleShape(sf::Vector2f(width_, height_));

	sf::Texture texture;
	sf::Sprite sprite;

	beingType type = UNKNOWN; //default value
private:
	bool areTheBoss = false;
	bool theBossJustSpawn = false;  // pb anticiper

};

