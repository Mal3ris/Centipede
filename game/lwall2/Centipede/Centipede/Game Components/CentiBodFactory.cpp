#include "TEAL\CommonElements.h"
#include "CentiBodFactory.h"
#include "CentiBod.h"
#include <cmath>
#include "CentiBodPool.h"
#include "CentipedeFactory.h"

CentiBodPool* CentiBodFactory::myCentiBodPool = nullptr;


CentiBodFactory::CentiBodFactory() {
	myCentiBodPool = new CentiBodPool();
}

CentiBodFactory::~CentiBodFactory() {
	delete myCentiBodPool;
}

CentiBod* CentiBodFactory::CreateCentiBod(sf::Vector2f location, MushroomSpawner* pMG,
	CentipedeFactory* pFact, bool dir) {
	CentiBod* tempCentiBod = myCentiBodPool->GetCentiBod();
	tempCentiBod->SetExternalManagement(RecycleCentiBod);

	tempCentiBod->Initialize(location, pMG, pFact, dir, this);

	bodyList.push_back(tempCentiBod);

	return tempCentiBod;
}

void CentiBodFactory::RecycleCentiBod(GameObject* b) {
	myCentiBodPool->ReturnCentiBod(static_cast<CentiBod*>(b));
}

void CentiBodFactory::recallAll() {
	while (bodyList.empty() == false) {
		bodyList.front()->MarkForDestroy();
		bodyList.pop_front();
	}
}

void CentiBodFactory::removeSpecific(CentiBod* b) {

	bodyList.erase(std::find(bodyList.begin(), bodyList.end(), b));
}

