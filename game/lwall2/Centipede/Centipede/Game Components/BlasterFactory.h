#pragma once

#include "TEAL\CommonElements.h"
#include <list>

//Forward declarations
class BlasterPool;
class GameObject;
class Blaster;
class BulletFactory;
class MovementStrategy;

class BlasterFactory
{
public:
	BlasterFactory() = default;
	BlasterFactory(BulletFactory* b);
	BlasterFactory(const BlasterFactory&) = delete;
	BlasterFactory& operator=(const BlasterFactory&) = delete;
	~BlasterFactory();

	static void RecycleBlaster(GameObject* b);

	void SpawnBlaster();


private:

	static BlasterPool* myBlasterPool;
	static BulletFactory* myBulletFactory;

	static MovementStrategy* myStrat;

};