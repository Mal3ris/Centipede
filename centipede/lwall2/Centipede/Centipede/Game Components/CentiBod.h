#pragma once

#include "TEAL\CommonElements.h"
#include "GridConstants.h"

#include <queue>

//Forward Declarations
class MushroomSpawner;
class Bullet;
class MoveStateCentipede;
class Centipede;
class CentipedeFactory;
class CentiBodFactory;
class CommandScore;
class CommandSound;

class CentiBod : public GameObject
{
public:
	CentiBod();
	CentiBod(const CentiBod&) = delete;
	CentiBod& operator=(const CentiBod&) = delete;
	~CentiBod() = default;

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	virtual void Initialize(sf::Vector2f p, MushroomSpawner* pMushroomGrid, 
		CentipedeFactory* newHeadFact,bool dir, CentiBodFactory* newBodyFact);

	virtual void Collision(GameObject* go) {};
	virtual void Collision(Bullet* other);

	sf::Vector2f getPos();

	void setPrevHead(Centipede* prev);
	void setPrevBod(CentiBod* prev);
	void setNextBod(CentiBod* next);

	void setNextState(const MoveStateCentipede* nextState);
	void setCurrState(const MoveStateCentipede* nextState);

	void CleanCommands();

	void swapForHead();

private:
	const MoveStateCentipede* myPrevState;
	const MoveStateCentipede* myCurrState;

	CentiBod* pNextBod;
	CentiBod* pPrevBod;
	Centipede* pPrevHead = nullptr;

	sf::Vector2f Pos;
	AnimatedSprite MainSprite;

	bool prevIsHead;
	
	int posCounter = 0;

	MushroomSpawner* myMushroomGrid;
	CentipedeFactory* myHeadFactory;
	CentiBodFactory* myBodyFactory;

	CommandScore* pDeath;
	CommandSound* pSound;
	
	bool pDeathReleased = false;

};
