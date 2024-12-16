#pragma once

#include <stack>

class Blaster;

class BlasterPool
{
public:
	BlasterPool() = default;
	BlasterPool(const BlasterPool&) = delete;
	BlasterPool& operator=(const BlasterPool&) = delete;
	~BlasterPool();

	Blaster* GetBlaster();

	void ReturnBlaster(Blaster* b);

private:
	std::stack<Blaster*> recycledBlaster;
};
