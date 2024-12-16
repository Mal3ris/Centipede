#pragma once

#include "TEAL\CommonElements.h"
#include "GridConstants.h"

class MushroomSpawner;
class Bullet;
class MoveStateCentipede;
class CentiBod;
class CommandScore;
class CommandSound;
class CentipedeFactory;

class Centipede : public GameObject
{
public:
	Centipede();
	Centipede(const Centipede&) = delete;
	Centipede& operator=(const Centipede&) = delete;
	~Centipede() = default;

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	virtual void Initialize(sf::Vector2f p, MushroomSpawner* pMushroomGrid,
		bool moveRight, CentipedeFactory* myNewFact);
	virtual void Initialize(sf::Vector2f p, MushroomSpawner* pMushroomGrid, int pCount, 
		const MoveStateCentipede* pState, CentipedeFactory* myNewFact);

	virtual void Collision(GameObject* go) {};
	virtual void Collision(Bullet* other);

	sf::Vector2f getPos();

	void CleanCommands();

	void setNextBod(CentiBod* next);

	const MoveStateCentipede* getState();



private:
	
	const MoveStateCentipede* pCurrState;

	CentipedeFactory* myFact;

	sf::Vector2f Pos;
	AnimatedSprite MainSprite;

	CentiBod* nextBod = nullptr;

	const float SPEED = 2;
	
	int posCounter = 0;

	MushroomSpawner* myMushroomGrid;

	CommandScore* pDeath;
	CommandSound* pSound;
	bool pDeathReleased;

};