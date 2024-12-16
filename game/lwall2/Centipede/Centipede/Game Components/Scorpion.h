#pragma once

//Scorpion

#include "TEAL\CommonElements.h"

class Bullet;
class MushroomSpawner;
class ScorpionSpawner;
class CommandScore;
class CommandSound;
class ScorpionFactory;

class Scorpion : public GameObject
{
public:
	Scorpion();
	Scorpion(const Scorpion&) = delete;
	Scorpion& operator=(const Scorpion&) = delete;
	~Scorpion() = default;

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	virtual void Initialize(sf::Vector2f p, bool moveRight, float nSpeed, ScorpionFactory* myNewFact, ScorpionSpawner* myNewSpawn);

	virtual void Collision( GameObject *go){};
	virtual void Collision(Bullet* other);

	void CleanCommands();


private:
	sf::Vector2f Pos;
	AnimatedSprite MainSprite;
	
	float speed = 2;

	CommandScore* pDeath;
	CommandSound* pSound;
	bool pDeathReleased;
	
	ScorpionFactory* myFact = nullptr;
	ScorpionSpawner* mySpawner = nullptr;
};