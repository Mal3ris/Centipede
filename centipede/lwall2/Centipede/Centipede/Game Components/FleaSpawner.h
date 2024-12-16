#pragma once

#include "TEAL/CommonElements.h"
#include "FileRead.h"
#include "CritterStructs.h"

class MushroomSpawner;
class FleaFactory;

class FleaSpawner
{
public:
	FleaSpawner(MushroomSpawner* mushroomGrid);
	FleaSpawner(const FleaSpawner&) = delete;
	FleaSpawner& operator=(const FleaSpawner&) = delete;
	~FleaSpawner() = default;

	void spawnFlea();

	void setFleaFactory(FleaFactory* fleaFactory);
	void waveSettings(FleaData& pFD);
private:
	static MushroomSpawner* myMushroomGrid;
	static FleaFactory* myFleaFactory;
	int mushroomsNeeded;
	int frequency;
	float speed;
	bool isActive;
};
