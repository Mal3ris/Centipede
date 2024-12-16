#include "TEAL\CommonElements.h"
#include "TileFactory.h"
#include "Tile.h"
#include "TilePool.h"
#include "MushroomSpawner.h"

TileFactory* TileFactory::ptrInstance = nullptr;

TilePool* TileFactory::myTilePool = nullptr;

MushroomSpawner* TileFactory::myMushroomGrid = nullptr;

//Creates Tile Pool
TileFactory::TileFactory() {
	myTilePool = new TilePool();
}

//Sets my Mushroom Grid
void TileFactory::privSetGrid(MushroomSpawner* pMG) {
	myMushroomGrid = pMG;
}

//Destructor
TileFactory::~TileFactory() {
}

//Returns Factory
TileFactory* TileFactory::privGetFactory() {
	return this;
}

//Cleans Extra Pointers
void TileFactory::Terminate() {
	delete myTilePool;
	delete ptrInstance;
	ptrInstance = nullptr;
}

//Spawns Tile At given location and updates Grid
void TileFactory::privCreateTile(sf::Vector2f location) {
	Tile* tempTile = myTilePool->GetTile();
	tempTile->SetExternalManagement(RecycleTile);

	tempTile->Initialize(location, myMushroomGrid);

	tileList.push_back(tempTile);

	myMushroomGrid->setCell((int)(((location.x) - GridConstants::HALFCELLSIZE) / GridConstants::CELLSIZE), (int)(((location.y) - GridConstants::HALFCELLSIZE) / GridConstants::CELLSIZE), tempTile);
}

//Recycles Tile
void TileFactory::RecycleTile(GameObject* b) {
	myTilePool->ReturnTile(static_cast<Tile*>(b));
}

//Recalls Tile
void TileFactory::privRecallAll() {
	while (tileList.empty() == false) {
		tileList.front()->MarkForDestroy();
		tileList.pop_front();
	}
}


