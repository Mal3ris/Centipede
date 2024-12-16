#include "ExplosionPoolSmall.h"
#include "TEAL\CommonElements.h"
#include "ExplosionSmall.h"

ExplosionSmall* ExplosionPoolSmall::GetExplosion() {
	ExplosionSmall* tempExplosion;

	if (recycledExplosion.empty()) {
		//ConsoleMsg::WriteLine("Fresh Explosion");
		tempExplosion = new ExplosionSmall();
	}
	else {
		//ConsoleMsg::WriteLine("Recycled explosion");
		tempExplosion = recycledExplosion.top();
		recycledExplosion.pop();

		tempExplosion->RegisterToCurrentScene();
	}

	return tempExplosion;
}

void ExplosionPoolSmall::ReturnExplosion(ExplosionSmall* b) {
	recycledExplosion.push(static_cast<ExplosionSmall*>(b));
}

ExplosionPoolSmall::~ExplosionPoolSmall() {
	while (!recycledExplosion.empty()) {
		delete recycledExplosion.top();
		recycledExplosion.pop();
	}
}