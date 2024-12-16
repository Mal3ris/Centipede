#pragma once

//Singleton that Holds All of my Factories and Spawners
//Used to Persist between Scenes
//Also is my wave manager due to already having pointers necessary
//Should have been broken up -> reason time

#include "TEAL\CommonElements.h"
#include "GridConstants.h"

// Forward declarations
class GameManagerLoop;

class BulletFactory;
class BlasterFactory;

class MushroomSpawner;
class MushroomFactory;

class FleaSpawner;
class FleaFactory;

class CentipedeFactory;
class CentiBodFactory;
class CentipedeSpawner;

class ScorpionSpawner;
class ScorpionFactory;

class SpiderSpawner;
class SpiderFactory;

class ExplosionFactorySmall;
class ExplosionFactoryLarge;
class ExplosionFactorySpider;

class FileRead;
class CommandSound;


class GameManager
{
public: //UNDERSTAND SHOULD BE PRIVATE BUT WHEN IT IS GET LINKING ERRORS

	static GameManager* ptrInstance; // used for singleton

	GameManager();
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	~GameManager() = default;

	static GameManager& Instance()
	{
		if (ptrInstance == nullptr)
			ptrInstance = new GameManager();
		return *ptrInstance;
	};

public:
	static void Terminate();

	static void CreateWave(int i) { Instance().privCreateWave(i); };
	static void LevelComplete() { Instance().privLevelComplete(); };
	static void PlayerDeath() { Instance().privPlayerDeath(); };
	static void Mute() { Instance().privMute(); };
	static void SwapScene() { Instance().privSwap(); };
	static void Initialize(std::string s) { Instance().privInitialize(s); };
	static void SpawnExplosion(int i, sf::Vector2f pos) { Instance().privSpawnExplosion(i, pos); };
	static void SpawnExplosion(int i, sf::Vector2f pos, int val) { Instance().privSpawnExplosion(i, pos, val); };
	static void StartPlay() { Instance().privStartPlay(); };

private:

	void privCreateWave(int i);
	void privLevelComplete();
	void privPlayerDeath();
	void privMute();
	void privSwap();
	void privStartPlay();
	void privInitialize(std::string s);
	void privSpawnExplosion(int i, sf::Vector2f pos);
	void privSpawnExplosion(int i, sf::Vector2f pos, int val);


	static GameManagerLoop* myLittleLoop;

	static BulletFactory* myBulletFactory;
	static BlasterFactory* myBlasterFactory;

	static MushroomSpawner* myMushroomGrid;
	static MushroomFactory* myMushroomFactory;

	static FleaSpawner* myFleaSpawner;
	static FleaFactory* myFleaFactory;

	static CentipedeSpawner* myCentiSpawner;
	static CentipedeFactory* myCentiFactory;
	static CentiBodFactory* myBodFactory;

	static ScorpionSpawner* myScorpiSpawner;
	static ScorpionFactory* myScorpiFactory;

	static SpiderSpawner* mySpidSpawner;
	static SpiderFactory* mySpidFactory;

	static ExplosionFactorySmall* mySmallExpFact;
	static ExplosionFactoryLarge* myLargeExpFact;
	static ExplosionFactorySpider* mySpidExpFact;


	static FileRead* myFile;
};
