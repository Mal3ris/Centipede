#include "SpiderSpawner.h"
#include "MushroomSpawner.h"
#include "Spider.h"
#include "GridConstants.h"
#include "SpiderFactory.h"
#include "SpiderLoop.h"

SpiderFactory* SpiderSpawner::mySpiderFactory = nullptr;

//Creates Little Buddy
void SpiderSpawner::Initialize() {
	myLittleLoop = new SpiderLoop(this);
}

//Sets Spider Fact
void SpiderSpawner::setSpiderFactory(SpiderFactory* SpiderFactory) {
	mySpiderFactory = SpiderFactory;
}

//Picks Side for Spider to Spawn at
void SpiderSpawner::spawnSpider() {
	if (isActive == false) {
		return;
	}
	bool dir = rand() % 2;
	if (dir) {
		mySpiderFactory->CreateSpider(sf::Vector2f(0.0f - GridConstants::HALFCELLSIZE, (float)(TOPZONE * GridConstants::CELLSIZE) - GridConstants::HALFCELLSIZE), dir, speed);
	}
	else {
		mySpiderFactory->CreateSpider(sf::Vector2f(WindowManager::Window().getView().getSize().x + GridConstants::HALFCELLSIZE, (float)(TOPZONE * GridConstants::CELLSIZE) - GridConstants::HALFCELLSIZE), dir, speed);
	}

	myLittleLoop->AlarmCancel(0);
}

//Stops Alarms while resetting
void SpiderSpawner::CancelAlarms() {
	myLittleLoop->AlarmCancel(0);
}

//Resets the alarms
void SpiderSpawner::resetAlarm() {
	myLittleLoop->SetAlarm(0, SPAWNTIME);
}

//Loads in Wave Data
void SpiderSpawner::waveSettings(SpiderData& pSD) {
	isActive = pSD.active;
	SPAWNTIME = pSD.frequency;
	speed = pSD.speed;
	if (isActive) {
		myLittleLoop->SetAlarm(0, SPAWNTIME);
	}
}