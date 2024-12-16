// GameStart.cpp
// Andre Berthiaume, July 2019

#include "Game.h"
#include "..\ScoreManager.h"
#include "..\SoundManager.h"
#include "..\PlayerManager.h"
#include "..\TileFactory.h"
#include "..\GameManager.h"

void Game::GameEnd()
{
	GameManager::Terminate();
	ScoreManager::DeleteSelf();
	SoundManager::DeleteSelf();
	PlayerManager::Terminate();
	TileFactory::Terminate();
	
	// Empty for now
}