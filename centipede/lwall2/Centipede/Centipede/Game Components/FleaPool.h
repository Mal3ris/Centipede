#pragma once

#include <stack>

class Flea;

class FleaPool
{
public:
	FleaPool() = default;
	FleaPool(const FleaPool&) = delete;
	FleaPool& operator=(const FleaPool&) = delete;
	~FleaPool();

	Flea* GetFlea();

	void ReturnFlea(Flea* b);

private:
	std::stack<Flea*> recycledFlea;
};