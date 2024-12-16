#include "CentipedeSpawner.h"
#include "MushroomSpawner.h"
#include "CentipedeFactory.h"
#include "CentiBodFactory.h"
#include "Centipede.h"
#include "CentiBod.h"
#include "CentipedeLoop.h"
#include "GridConstants.h"

CentipedeFactory* CentipedeSpawner::myCentipedeFactory = nullptr;
CentiBodFactory*  CentipedeSpawner::myCentiBodFactory = nullptr;
MushroomSpawner*  CentipedeSpawner::myMushroomGrid = nullptr;

CentipedeSpawner::CentipedeSpawner(MushroomSpawner* pMS, CentipedeFactory* pCF, 
	CentiBodFactory* pCBF) 
{
	myLittleLoop = nullptr;
	myMushroomGrid = pMS;
	myCentipedeFactory = pCF;
	myCentiBodFactory = pCBF;
	speed = 0;
	len = 0;
	SoloStartActive = false;
	numSoloStart = 0;
	SoloBottomActive = false;
	numSoloBottom = 0;
	SoloBottomFrequency = 0;
}

void CentipedeSpawner::SpawnCentipede(int length) {
	
	float tmpStartX = (float)((rand() % 30 + 1)* GridConstants::CELLSIZE)
		- GridConstants::HALFCELLSIZE;
	float tmpStartY = -1 * GridConstants::CELLSIZE
		+ GridConstants::HALFCELLSIZE;

	bool dir = rand() % 2;
	
	Centipede* tmpCenti = myCentipedeFactory->CreateCentipede(
		sf::Vector2f(tmpStartX, tmpStartY), myMushroomGrid, dir);
	if (dir == true) {
		if (length > 1) {
			CentiBod* tmpCurrBod = myCentiBodFactory->CreateCentiBod(
				sf::Vector2f(tmpStartX - GridConstants::CELLSIZE, tmpStartY), myMushroomGrid, myCentipedeFactory, dir);

			tmpCenti->setNextBod(tmpCurrBod);
			tmpCurrBod->setPrevHead(tmpCenti);

			if (length > 2) {
				for (int i = 2; i < length; i++) {
					CentiBod* tmpNextBod = myCentiBodFactory->CreateCentiBod(
						sf::Vector2f(tmpStartX - i * GridConstants::CELLSIZE, tmpStartY), myMushroomGrid, myCentipedeFactory, dir);
					tmpCurrBod->setNextBod(tmpNextBod);
					tmpNextBod->setPrevBod(tmpCurrBod);
					tmpCurrBod = tmpNextBod;
				}
				tmpCurrBod->setNextBod(nullptr);
			}
		}
	}
	else {
		if (length > 1) {
			CentiBod* tmpCurrBod = myCentiBodFactory->CreateCentiBod(
				sf::Vector2f(tmpStartX + GridConstants::CELLSIZE, tmpStartY), myMushroomGrid, myCentipedeFactory, dir);

			tmpCenti->setNextBod(tmpCurrBod);
			tmpCurrBod->setPrevHead(tmpCenti);

			if (length > 2) {
				for (int i = 2; i < length; i++) {
					CentiBod* tmpNextBod = myCentiBodFactory->CreateCentiBod(
						sf::Vector2f(tmpStartX + i * GridConstants::CELLSIZE, tmpStartY), myMushroomGrid, myCentipedeFactory, dir);
					tmpCurrBod->setNextBod(tmpNextBod);
					tmpNextBod->setPrevBod(tmpCurrBod);
					tmpCurrBod = tmpNextBod;
				}
				tmpCurrBod->setNextBod(nullptr);
			}
		}
	}
}

void CentipedeSpawner::SpawnBottomCentipede() {

	bool dir = rand() % 2;

	float tmpStartX;

	if (dir == false) {
		tmpStartX = 0 - GridConstants::HALFCELLSIZE;
	}
	else {
		tmpStartX = (GridConstants::GRIDWIDTH + 1) * GridConstants::CELLSIZE
			- GridConstants::HALFCELLSIZE;
	}
	


	float tmpStartY = (GridConstants::PLAYZONE-1) * GridConstants::CELLSIZE
		+ GridConstants::HALFCELLSIZE;

	Centipede* tmpCenti = myCentipedeFactory->CreateCentipede(
		sf::Vector2f(tmpStartX, tmpStartY), myMushroomGrid, dir);
}

void CentipedeSpawner::Initialize() {
	myLittleLoop = new CentipedeLoop(this);
}

void CentipedeSpawner::CancelAlarms() {
	//all alarms in loop
	for (int i = 0; i < 5; i++) {
		myLittleLoop->AlarmCancel(i);
	}
	
}

void CentipedeSpawner::startWave() {
	SpawnCentipede(len);
	if (SoloStartActive) {
		for (int i = 0; i < numSoloStart; i++) {
			SpawnCentipede(1);
		}
	}
	if (SoloBottomActive) {
		for (int i = 0; i < numSoloBottom; i++) {
			myLittleLoop->SetAlarm(i, i * SoloBottomFrequency);
		}
	}
}

void CentipedeSpawner::waveSettings(CentipedeData& pCD) {
	
	speed = pCD.speed;
	len = pCD.length;
	SoloStartActive = pCD.soloStartActive;
	numSoloStart = pCD.soloStartCount;
	SoloBottomActive = pCD.soloPlayerActive;
	numSoloBottom = pCD.soloPlayerCount;
	SoloBottomFrequency = pCD.soloPlayerFrequency;
}
