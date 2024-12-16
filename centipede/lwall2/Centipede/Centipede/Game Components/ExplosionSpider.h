#pragma once

#include "TEAL\CommonElements.h"


class ExplosionSpider : public GameObject
{
public:
	ExplosionSpider();
	ExplosionSpider(const ExplosionSpider&) = delete;
	ExplosionSpider& operator=(const ExplosionSpider&) = delete;
	~ExplosionSpider() = default;

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	virtual void Initialize(sf::Vector2f p, int val);

	virtual void Alarm0();


private:
	AnimatedSprite MainSprite;
	const float WAITTIME = 1.0f;
};