#pragma once

#include "TEAL\CommonElements.h"
#include "MoveStateCentipede.h"

class Centipede;

class MoveLeftPoisonCentipede : public MoveStateCentipede
{
public:
	MoveLeftPoisonCentipede();
	MoveLeftPoisonCentipede(const MoveLeftPoisonCentipede&) = default;
	MoveLeftPoisonCentipede& operator=(const MoveLeftPoisonCentipede&) = default;
	~MoveLeftPoisonCentipede() = default;

	virtual const sf::Vector2f GetScale(int i) const override;
	virtual const MoveStateCentipede* GetNextState(Centipede* centi,
		MushroomSpawner* mushGrid) const override;
	virtual const void createMushroom(sf::Vector2f location,
		MushroomSpawner* mushGrid) const override;
private:

};