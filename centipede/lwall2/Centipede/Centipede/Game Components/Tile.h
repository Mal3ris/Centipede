#pragma once

//Tile Class Used on Grid

#include "TEAL\CommonElements.h"

class MushroomSpawner;
class Bullet;

class Tile: public GameObject
{
public:
	Tile();
	Tile(const Tile&) = delete;
	Tile& operator=(const Tile&) = delete;
	~Tile() = default;

	virtual void Destroy();
	virtual void Draw();
	virtual void reset() {};
	virtual bool getPoison() { return false; };

	virtual void Initialize(sf::Vector2f p, MushroomSpawner* myManager);

	virtual void Collision(GameObject* go) {};
	virtual void Collision(Bullet* other) {};

private:
	sf::Vector2f Pos;
	AnimatedSprite MainSprite;

	MushroomSpawner* myMushroomSpawner = nullptr;
};