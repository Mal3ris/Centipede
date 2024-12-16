#pragma once

#include "TEAL\CommonElements.h"
#include "GridConstants.h"

class MushroomSpawner;
class Centipede;
class CentiBod;

class MoveStateCentipede
{
public:
	MoveStateCentipede() = default;
	MoveStateCentipede(const MoveStateCentipede&) = default;
	MoveStateCentipede& operator=(const MoveStateCentipede&) = default;
	~MoveStateCentipede() = default;

	const sf::Vector2f GetMoveOffset(int i) const { return myMoveOffsets[i]; }
	const int GetSpriteOffset(int i) const { return mySpritesOffset[i]; }
	virtual const sf::Vector2f GetScale(int i) const = 0;
	virtual const MoveStateCentipede* GetNextState(Centipede* centi,
		MushroomSpawner* mushGrid) const = 0;
	virtual const void createMushroom(sf::Vector2f location,
		MushroomSpawner* mushGrid) const = 0;

protected:
	sf::Vector2f myMoveOffsets[GridConstants::HALFCELLSIZE];

	int mySpritesOffset[GridConstants::HALFCELLSIZE];

};
