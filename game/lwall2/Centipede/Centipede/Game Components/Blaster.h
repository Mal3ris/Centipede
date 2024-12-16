#pragma once

#include "TEAL\CommonElements.h"
#include "GridConstants.h"

// Forward declarations
class Mushroom;
class Flea;
class Centipede;
class CentiBod;
class Spider;
class GameController;
class BulletFactory;
class MovementStrategy;
class CommandSound;

class Blaster : public GameObject
{
public:
	Blaster();
	Blaster(const Blaster&) = delete;
	Blaster& operator=(const Blaster&) = delete;
	~Blaster() = default;

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	void Initialize(BulletFactory* pBulletFactory, MovementStrategy* pStrat);
	
	virtual void Collision(GameObject* go) {};
	virtual void Collision( Mushroom *other );
	virtual void Collision( Flea *other );
	virtual void Collision( Centipede *other );
	virtual void Collision( CentiBod *other );
	virtual void Collision( Spider *other );

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Fire();

	void CleanCommands();

	sf::Vector2f getPos() { return Pos; }

private:

	MovementStrategy* myMovement;

	const float SPEED = 4;

	const sf::Vector2f blasterOffset = sf::Vector2f(0, 0);

	float offset;

	sf::Vector2f Pos;
	sf::Vector2f PrevPos;

	AnimatedSprite MainSprite;

	const float PLAYTOP = GridConstants::PLAYZONE * GridConstants::CELLSIZE
		+ GridConstants::HALFCELLSIZE;
	const float PLAYBOTTOM = GridConstants::BOTTOMZONE * GridConstants::CELLSIZE
		- GridConstants::HALFCELLSIZE;

	bool activeBullet = false;

	bool resetMove = false;

	BulletFactory* myBulletFactory;

	CommandSound* pSound;
};