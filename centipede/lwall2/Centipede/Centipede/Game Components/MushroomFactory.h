#pragma once

#include "TEAL\CommonElements.h"
#include "GridConstants.h"

// Forward declarations
class MushroomPool;
class GameObject;
class MushroomSpawner;

class MushroomFactory
{
public:
	MushroomFactory(MushroomSpawner* pMG);
	MushroomFactory(const MushroomFactory&) = delete;
	MushroomFactory& operator=(const MushroomFactory&) = delete;
	~MushroomFactory();


	void CreateMushroom(sf::Vector2f location);
	void DestroyMushroom(sf::Vector2f location);
	void clearPlayerSpawn();

	void Terminate();

	static void RecycleMushroom(GameObject* b);

private:
	
	static MushroomPool* myMushroomPool;

	static MushroomSpawner* myMushroomGrid;

	

};
