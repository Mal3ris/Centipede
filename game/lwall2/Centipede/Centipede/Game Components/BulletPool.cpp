#include "BulletPool.h"
#include "TEAL\CommonElements.h"
#include "Bullet.h"

std::stack<Bullet*> BulletPool::recycledBullet;

Bullet* BulletPool::GetBullet() {
	Bullet* tempBullet;

	if (recycledBullet.empty()) {
		tempBullet = new Bullet();
	}
	else {
		tempBullet = recycledBullet.top();
		recycledBullet.pop();

		tempBullet->RegisterToCurrentScene();
	}

	return tempBullet;
}

void BulletPool::ReturnBullet(Bullet* b) {
	//BANDAID FIX CAUSE OBJECT WAS PUSHING TO STACK TWICE
	std::stack<Bullet*> tmp = recycledBullet;
	while (!tmp.empty()) {
		if (tmp.top() == b) {
			return;
		}
		tmp.pop();
	}
	recycledBullet.push(static_cast<Bullet*>(b));
}

BulletPool::~BulletPool() {
	while (recycledBullet.empty() == false) {
		recycledBullet.top()->ClearCommands();
		delete recycledBullet.top();
		recycledBullet.pop();
	}
}