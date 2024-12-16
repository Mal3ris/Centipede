#pragma once

#include "TEAL\CommonElements.h"
#include "GridConstants.h"
#include <list>

// Forward declarations
class CentipedePool;
class GameObject;
class MushroomSpawner;
class Centipede;
class MoveStateCentipede;
class CommandSound;

class CentipedeFactory
{
public:
	CentipedeFactory();
	CentipedeFactory(const CentipedeFactory&) = delete;
	CentipedeFactory& operator=(const CentipedeFactory&) = delete;
	~CentipedeFactory();

	Centipede* CreateCentipede(sf::Vector2f location, MushroomSpawner* pMG, bool dir);
	Centipede* ReplaceCentipede(sf::Vector2f location, MushroomSpawner* pMG, int pCount, const MoveStateCentipede* pState);

	static void RecycleCentipede(GameObject* b);

	void recallAll();

	void removeSpecific(Centipede* b);
	
	void Pause();
	void Play();

private:

	static CentipedePool* myCentipedePool;

	sf::Vector2f turnLocations[GridConstants::HALFCELLSIZE];

	static std::list<Centipede*> headList;

	static CommandSound* pSound;

};
