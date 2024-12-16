#include "TEAL\CommonElements.h"
#include "FleaFactory.h"
#include "Flea.h"
#include "FleaPool.h"
#include "FleaSpawner.h"

FleaPool* FleaFactory::myFleaPool = nullptr;
MushroomSpawner* FleaFactory::myMushroomGrid = nullptr;
FleaSpawner* FleaFactory::myFleaSpawner = nullptr;

FleaFactory::FleaFactory(MushroomSpawner* mushroomGrid, FleaSpawner* fleaSpawner)
{
	myFleaSpawner = fleaSpawner;
	myMushroomGrid = mushroomGrid;
	myFleaPool = new FleaPool();
}

FleaFactory::~FleaFactory() {
	delete myFleaPool;
}

void FleaFactory::CreateFlea(sf::Vector2f location, float speed, int frequency) {
	Flea* tempFlea = myFleaPool->GetFlea();
	tempFlea->SetExternalManagement(RecycleFlea);

	tempFlea->Initialize(location, myMushroomGrid, myFleaSpawner, this, speed, frequency);
	fleaList.push_back(tempFlea);
}


void FleaFactory::RecycleFlea(GameObject* b) {
	myFleaPool->ReturnFlea(static_cast<Flea*>(b));
}

void FleaFactory::recallAll() {
	while (fleaList.empty() == false) {
		fleaList.front()->MarkForDestroy();
		fleaList.pop_front();
	}
}

void FleaFactory::removeSpecific(Flea* b) {

	fleaList.erase(std::find(fleaList.begin(), fleaList.end(), b));
}

