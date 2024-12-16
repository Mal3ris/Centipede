#pragma once

//Create a Pool For Spiders

#include <stack>

class Spider;

class SpiderPool
{
public:
	SpiderPool() = default;
	SpiderPool(const SpiderPool&) = delete;
	SpiderPool& operator=(const SpiderPool&) = delete;
	~SpiderPool();

	Spider* GetSpider();

	void ReturnSpider(Spider* b);

private:
	std::stack<Spider*> recycledSpider;
};