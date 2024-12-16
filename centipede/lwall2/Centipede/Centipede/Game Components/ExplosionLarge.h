#pragma once

#include "TEAL\CommonElements.h"

class ExplosionLarge : public GameObject
{
public:
	ExplosionLarge();
	ExplosionLarge(const ExplosionLarge&) = delete;
	ExplosionLarge& operator=(const ExplosionLarge&) = delete;
	~ExplosionLarge() = default;

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	virtual void Initialize(sf::Vector2f p);


private:
	AnimatedSprite MainSprite;
	int ANIMLENGTH = 8;
	int posCounter;
};