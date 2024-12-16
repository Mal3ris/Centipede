#pragma once

//Spider Spawner in charger of spawning spiders and taking in wave data

#include "TEAL/CommonElements.h"
#include "GridConstants.h"
#include "FileRead.h"
#include "CritterStructs.h"

class MushroomSpawner;
class SpiderFactory;
class SpiderLoop;

class SpiderSpawner
{
public:
	SpiderSpawner() = default;
	SpiderSpawner(const SpiderSpawner&) = delete;
	SpiderSpawner& operator=(const SpiderSpawner&) = delete;
	~SpiderSpawner() = default;

	void Initialize();

	void spawnSpider();

	void CancelAlarms();

	void setSpiderFactory(SpiderFactory* SpiderFactory);

	void resetAlarm();

	void waveSettings(SpiderData& pSD);
private:
	static SpiderFactory* mySpiderFactory;

	SpiderLoop* myLittleLoop = nullptr;

	float speed = 0;
	bool isActive = false;
	float SPAWNTIME = 8.0f;
	int BOTTOMZONE = 15;
	int TOPZONE = GridConstants::PLAYZONE;
};