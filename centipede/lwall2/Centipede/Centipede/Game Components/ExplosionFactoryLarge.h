#pragma once

#include "TEAL\CommonElements.h"
#include <list>


// Forward declarations
class GameObject;
class ExplosionPoolLarge;

class ExplosionFactoryLarge
{
public:
	ExplosionFactoryLarge();
	ExplosionFactoryLarge(const ExplosionFactoryLarge&) = delete;
	ExplosionFactoryLarge& operator=(const ExplosionFactoryLarge&) = delete;
	~ExplosionFactoryLarge();


	void CreateExplosion(sf::Vector2f location);

	static void RecycleExplosion(GameObject* b);

private:

	static ExplosionPoolLarge* myExplosionPool;

};
