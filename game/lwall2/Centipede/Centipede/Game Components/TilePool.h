#pragma once

//Pool For Tiles

#include <stack>

//Forward Declarations
class Tile;

class TilePool
{
public:
	TilePool() = default;
	TilePool(const TilePool&) = delete;
	TilePool& operator=(const TilePool&) = delete;
	~TilePool();

	Tile* GetTile();

	void ReturnTile(Tile* b);

private:
	std::stack<Tile*> recycledTile;
};
