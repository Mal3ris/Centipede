#pragma once

#include <stack>

class CentiBod;

class CentiBodPool
{
public:
	CentiBodPool() = default;
	CentiBodPool(const CentiBodPool&) = delete;
	CentiBodPool& operator=(const CentiBodPool&) = delete;
	~CentiBodPool();

	CentiBod* GetCentiBod();

	void ReturnCentiBod(CentiBod* b);

private:
	std::stack<CentiBod*> recycledCentiBod;
};