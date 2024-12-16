#pragma once

#include <stack>

class ExplosionLarge;

class ExplosionPoolLarge
{
public:
	ExplosionPoolLarge() = default;
	ExplosionPoolLarge(const ExplosionPoolLarge&) = delete;
	ExplosionPoolLarge& operator=(const ExplosionPoolLarge&) = delete;
	~ExplosionPoolLarge();

	ExplosionLarge* GetExplosion();

	void ReturnExplosion(ExplosionLarge* b);

private:
	std::stack<ExplosionLarge*> recycledExplosion;
};