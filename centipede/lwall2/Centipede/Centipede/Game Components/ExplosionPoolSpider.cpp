#include "ExplosionPoolSpider.h"
#include "TEAL\CommonElements.h"
#include "ExplosionSpider.h"

ExplosionSpider* ExplosionPoolSpider::GetExplosion() {
	ExplosionSpider* tempExplosion;

	if (recycledExplosion.empty()) {
		//ConsoleMsg::WriteLine("Fresh explosion");
		tempExplosion = new ExplosionSpider();
	}
	else {
		//ConsoleMsg::WriteLine("Recycled explosion");
		tempExplosion = recycledExplosion.top();
		recycledExplosion.pop();

		tempExplosion->RegisterToCurrentScene();
	}

	return tempExplosion;
}

void ExplosionPoolSpider::ReturnExplosion(ExplosionSpider* b) {
	recycledExplosion.push(static_cast<ExplosionSpider*>(b));
}

ExplosionPoolSpider::~ExplosionPoolSpider() {
	while (!recycledExplosion.empty()) {
		delete recycledExplosion.top();
		recycledExplosion.pop();
	}
}