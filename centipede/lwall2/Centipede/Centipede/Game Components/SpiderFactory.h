#pragma once

//Spider Factory In Charge of Create Spiders

#include "TEAL\CommonElements.h"
#include <list>

// Forward declarations
class SpiderPool;
class GameObject;
class MushroomSpawner;
class SpiderSpawner;
class Spider;
class CommandSound;

class SpiderFactory
{
public:
	SpiderFactory();
	SpiderFactory(const SpiderFactory&) = delete;
	SpiderFactory& operator=(const SpiderFactory&) = delete;
	~SpiderFactory();


	void CreateSpider(sf::Vector2f location, bool moveRight, float speed);

	static void RecycleSpider(GameObject* b);

	void recallAll();

	void removeSpecific(Spider* b);
	
	void setSpawner(SpiderSpawner*);

	void Pause();
	void Play();

private:
	
	static SpiderPool* mySpiderPool;

	static MushroomSpawner* myMushroomGrid;

	static SpiderSpawner* mySpiderSpawner;

	static std::list<Spider*> spiderList;
	
	CommandSound* pSound;

};
