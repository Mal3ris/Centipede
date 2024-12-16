#pragma once

//Factory In Charge of Tiles

#include "TEAL\CommonElements.h"
#include "GridConstants.h"



// Forward declarations
class TilePool;
class GameObject;
class MushroomSpawner;
class Tile;

class TileFactory
{
public: //KNOW SHOULD BE PRIVATE GET LINKING ERRORS

	static TileFactory* ptrInstance;

	TileFactory();
	TileFactory(const TileFactory&) = delete;
	TileFactory& operator=(const TileFactory&) = delete;
	~TileFactory();

	static TileFactory& Instance()
	{
		if (ptrInstance == nullptr)
			ptrInstance = new TileFactory();
		return *ptrInstance;
	};

public:

	static void Terminate();

	static void RecycleTile(GameObject* b);


	static void recallAll() { Instance().privRecallAll(); };
	static void setGrid(MushroomSpawner* pMG) { Instance().privSetGrid(pMG); };
	static TileFactory* getFactory(){ return Instance().privGetFactory(); };
	static void CreateTile(sf::Vector2f location) { Instance().privCreateTile(location); };

private:

	void privCreateTile(sf::Vector2f location);
	void privRecallAll();
	TileFactory* privGetFactory();

	void privSetGrid(MushroomSpawner* pMG);
	
	static TilePool* myTilePool;

	static MushroomSpawner* myMushroomGrid;

	std::list<Tile*> tileList;

};
