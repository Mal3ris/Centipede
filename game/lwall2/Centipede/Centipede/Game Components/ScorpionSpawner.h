#pragma once

//Scorpion Spawner for Spawning Scorpions

#include "TEAL/CommonElements.h"
#include "FileRead.h"
#include "CritterStructs.h"

class MushroomSpawner;
class ScorpionFactory;
class ScorpionLoop;

class ScorpionSpawner
{
public:
	ScorpionSpawner() = default;
	ScorpionSpawner(const ScorpionSpawner&) = delete;
	ScorpionSpawner& operator=(const ScorpionSpawner&) = delete;
	~ScorpionSpawner() = default;

	void Initialize();

	void CancelAlarms();

	void spawnScorpion();

	void setScorpionFactory(ScorpionFactory* ScorpionFactory);

	void restartAlarm();

	void waveSettings(ScorpionData& pSD);

private:
	static ScorpionFactory* myScorpionFactory;

	ScorpionLoop* myLittleLoop = nullptr;

	float speed = 0;
	bool isActive = false;
	float SPAWNTIME = 8.0f;
	int BOTTOMZONE = 8;
	int TOPZONE = 5;
};
