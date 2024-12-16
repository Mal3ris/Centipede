#pragma once

#include "TEAL\CommonElements.h"
#include <list>


// Forward declarations
class FleaPool;
class GameObject;
class MushroomSpawner;
class FleaSpawner;
class Flea;

class FleaFactory
{
public:
	FleaFactory(MushroomSpawner* mushroomGrid, FleaSpawner* fleaSpawner);
	FleaFactory(const FleaFactory&) = delete;
	FleaFactory& operator=(const FleaFactory&) = delete;
	~FleaFactory();


	void CreateFlea(sf::Vector2f location, float speed, int frequency);

	static void RecycleFlea(GameObject* b);

	void recallAll();

	void removeSpecific(Flea* b);

private:
	
	static FleaPool* myFleaPool;

	static MushroomSpawner* myMushroomGrid;

	static FleaSpawner* myFleaSpawner;
	
	std::list<Flea*> fleaList;

};