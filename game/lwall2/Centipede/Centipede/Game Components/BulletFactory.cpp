#include "TEAL\CommonElements.h"
#include "BulletFactory.h"
#include "Bullet.h"
#include "BulletPool.h"

BulletPool* BulletFactory::myBulletPool = nullptr;

BulletFactory::BulletFactory() {
	myBulletPool = new BulletPool();
}

BulletFactory::~BulletFactory() {
	delete myBulletPool;
}

void BulletFactory::shootBullet(sf::Vector2f location) {
	if (activeBullet == false) {
		activeBullet = true;

		Bullet* tempBullet = myBulletPool->GetBullet();
		tempBullet->SetExternalManagement(RecycleBullet);

		tempBullet->Initialize(location, this);
		bulletList.push_back(tempBullet);
	}
}

void BulletFactory::setActiveBullet(bool tf) {
	activeBullet = tf;
}

void BulletFactory::RecycleBullet(GameObject* b) {
	myBulletPool->ReturnBullet(static_cast<Bullet*>(b));
}

void BulletFactory::recallAll() {
	while (bulletList.empty() == false) {
		bulletList.front()->MarkForDestroy();
		bulletList.pop_front();
	}
}

void BulletFactory::removeSpecific(Bullet* b) {
	bulletList.erase(std::find(bulletList.begin(), bulletList.end(), b));
}

