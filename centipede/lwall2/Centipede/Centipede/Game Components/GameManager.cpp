#include "TEAL/CommonElements.h"
#include "GameManager.h"
#include "GameManagerLoop.h"

#include "CritterStructs.h"

#include "PlayerManager.h"
#include "BlasterFactory.h"
#include "BulletFactory.h"

#include "MushroomSpawner.h"
#include "MushroomFactory.h"

#include "FleaSpawner.h"
#include "FleaFactory.h"

#include "CentipedeSpawner.h"
#include "CentipedeFactory.h"
#include "CentiBodFactory.h"

#include "ScorpionSpawner.h"
#include "ScorpionFactory.h"

#include "SpiderSpawner.h"
#include "SpiderFactory.h"

#include "ExplosionFactorySmall.h"
#include "ExplosionFactoryLarge.h"
#include "ExplosionFactorySpider.h"

#include "ScoreManager.h"
#include "SoundManager.h"

#include "WriteText.h"
#include "FileRead.h"

#include "TileFactory.h"
#include "CommandSound.h"


GameManager* GameManager::ptrInstance = nullptr;

GameManagerLoop* GameManager::myLittleLoop = nullptr;

BulletFactory* GameManager::myBulletFactory = nullptr;
BlasterFactory* GameManager::myBlasterFactory = nullptr;

MushroomSpawner* GameManager::myMushroomGrid = nullptr;
MushroomFactory* GameManager::myMushroomFactory = nullptr;

FleaSpawner* GameManager::myFleaSpawner = nullptr;
FleaFactory* GameManager::myFleaFactory = nullptr;

CentipedeSpawner* GameManager::myCentiSpawner = nullptr;
CentipedeFactory* GameManager::myCentiFactory = nullptr;
CentiBodFactory* GameManager:: myBodFactory = nullptr;

ScorpionSpawner* GameManager::myScorpiSpawner = nullptr;
ScorpionFactory* GameManager::myScorpiFactory = nullptr;

SpiderSpawner* GameManager::mySpidSpawner = nullptr;
SpiderFactory* GameManager::mySpidFactory = nullptr;

ExplosionFactorySmall* GameManager::mySmallExpFact = nullptr;
ExplosionFactoryLarge* GameManager::myLargeExpFact = nullptr;
ExplosionFactorySpider* GameManager::mySpidExpFact = nullptr;

FileRead* GameManager::myFile = nullptr;

//Creates Every Factory and Spawner the game needs besides Tiles
//Also in charge of Starting File Read
GameManager::GameManager() {


	myBulletFactory = new BulletFactory();
	myBlasterFactory = new BlasterFactory(myBulletFactory);

	myMushroomGrid = new MushroomSpawner();
	myMushroomFactory = new MushroomFactory(myMushroomGrid);
	myMushroomGrid->setMushroomFactory(myMushroomFactory);


	myFleaSpawner = new FleaSpawner(myMushroomGrid);
	myFleaFactory = new FleaFactory(myMushroomGrid, myFleaSpawner);
	myFleaSpawner->setFleaFactory(myFleaFactory);
	myMushroomGrid->setFleaSpawner(myFleaSpawner);

	myCentiFactory = new CentipedeFactory();
	myBodFactory = new CentiBodFactory();
	myCentiSpawner = new CentipedeSpawner(myMushroomGrid, myCentiFactory,
		myBodFactory);

	myScorpiSpawner = new ScorpionSpawner();
	myScorpiFactory = new ScorpionFactory(myScorpiSpawner);
	myScorpiSpawner->setScorpionFactory(myScorpiFactory);

	mySpidSpawner = new SpiderSpawner();
	mySpidFactory = new SpiderFactory();
	mySpidSpawner->setSpiderFactory(mySpidFactory);
	mySpidFactory->setSpawner(mySpidSpawner);

	mySmallExpFact = new ExplosionFactorySmall();
	myLargeExpFact = new ExplosionFactoryLarge();
	mySpidExpFact = new ExplosionFactorySpider();

	myFile = new FileRead();

	TileFactory::setGrid(myMushroomGrid);

}

