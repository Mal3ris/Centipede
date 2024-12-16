#pragma once

//Pool For Scorpions

#include <stack>

class Scorpion;

class ScorpionPool
{
public:
	ScorpionPool() = default;
	ScorpionPool(const ScorpionPool&) = delete;
	ScorpionPool& operator=(const ScorpionPool&) = delete;
	~ScorpionPool();

	Scorpion* GetScorpion();

	void ReturnScorpion(Scorpion* b);

private:
	std::stack<Scorpion*> recycledScorpion;
};
