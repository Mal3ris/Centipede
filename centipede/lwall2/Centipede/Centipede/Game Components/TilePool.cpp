#include "TilePool.h"
#include "TEAL\CommonElements.h"
#include "Tile.h"

//Returns Tiles
Tile* TilePool::GetTile() {
	Tile* tempTile;

	if (recycledTile.empty()) {
		//ConsoleMsg::WriteLine("Fresh Tile");
		tempTile = new Tile();
	}
	else {
		//ConsoleMsg::WriteLine("Recycled Tile");
		tempTile = recycledTile.top();
		recycledTile.pop();

		tempTile->RegisterToCurrentScene();
	}

	return tempTile;
}

//Returns Tiles
void TilePool::ReturnTile(Tile* b) {
	recycledTile.push(static_cast<Tile*>(b));
}

//Cleans List of Tiles
TilePool::~TilePool() {
	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledTile.size()) + " Tiles");
	while (!recycledTile.empty())
	{
		delete recycledTile.top();
		recycledTile.pop();
	}
}