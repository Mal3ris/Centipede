#include "TEAL\CommonElements.h"
#include "ExplosionFactoryLarge.h"
#include "ExplosionLarge.h"
#include "ExplosionPoolLarge.h"


ExplosionPoolLarge* ExplosionFactoryLarge::myExplosionPool = nullptr;

ExplosionFactoryLarge::ExplosionFactoryLarge()
{
	myExplosionPool = new ExplosionPoolLarge();
}

ExplosionFactoryLarge::~ExplosionFactoryLarge() {
	delete myExplosionPool;
}

void ExplosionFactoryLarge::CreateExplosion(sf::Vector2f location) {
	ExplosionLarge* tempExplosion = myExplosionPool->GetExplosion();
	tempExplosion->SetExternalManagement(RecycleExplosion);

	tempExplosion->Initialize(location);
}


void ExplosionFactoryLarge::RecycleExplosion(GameObject* b) {
	myExplosionPool->ReturnExplosion(static_cast<ExplosionLarge*>(b));
}



