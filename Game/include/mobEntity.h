#pragma once
#include "Entity.h"
#include "Menu.h"

class Mob : public Being {
public:
	Mob();
	virtual ~Mob() {}

	void update(sf::RenderWindow& window, double deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	Vector velocity() const { return velocity_; }

	void setVelocity(double velocityx, double velocityy) {
		velocity_.x = velocityx; velocity_.y = velocityy;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//Boss
	void bossPaternDashAttackOne(sf::RenderWindow& window, double deltaTime);

	void bossPaternRangeAttackOne(sf::RenderWindow& window, double deltaTime);

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	void updatePosition(sf::RenderWindow& window, double deltaTime);

	void getHit(std::shared_ptr<Being> object);

	double getShootTimer() const { return shootTimer; }
	void setShootTimer(double x) { shootTimer = x; }
	void resetShootTimer() { shootTimer = 1; }
	void atkSpeedHandler(double deltaTime);
	void shoot();

	void setMobType(string type) { MobType = type; }
	std:: string getMobType() { return MobType; }

	void setSpawnPosY(double pos) { SpawnPosY = pos; }

	void resetRangedAttackBoss();
	


private:
	//type de déplacement
	string MobType = "Kamikaze";
	Vector velocity_ = Vector(-300, 0.0);
	double SpawnPosY  = 540;

	//pour tireur
	double shootTimer = 0;

	//pour chenille
	double centreX = 1920;
	double angle = 0; // Angle en radians

	//pour kamikaze
	double lockTime = 0;
	double deathTimer = 0;
	Vector playerPos = Vector(0, 0);
	Vector mobPos = Vector(0, 0);

	//Pour le boss
	float phaseTwoIncrease = 1; // Pour augmenter la vitesse de deplacement du boss quand il est low
	float phaseTwoReducer = 1;  // Pour reduire le temps d'attente du boss quand il est low
	int dashAttackNumber = 3;
	double lockTimeBoss = 0;

	//Dashattack
	bool canAttack = false;
	bool onDashAttack = true;

	//RangedAttack
	bool onRangeAttack = false;
	sf::CircleShape rangedAttackZone;
	sf::CircleShape comingRangedAttackZone;
	int rangedAttackNbr = 3;
	float timeBeforeRangedAttackZone = 0;
	float xzone = 0;
	float yzone = 0;
	float side = 0;
	float timerDeplacementY = 0;
};