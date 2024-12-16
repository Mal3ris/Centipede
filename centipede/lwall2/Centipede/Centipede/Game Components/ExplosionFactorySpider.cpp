#include "TEAL\CommonElements.h"
#include "ExplosionFactorySpider.h"
#include "ExplosionSpider.h"
#include "ExplosionPoolSpider.h"


ExplosionPoolSpider* ExplosionFactorySpider::myExplosionPool = nullptr;

ExplosionFactorySpider::ExplosionFactorySpider()
{
	myExplosionPool = new ExplosionPoolSpider();
}

ExplosionFactorySpider::~ExplosionFactorySpider() {
	delete myExplosionPool;
}

void ExplosionFactorySpider::CreateExplosion(sf::Vector2f location, int val) {
	ExplosionSpider* tempExplosion = myExplosionPool->GetExplosion();
	tempExplosion->SetExternalManagement(RecycleExplosion);

	tempExplosion->Initialize(location, val);
}


void ExplosionFactorySpider::RecycleExplosion(GameObject* b) {
	myExplosionPool->ReturnExplosion(static_cast<ExplosionSpider*>(b));
}



