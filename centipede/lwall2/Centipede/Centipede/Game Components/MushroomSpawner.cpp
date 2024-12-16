#include "MushroomSpawner.h"
#include "FleaSpawner.h"
#include "Mushroom.h"
#include "MushroomFactory.h"
#include "MushroomLoop.h"
#include "Tile.h"

MushroomFactory* MushroomSpawner::myMushroomFactory = nullptr;
FleaSpawner* MushroomSpawner::myFleaSpawner = nullptr;
int MushroomSpawner::mushroomsPlayAreaCount = 0;
float MushroomSpawner::RESPAWNRATE = .1f;
Tile* MushroomSpawner::mushroomGrid[GridConstants::GRIDHEIGHT][GridConstants::GRIDWIDTH];

MushroomSpawner::MushroomSpawner()
{
	for (int i = 0; i < GridConstants::GRIDHEIGHT; i++) {
		for (int j = 0; j < GridConstants::GRIDWIDTH; j++) {
			mushroomGrid[i][j] = nullptr;
		}
	}
	myFleaSpawner = nullptr;
	myMushroomFactory = nullptr;
	myLittleLoop = nullptr;
}

void MushroomSpawner::populateMushrooms() {
	myLittleLoop = new MushroomLoop();
	for (int i = 0; i < GridConstants::GRIDHEIGHT; i++) {
		for (int j = 0; j < GridConstants::GRIDWIDTH; j++) {
			if (rand() % 100 + 1 <= FREQUENCY) {
				spawnMushroomAt(sf::Vector2f((float)(j * GridConstants::CELLSIZE + GridConstants::HALFCELLSIZE), (float)(i * GridConstants::CELLSIZE + GridConstants::HALFCELLSIZE)));
			}
		}
	}
	clearPlayerSpawn();
}


void MushroomSpawner::spawnMushroomAt(sf::Vector2f location) {
	if (mushroomAt(location) == MushroomState::BLOCKED || mushroomAt(location) == MushroomState::POISON ||
		(int)(((location.y) - GridConstants::HALFCELLSIZE) / GridConstants::CELLSIZE) >= GridConstants::GRIDHEIGHT) {
		return;
	}
	myMushroomFactory->CreateMushroom(location);

	if ((int)(((location.y) - GridConstants::HALFCELLSIZE) / GridConstants::CELLSIZE) >= GridConstants::PLAYZONE) {
		mushroomsPlayAreaCount++;
	}

}

void MushroomSpawner::Clean() {
	for (int i = 0; i < GridConstants::GRIDHEIGHT; i++) {
		for (int j = 0; j < GridConstants::GRIDWIDTH; j++) {
			mushroomGrid[i][j] = nullptr;
		}
	}
	mushroomsPlayAreaCount = 0;
}

void MushroomSpawner::destroyMushroomAt(sf::Vector2f location) {
	if (mushroomAt(location) == MushroomState::EMPTY) {
		return;
	}
	
	myMushroomFactory->DestroyMushroom(location);
	
	if ((int)(((location.y) - GridConstants::HALFCELLSIZE) / GridConstants::CELLSIZE) >= GridConstants::PLAYZONE) {
		mushroomsPlayAreaCount--;
		myFleaSpawner->spawnFlea();
	}
}

MushroomSpawner::MushroomState MushroomSpawner::mushroomAt(sf::Vector2f location) {
	if ((int)(((location.x) - GridConstants::HALFCELLSIZE) / GridConstants::CELLSIZE) < 0 || (int)(((location.x) - GridConstants::HALFCELLSIZE) / GridConstants::CELLSIZE) >= GridConstants::GRIDWIDTH) {
		return MushroomState::BLOCKED;
	}
	if ((int)(((location.y) - GridConstants::HALFCELLSIZE) / GridConstants::CELLSIZE) >= GridConstants::GRIDHEIGHT) {
		return MushroomState::EMPTY;
	}
	if (mushroomGrid[(int)(((location.y) - GridConstants::HALFCELLSIZE) / GridConstants::CELLSIZE)][(int)(((location.x) - GridConstants::HALFCELLSIZE) / GridConstants::CELLSIZE)] == nullptr) {
		return MushroomState::EMPTY;
	} 
	else if (mushroomGrid[(int)(((location.y) - GridConstants::HALFCELLSIZE) / GridConstants::CELLSIZE)][(int)(((location.x) - GridConstants::HALFCELLSIZE) / GridConstants::CELLSIZE)]->getPoison()) {
		return MushroomState::POISON;
	}
	else {
		return MushroomState::BLOCKED;
	}
}

void MushroomSpawner::clearPlayerSpawn() {
	myMushroomFactory->clearPlayerSpawn();
}



void MushroomSpawner::remakeGrid() {
	for (int i = 0; i < GridConstants::GRIDHEIGHT; i++) {
		for (int j = 0; j < GridConstants::GRIDWIDTH; j++) {
			destroyMushroomAt(sf::Vector2f((float)(j * GridConstants::CELLSIZE + GridConstants::HALFCELLSIZE), (float)(i * GridConstants::CELLSIZE + GridConstants::HALFCELLSIZE)));
			if (rand() % 100 + 1 <= FREQUENCY) {
				spawnMushroomAt(sf::Vector2f((float)(j * GridConstants::CELLSIZE + GridConstants::HALFCELLSIZE), (float)(i * GridConstants::CELLSIZE + GridConstants::HALFCELLSIZE)));
			}
		}
	}
	clearPlayerSpawn();
}

void MushroomSpawner::resetGrid() {
	for (int i = 0; i < GridConstants::GRIDHEIGHT; i++) {
		for (int j = 0; j < GridConstants::GRIDWIDTH; j++) {
			if (mushroomGrid[j][i] != nullptr) {
				mushroomGrid[j][i]->SetAlarm(0, i * RESPAWNRATE);
			}
		}
	}
	myLittleLoop->SetAlarm(0, RESPAWNRATE * GridConstants::GRIDWIDTH);
}

int MushroomSpawner::getMushroomPlayAreaCount() {
	return mushroomsPlayAreaCount;
}

void MushroomSpawner::setFleaSpawner(FleaSpawner* fleaSpawner) {
	myFleaSpawner = fleaSpawner;
}

void MushroomSpawner::setMushroomFactory(MushroomFactory* pMF) {
	myMushroomFactory = pMF;
}


void MushroomSpawner::setCell(int x, int y, Tile* value) {
	mushroomGrid[y][x] = value;
}

Tile* MushroomSpawner::getCell(int x, int y) {
	return mushroomGrid[y][x];
}