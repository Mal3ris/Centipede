#pragma once

#include <stack>

class Centipede;

class CentipedePool
{
public:
	CentipedePool() = default;
	CentipedePool(const CentipedePool&) = delete;
	CentipedePool& operator=(const CentipedePool&) = delete;
	~CentipedePool();

	Centipede* GetCentipede();

	void ReturnCentipede(Centipede* b);

private:
	std::stack<Centipede*> recycledCentipede;
};