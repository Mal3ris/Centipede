#pragma once

#include "TEAL\CommonElements.h"
#include "GridConstants.h"



class Mushroom;
class FleaSpawner;
class MushroomFactory;
class Tile;
class MushroomLoop;

class MushroomSpawner
{
public:

	enum class MushroomState { EMPTY, BLOCKED, POISON, BOTTOM };

	MushroomSpawner();
	MushroomSpawner(const MushroomSpawner&) = delete;
	MushroomSpawner& operator=(const MushroomSpawner&) = delete;
	~MushroomSpawner() = default;

	void populateMushrooms();
	void spawnMushroomAt(sf::Vector2f location);
	void destroyMushroomAt(sf::Vector2f location);
	MushroomState mushroomAt(sf::Vector2f location);
	void remakeGrid();
	void resetGrid();
	void Clean();
	void clearPlayerSpawn();

	int getMushroomPlayAreaCount();
	void setFleaSpawner(FleaSpawner* fleaSpawner);
	void setMushroomFactory(MushroomFactory* pMF);
	void setCell(int x, int y, Tile* value);
	Tile* getCell(int x, int y);

private:
	static Tile* mushroomGrid[GridConstants::GRIDHEIGHT][GridConstants::GRIDWIDTH];

	static const int FREQUENCY = 4;
	//dunno why cant be const
	static float RESPAWNRATE;
	static int mushroomsPlayAreaCount;
	static FleaSpawner* myFleaSpawner;

	static MushroomFactory* myMushroomFactory;

	MushroomLoop* myLittleLoop;
};
