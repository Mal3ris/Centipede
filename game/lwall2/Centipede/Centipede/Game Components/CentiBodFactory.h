#pragma once

#include "TEAL\CommonElements.h"
#include "GridConstants.h"
#include <list>

// Forward declarations
class CentiBodPool;
class GameObject;
class MushroomSpawner;
class CentiBod;
class CentipedeFactory;

class CentiBodFactory
{
public:
	CentiBodFactory();
	CentiBodFactory(const CentiBodFactory&) = delete;
	CentiBodFactory& operator=(const CentiBodFactory&) = delete;
	~CentiBodFactory();

	CentiBod* CreateCentiBod(sf::Vector2f location, MushroomSpawner* pMG, CentipedeFactory* pFact, bool moveRight);

	static void RecycleCentiBod(GameObject* b);

	void recallAll();

	void removeSpecific(CentiBod* b);

private:
	
	static CentiBodPool* myCentiBodPool;

	sf::Vector2f turnLocations[GridConstants::HALFCELLSIZE];

	std::list<CentiBod*> bodyList;

};
