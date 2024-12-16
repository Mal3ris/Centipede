#include "FleaSpawner.h"
#include "MushroomSpawner.h"
#include "Flea.h"
#include "GridConstants.h"
#include "FleaFactory.h"

MushroomSpawner* FleaSpawner::myMushroomGrid = nullptr;
FleaFactory* FleaSpawner::myFleaFactory = nullptr;

FleaSpawner::FleaSpawner(MushroomSpawner* mushroomGrid)
{
	myMushroomGrid = mushroomGrid;
	//Temp nums
	frequency = 20;
	isActive = false;
	speed = 2;
	mushroomsNeeded = 5;
}

void FleaSpawner::spawnFlea() {
	if (isActive == false) {
		return;
	}
	if (myMushroomGrid->getMushroomPlayAreaCount() <= mushroomsNeeded) {
		myFleaFactory->CreateFlea(sf::Vector2f((float)((rand() % 30 + 1) * GridConstants::CELLSIZE), 0.0f), speed, frequency);
	}
}

void FleaSpawner::setFleaFactory(FleaFactory* fleaFactory) {
	myFleaFactory = fleaFactory;
}

void FleaSpawner::waveSettings(FleaData& pFD) {
	isActive = pFD.active;
	speed = pFD.speed;
	frequency = pFD.probability;
	mushroomsNeeded = pFD.threshold;
}