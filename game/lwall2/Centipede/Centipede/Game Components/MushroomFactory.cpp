#include "TEAL\CommonElements.h"
#include "MushroomFactory.h"
#include "Mushroom.h"
#include "MushroomPool.h"
#include "MushroomSpawner.h"

MushroomPool* MushroomFactory::myMushroomPool = nullptr;
MushroomSpawner* MushroomFactory::myMushroomGrid = nullptr;

MushroomFactory::MushroomFactory(MushroomSpawner* pMG) {
	myMushroomGrid = pMG;
	myMushroomPool = new MushroomPool();
	
}

MushroomFactory::~MushroomFactory() {
	delete(myMushroomPool);
}

void MushroomFactory::Terminate() {
	delete(myMushroomPool);
}

void MushroomFactory::CreateMushroom(sf::Vector2f location) {
	Mushroom* tempMushroom = myMushroomPool->GetMushroom();
	tempMushroom->SetExternalManagement(RecycleMushroom);

	tempMushroom->Initialize(location, myMushroomGrid);

	myMushroomGrid->setCell((int)(((location.x) - GridConstants::HALFCELLSIZE) / GridConstants::CELLSIZE), (int)(((location.y) - GridConstants::HALFCELLSIZE) / GridConstants::CELLSIZE), tempMushroom);
}

void MushroomFactory::DestroyMushroom(sf::Vector2f location) {
	myMushroomGrid->getCell((int)(((location.x) - GridConstants::HALFCELLSIZE) / GridConstants::CELLSIZE), (int)(((location.y) - GridConstants::HALFCELLSIZE) / GridConstants::CELLSIZE))->MarkForDestroy();
	myMushroomGrid->setCell((int)(((location.x) - GridConstants::HALFCELLSIZE) / GridConstants::CELLSIZE), (int)(((location.y) - GridConstants::HALFCELLSIZE) / GridConstants::CELLSIZE), nullptr);
}

void MushroomFactory::clearPlayerSpawn() {
	//Magic Numbers very unfortunate
	myMushroomGrid->destroyMushroomAt(sf::Vector2f(248, 408));
	myMushroomGrid->destroyMushroomAt(sf::Vector2f(232, 408));
	myMushroomGrid->destroyMushroomAt(sf::Vector2f(248, 392));
	myMushroomGrid->destroyMushroomAt(sf::Vector2f(232, 392));
	myMushroomGrid->destroyMushroomAt(sf::Vector2f(248, 424));
	myMushroomGrid->destroyMushroomAt(sf::Vector2f(232, 424));
}

void MushroomFactory::RecycleMushroom(GameObject* b) {
	myMushroomPool->ReturnMushroom(static_cast<Mushroom*>(b));
}


