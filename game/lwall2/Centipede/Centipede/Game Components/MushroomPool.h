#pragma once

#include <stack>

class Mushroom;

class MushroomPool
{
public:
	MushroomPool() = default;
	MushroomPool(const MushroomPool&) = delete;
	MushroomPool& operator=(const MushroomPool&) = delete;
	~MushroomPool();

	Mushroom* GetMushroom();

	void ReturnMushroom(Mushroom* b);

private:
	std::stack<Mushroom*> recycledMushroom;
};
