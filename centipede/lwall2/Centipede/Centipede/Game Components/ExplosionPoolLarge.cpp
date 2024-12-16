#include "ExplosionPoolLarge.h"
#include "TEAL\CommonElements.h"
#include "ExplosionLarge.h"

ExplosionLarge* ExplosionPoolLarge::GetExplosion() {
	ExplosionLarge* tempExplosion;

	if (recycledExplosion.empty()) {
		//ConsoleMsg::WriteLine("Fresh Explosion");
		tempExplosion = new ExplosionLarge();
	}
	else {
		//ConsoleMsg::WriteLine("Recycled Explosion");
		tempExplosion = recycledExplosion.top();
		recycledExplosion.pop();

		tempExplosion->RegisterToCurrentScene();
	}

	return tempExplosion;
}

void ExplosionPoolLarge::ReturnExplosion(ExplosionLarge* b) {
	recycledExplosion.push(static_cast<ExplosionLarge*>(b));
}

ExplosionPoolLarge::~ExplosionPoolLarge() {
	while (!recycledExplosion.empty()) {
		delete recycledExplosion.top();
		recycledExplosion.pop();
	}
}