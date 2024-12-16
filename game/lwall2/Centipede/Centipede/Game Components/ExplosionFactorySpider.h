#pragma once

#include "TEAL\CommonElements.h"
#include <list>


// Forward declarations
class GameObject;
class ExplosionPoolSpider;

class ExplosionFactorySpider
{
public:
	ExplosionFactorySpider();
	ExplosionFactorySpider(const ExplosionFactorySpider&) = delete;
	ExplosionFactorySpider& operator=(const ExplosionFactorySpider&) = delete;
	~ExplosionFactorySpider();


	void CreateExplosion(sf::Vector2f location, int val);

	static void RecycleExplosion(GameObject* b);

private:

	static ExplosionPoolSpider* myExplosionPool;

};