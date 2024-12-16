#include "ScorpionSpawner.h"
#include "MushroomSpawner.h"
#include "Scorpion.h"
#include "GridConstants.h"
#include "ScorpionFactory.h"
#include "ScorpionLoop.h"

ScorpionFactory* ScorpionSpawner::myScorpionFactory = nullptr;

//Creates Little Buddy Loop
void ScorpionSpawner::Initialize() {
	myLittleLoop = new ScorpionLoop(this);
}

//Sets Up Factory
void ScorpionSpawner::setScorpionFactory(ScorpionFactory* ScorpionFactory) {
	myScorpionFactory = ScorpionFactory;
}

//Picks the Side to Spawn Scorpion and does so
void ScorpionSpawner::spawnScorpion() {
	if (isActive == false) {
		return;
	}
	bool dir = rand() % 2;
	if (dir) {
		myScorpionFactory->CreateScorpion(sf::Vector2f(0.0f - GridConstants::HALFCELLSIZE, (float)((rand() % BOTTOMZONE + TOPZONE) * GridConstants::CELLSIZE) - GridConstants::HALFCELLSIZE), dir, speed);
	}
	else {
		myScorpionFactory->CreateScorpion(sf::Vector2f(WindowManager::Window().getView().getSize().x + GridConstants::HALFCELLSIZE, (float)((rand() % BOTTOMZONE + TOPZONE) * GridConstants::CELLSIZE) - GridConstants::HALFCELLSIZE), dir, speed);
	}
	myLittleLoop->AlarmCancel(0);
}

//Cancels alarms for in between deaths
void ScorpionSpawner::CancelAlarms() {
	myLittleLoop->AlarmCancel(0);
}

//Restarts the alarm after Scorp is offscreen
void ScorpionSpawner::restartAlarm() {
	myLittleLoop->SetAlarm(0, SPAWNTIME);
}

//Loads in Wave settings
void ScorpionSpawner::waveSettings(ScorpionData& pSD) {
	isActive = pSD.active;
	SPAWNTIME = pSD.frequency;
	speed = pSD.speed;
	if (isActive) {
		myLittleLoop->SetAlarm(0, SPAWNTIME);
	}
}