#pragma once

#include <stack>

class ExplosionSmall;

class ExplosionPoolSmall
{
public:
	ExplosionPoolSmall() = default;
	ExplosionPoolSmall(const ExplosionPoolSmall&) = delete;
	ExplosionPoolSmall& operator=(const ExplosionPoolSmall&) = delete;
	~ExplosionPoolSmall();

	ExplosionSmall* GetExplosion();

	void ReturnExplosion(ExplosionSmall* b);

private:
	std::stack<ExplosionSmall*> recycledExplosion;
};