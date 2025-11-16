#pragma once
#include "Entity.h"
#include "Audio.h"
#include "Image.h"

class Player : public Being {
public:
	Player();
	virtual ~Player() {}

	Vector velocity() const { return velocity_; }
	void setVelocity(double velocityx, double velocityy);

	InputManager inputManager;
	void inputDetection();

	void updatePosition(sf::RenderWindow& window, double deltaTime);
	void update(sf::RenderWindow& window, double deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	void getHit(std::shared_ptr<Being> object);

	// shoot systeme
	double getShootTimer() const { return shootTimer; }
	void setShootTimer(double x) { shootTimer = x; }
	void resetShootTimer() { shootTimer = 0.2; }

	double getExplosionTimer() const { return ExplosiveTimer; }
	void setExplosionTimer(double x) { ExplosiveTimer = x; }
	void resetExplosionTimer() { ExplosiveTimer = 10; }

	void atkSpeedHandler(double deltaTime);
	void shoot();
	void shootExplosive();

	void drawDisplayHP(sf::RenderWindow& window);
	void drawExplosiveBulletCD(sf::RenderWindow& window);
	void drawTextOnTheScren(sf::RenderWindow& window, const std::string& text, int fontSize, float x, float y);
	void loadFont();

	void drawPlayerScore(sf::RenderWindow& window);

	bool loadImagePV(std::string path);
	//entity
	std::vector<sf::Sprite> displayHP();

	static std::shared_ptr<Player> getInstance() {
		if (!instance) {
			instance = std::shared_ptr<Player>(new Player());
		}
		return instance;
	}

	double getPVHeight() const { return PVHeight; }
	void setPVHeight(double x) { PVHeight = x; }

	double getPVWidth() const { return PVWidth; }
	void setPVWidth(double x) { PVWidth = x; }

	void addScore(int addValue);
	void resetScore() { score = 0; }
	int getScore() { return score; }

private:
	static std::shared_ptr<Player> instance;

	Vector velocity_ = Vector(0.0, 0.0);

	sf::Texture texturePV;
	sf::Sprite spritePV;

	double PVHeight = 150;
	double PVWidth = 200;

	int score = 0;

	double shootTimer = 0.2;
	double ExplosiveTimer = 0;
	sf::Font font;
	bool alwaysClick = false;
	Audio& audio = Audio::getInstance();
};