#pragma once

#include <stack>

class Bullet;

class BulletPool
{
public:
	BulletPool() = default;
	BulletPool(const BulletPool&) = delete;
	BulletPool& operator=(const BulletPool&) = delete;
	~BulletPool();

	Bullet* GetBullet();

	void ReturnBullet(Bullet* b);

private:
	static std::stack<Bullet*> recycledBullet;
};