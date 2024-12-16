#pragma once

//The Spider

#include "TEAL\CommonElements.h"
#include "GridConstants.h"

class Bullet;
class MushroomSpawner;
class SpiderSpawner;
class SpiderFactory;
class CommandScore;
class CommandSound;

class Spider : public GameObject
{
public:
	Spider();
	Spider(const Spider&) = delete;
	Spider& operator=(const Spider&) = delete;
	~Spider() = default;

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	virtual void Initialize(sf::Vector2f p, bool moveRight, float nSpeed, SpiderFactory* myNewFact, SpiderSpawner* mySpawn);

	virtual void Collision(GameObject* go) {};
	virtual void Collision(Bullet* other);

	void CleanCommands();


private:
	sf::Vector2f Pos;
	AnimatedSprite MainSprite;

	float speed = 2;
	bool moving = true;
	bool bouncing = false;

	bool moveFlip = false;
	bool bounceFlip = false;

	int amountToMove;
	int amountToBounce;

	int posCounter;

	CommandScore* pDeath;
	CommandSound* pSound;

	SpiderFactory* myFact;
	SpiderSpawner* mySpawner;

	int MAXBOUNCE = (int)((GridConstants::BOTTOMZONE * GridConstants::CELLSIZE - GridConstants::PLAYZONE * GridConstants::CELLSIZE));
	int MINBOUNCE = (int)GridConstants::CELLSIZE;
};