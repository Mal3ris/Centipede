#include "PlayerManager.h"
#include "MovementStrategy.h"

PlayerManager* PlayerManager::ptrInstance = nullptr;

PlayerManager::PlayerManager() {
	for (int i = 0; i < sizeof(players) / sizeof(players[0]); i++) {
		if (i <= 1) {
			players[i].currPat = "keys";
		}
		else {
			players[i].lives = 3;
			players[i].currPat = "ai";
		}
	}
	
}

void PlayerManager::privSetWaveNum(int num) {
	currPlayer.waveLevel = num;
}

void PlayerManager::privAddScore(int val) {
	currPlayer.score += val;
}

void PlayerManager::privSetScore(int val) {
	currPlayer.score = val;
}

void PlayerManager::privChangeHealth(int val) {
	currPlayer.lives += val;

	if (currPlayer.lives > MAXHEALTH) {
		currPlayer.lives = MAXHEALTH;
	}
	
}

void PlayerManager::privSetPlayer(int num) {
	currPlayer = players[num];
}

Player PlayerManager::privGetPlayer() {
	return currPlayer;
}

void PlayerManager::Terminate() {
	delete ptrInstance;
	ptrInstance = nullptr;
}