#pragma once

#include "TEAL\CommonElements.h"
#include "Tile.h"

//Forward Declarations
class Bullet; 
class MushroomSpawner;
class Scorpion;
class CommandScore;
class CommandSound;
class Spider;

class Mushroom : public Tile
{
public:
	Mushroom();
	Mushroom(const Mushroom&) = delete;
	Mushroom& operator=(const Mushroom&) = delete;
	~Mushroom() = default;

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	virtual void Initialize(sf::Vector2f p, MushroomSpawner* myManager);

	virtual void Collision( GameObject *go){};
	virtual void Collision( Bullet *other );
	virtual void Collision( Scorpion *other );
	virtual void Collision( Spider *other );

	virtual void Alarm0();

	sf::Vector2f getPos();
	float getWidth();
	float getHeight();

	void CleanCommands();

	virtual bool getPoison();

	virtual void reset();


private:
	sf::Vector2f Pos;
	AnimatedSprite MainSprite;

	float scale;
	int health;

	bool isPoison;

	MushroomSpawner* manager;

	CommandScore* pDeath;
	CommandScore* pRestore;

	CommandSound* pSound;
};