//In charge of making Little Buddy Loop and setting sound properly
//Also starts initial wave
void GameManager::privInitialize(std::string screen) {

	myLittleLoop = new GameManagerLoop(screen);

	//NECESSARY CAUSE OF SOUND WOULD PERSIST INTO HIGHSCORE (REASON UNKNOWN)
	if (screen == "attractor" || screen == "highscore") {
		SoundManager::ForceMute(myCentiFactory, mySpidFactory, myScorpiFactory);
	}
	else {
		SoundManager::StartSound(myCentiFactory, mySpidFactory, myScorpiFactory);
	}

	if (screen != "highscore") {
		myMushroomGrid->populateMushrooms();
		myScorpiSpawner->Initialize();
		mySpidSpawner->Initialize();
		myCentiSpawner->Initialize();

		myBlasterFactory->SpawnBlaster();
		GameManager::CreateWave(1);
	}
}

//Mute
void GameManager::privMute() {
	SoundManager::Mute(myCentiFactory, mySpidFactory, myScorpiFactory);
}

//Used to kill sounds when swapping scenes and clean mushroom grid
//plus disconnect from loop
void GameManager::privSwap() {

	myMushroomGrid->Clean();

	myScorpiFactory->Pause();
	myCentiFactory->Pause();
	mySpidFactory->Pause();

	myLittleLoop = nullptr;
}

//Runs necessary Level Complete work
void GameManager::privLevelComplete() {
	myCentiSpawner->CancelAlarms();
	myScorpiSpawner->CancelAlarms();
	mySpidSpawner->CancelAlarms();

	PlayerManager::setWaveNum(PlayerManager::getPlayer().waveLevel + 1);

	GameManager::CreateWave(PlayerManager::getPlayer().waveLevel);
}

//All Player Death Necessities
void GameManager::privPlayerDeath() {

	PlayerManager::changeHealth(-1);

	myBulletFactory->recallAll();
	myBodFactory->recallAll();
	myCentiSpawner->CancelAlarms();
	myCentiFactory->recallAll();
	myFleaFactory->recallAll();
	myScorpiFactory->recallAll();
	myScorpiSpawner->CancelAlarms();
	mySpidFactory->recallAll();
	mySpidSpawner->CancelAlarms();
	
	ScoreManager::ProcessScores();
	myLittleLoop->Write();

	//Checks player lives with different actions for Player vs AI
	if (PlayerManager::getPlayer().lives <= 0) {
		if (PlayerManager::getPlayer().currPat != "ai") {
			PlayerManager::setWaveNum(1);
			GameManager::SwapScene();
			ScoreManager::CheckHighScore();
		}
		else {
			PlayerManager::addScore(-1 * PlayerManager::getPlayer().score);
		}
		PlayerManager::changeHealth(3);
	}
	
	myMushroomGrid->resetGrid();
}

//Runs once all mushrooms are reset Starts Wave too
void GameManager::privStartPlay() {
	myBlasterFactory->SpawnBlaster();
	myMushroomGrid->clearPlayerSpawn();
	myFleaSpawner->spawnFlea();

	ScoreManager::ProcessScores();
	myLittleLoop->Write();

	GameManager::CreateWave(PlayerManager::getPlayer().waveLevel);
}

//In charge of Sending all Wave Commands
void GameManager::privCreateWave(int waveNum) {
	WaveData wave = myFile->getWave(waveNum);

	mySpidSpawner->waveSettings(wave.spiderData);

	myScorpiSpawner->waveSettings(wave.scorpionData);

	myFleaSpawner->waveSettings(wave.fleaData);

	myCentiSpawner->waveSettings(wave.centipedeData);
	myCentiSpawner->startWave();
}

//Makes Explosions
// 0 is small, 1 is big, 2 is spider
void GameManager::privSpawnExplosion(int i, sf::Vector2f pos) {
	if (i == 0) {
		mySmallExpFact->CreateExplosion(pos);
	}
	else if (i == 1) {
		myLargeExpFact->CreateExplosion(pos);
	}
}
void GameManager::privSpawnExplosion(int i, sf::Vector2f pos, int val) {
	//Sanity test
	if (i == 2) {
		mySpidExpFact->CreateExplosion(pos, val);
	}
}

//Cleans up
void GameManager::Terminate() {

	delete myMushroomGrid;
	delete myMushroomFactory;

	delete myBulletFactory;
	delete myBlasterFactory;

	delete myCentiSpawner;
	delete myCentiFactory;
	delete myBodFactory;

	delete myFleaSpawner;
	delete myFleaFactory;

	delete myScorpiSpawner;
	delete myScorpiFactory;

	delete mySpidSpawner;
	delete mySpidFactory;

	delete mySmallExpFact;
	delete myLargeExpFact;
	delete mySpidExpFact;

	delete myFile;

	delete ptrInstance;
	ptrInstance = nullptr;
}