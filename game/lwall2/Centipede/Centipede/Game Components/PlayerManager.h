#pragma once
#include "TEAL\CommonElements.h"

class MovementStrategy;

struct Player {
	int score = 0;
	int lives = 3;
	int waveLevel = 1;

	char* currPat = nullptr;
};

class PlayerManager
{
private:
	
	static PlayerManager* ptrInstance;

	PlayerManager();
	PlayerManager(const PlayerManager&) = delete;
	PlayerManager& operator=(const PlayerManager&) = delete;
	~PlayerManager() = default;

	static PlayerManager& Instance()
	{
		if (ptrInstance == nullptr)
			ptrInstance = new PlayerManager();
		return *ptrInstance;
	};

	int MAXHEALTH = 6;

	Player currPlayer;

	//0 = P1
	//1 = P2 //Removed -> Didnt Clean Out
	//2 = Ai

	Player players[3];

	void privSetPlayer(int num);
	Player privGetPlayer();
	void privSetWaveNum(int num);

	void privAddScore(int num);
	void privSetScore(int num);
	void privChangeHealth(int num);

public:
	static void setPlayer(int num) { Instance().privSetPlayer(num); };
	static Player getPlayer() { return Instance().privGetPlayer(); };
	static void setWaveNum(int num) { Instance().privSetWaveNum(num); }
	static void addScore(int num) { Instance().privAddScore(num); }
	static void setScore(int num) { Instance().privSetScore(num); }
	static void changeHealth(int num) { Instance().privChangeHealth(num); }

	static void Terminate();
};