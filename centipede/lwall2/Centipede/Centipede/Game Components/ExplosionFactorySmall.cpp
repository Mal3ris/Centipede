#include "TEAL\CommonElements.h"
#include "ExplosionFactorySmall.h"
#include "ExplosionSmall.h"
#include "ExplosionPoolSmall.h"


ExplosionPoolSmall* ExplosionFactorySmall::myExplosionPool = nullptr;

ExplosionFactorySmall::ExplosionFactorySmall()
{
	myExplosionPool = new ExplosionPoolSmall();
}

ExplosionFactorySmall::~ExplosionFactorySmall() {
	delete myExplosionPool;
}

void ExplosionFactorySmall::CreateExplosion(sf::Vector2f location) {
	ExplosionSmall* tempExplosion = myExplosionPool->GetExplosion();
	tempExplosion->SetExternalManagement(RecycleExplosion);

	tempExplosion->Initialize(location);
}


void ExplosionFactorySmall::RecycleExplosion(GameObject* b) {
	myExplosionPool->ReturnExplosion(static_cast<ExplosionSmall*>(b));
}



