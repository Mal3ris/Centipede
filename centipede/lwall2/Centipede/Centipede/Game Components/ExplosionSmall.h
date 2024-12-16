#pragma once

#include "TEAL\CommonElements.h"

class ExplosionSmall : public GameObject
{
public:
	ExplosionSmall();
	ExplosionSmall(const ExplosionSmall&) = delete;
	ExplosionSmall& operator=(const ExplosionSmall&) = delete;
	~ExplosionSmall() = default;

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	virtual void Initialize(sf::Vector2f p);


private:
	AnimatedSprite MainSprite;
	int ANIMLENGTH = 6;
	int posCounter;
};
