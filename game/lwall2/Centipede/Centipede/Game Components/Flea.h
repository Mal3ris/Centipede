#pragma once

#include "TEAL\CommonElements.h"

class Bullet;
class MushroomSpawner;
class FleaSpawner;
class CommandScore;
class CommandSound;
class FleaFactory;

class Flea : public GameObject
{
public:
	Flea();
	Flea(const Flea&) = delete;
	Flea& operator=(const Flea&) = delete;
	~Flea() = default;

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	virtual void Initialize(sf::Vector2f p, MushroomSpawner* mushroomGrid, 
		FleaSpawner* fleaSpawner, FleaFactory* myNewFact, float nSpeed, int nFrequency);

	virtual void Collision( GameObject *go){};
	virtual void Collision(Bullet* other);

	void CleanCommands();

	
private:
	sf::Vector2f Pos;
	AnimatedSprite MainSprite;

	FleaFactory* myFact;
	
	int frequency = 18;
	float speed = 2;
	const int SPEEDMULT = 2;
	int health = 0;
	const int MAXHEALTH = 2;

	int posCounter = 0;

	MushroomSpawner* myMushroomGrid;
	FleaSpawner* myFleaSpawner;

	CommandScore* pDeath;
	CommandSound* pSound;

};
