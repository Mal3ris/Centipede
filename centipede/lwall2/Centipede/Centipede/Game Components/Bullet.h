#pragma once

#include "TEAL\CommonElements.h"

//Forward declarations
class Mushroom;
class BulletFactory;
class Flea;
class CentiBod;
class Centipede;
class Scorpion;
class Spider;
class Tile;
class CommandSound;

class Bullet : public GameObject
{
public:
	Bullet();
	Bullet(const Bullet&) = delete;
	Bullet& operator=(const Bullet&) = delete;
	~Bullet() = default;

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	virtual void Initialize(sf::Vector2f p, BulletFactory* pFactoryNew);

	virtual void Collision( GameObject *go){};
	virtual void Collision( Mushroom *other );
	virtual void Collision( Tile *other );
	virtual void Collision( Flea *other );
	virtual void Collision( CentiBod *other );
	virtual void Collision( Centipede *other );
	virtual void Collision( Scorpion *other );
	virtual void Collision( Spider *other );

	void ClearCommands();

	sf::Vector2f getStartPos();


private:
	const float SPEED = 8;

	sf::Vector2f Pos;
	AnimatedSprite MainSprite;
	
	static BulletFactory* pFactory;
	
	sf::Vector2f startPos;

	CommandSound* pSound;
};