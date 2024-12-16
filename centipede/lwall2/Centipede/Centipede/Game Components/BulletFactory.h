#pragma once

#include "TEAL\CommonElements.h"
#include <list>

// Forward declarations
class BulletPool;
class GameObject;
class Bullet;

class BulletFactory
{
public:
	BulletFactory();
	BulletFactory(const BulletFactory&) = delete;
	BulletFactory& operator=(const BulletFactory&) = delete;
	~BulletFactory();

	void setActiveBullet(bool tf);

	void shootBullet(sf::Vector2f location);

	static void RecycleBullet(GameObject* b);

	void recallAll();

	void removeSpecific(Bullet* b);

private:
	
	static BulletPool* myBulletPool;

	bool activeBullet = false;

	std::list<Bullet*> bulletList;

};