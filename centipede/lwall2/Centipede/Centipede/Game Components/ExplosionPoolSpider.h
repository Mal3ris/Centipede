#pragma once

#include <stack>

class ExplosionSpider;

class ExplosionPoolSpider
{
public:
	ExplosionPoolSpider() = default;
	ExplosionPoolSpider(const ExplosionPoolSpider&) = delete;
	ExplosionPoolSpider& operator=(const ExplosionPoolSpider&) = delete;
	~ExplosionPoolSpider();

	ExplosionSpider* GetExplosion();

	void ReturnExplosion(ExplosionSpider* b);

private:
	std::stack<ExplosionSpider*> recycledExplosion;
};
