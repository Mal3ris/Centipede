#pragma once

#include "TEAL\CommonElements.h"
#include <list>


// Forward declarations
class GameObject;
class ExplosionPoolSmall;

class ExplosionFactorySmall
{
public:
	ExplosionFactorySmall();
	ExplosionFactorySmall(const ExplosionFactorySmall&) = delete;
	ExplosionFactorySmall& operator=(const ExplosionFactorySmall&) = delete;
	~ExplosionFactorySmall();


	void CreateExplosion(sf::Vector2f location);

	static void RecycleExplosion(GameObject* b);

private:

	static ExplosionPoolSmall* myExplosionPool;

};