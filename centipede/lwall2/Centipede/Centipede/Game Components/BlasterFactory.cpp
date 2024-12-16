#include "TEAL\CommonElements.h"
#include "BlasterFactory.h"
#include "BulletFactory.h"
#include "Blaster.h"
#include "BlasterPool.h"
#include "MovementStrategy.h"

BlasterPool* BlasterFactory::myBlasterPool = nullptr;
BulletFactory* BlasterFactory::myBulletFactory = nullptr;

MovementStrategy* BlasterFactory::myStrat = nullptr;

BlasterFactory::BlasterFactory(BulletFactory* b) {
	myBlasterPool = new BlasterPool();
	myStrat = new MovementStrategy();
	myStrat->Initialize();
	myBulletFactory = b;
}

BlasterFactory::~BlasterFactory() {
	myStrat->Terminate();
	delete myStrat;
	delete myBlasterPool;
}

void BlasterFactory::SpawnBlaster() {
	Blaster* tempBlaster = myBlasterPool->GetBlaster();
	tempBlaster->SetExternalManagement(RecycleBlaster);

	tempBlaster->Initialize(myBulletFactory, myStrat);
}


void BlasterFactory::RecycleBlaster(GameObject* b) {
	myBlasterPool->ReturnBlaster(static_cast<Blaster*>(b));
}


