#pragma once

#include "TEAL\CommonElements.h"
#include "MoveStateCentipede.h"

class Centipede;

class MoveRightAndDownCentipede : public MoveStateCentipede
{
public:
	MoveRightAndDownCentipede();
	MoveRightAndDownCentipede(const MoveRightAndDownCentipede&) = default;
	MoveRightAndDownCentipede& operator=(const MoveRightAndDownCentipede&) = default;
	~MoveRightAndDownCentipede() = default;

	virtual const sf::Vector2f GetScale(int i) const override;
	virtual const MoveStateCentipede* GetNextState(Centipede* centi,
		MushroomSpawner* mushGrid) const override;
	virtual const void createMushroom(sf::Vector2f location,
		MushroomSpawner* mushGrid) const override;
private:

};