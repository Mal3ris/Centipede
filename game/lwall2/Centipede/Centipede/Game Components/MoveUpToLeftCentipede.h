#pragma once

#include "TEAL\CommonElements.h"
#include "MoveStateCentipede.h"

class Centipede;

class MoveUpToLeftCentipede : public MoveStateCentipede
{
public:
	MoveUpToLeftCentipede();
	MoveUpToLeftCentipede(const MoveUpToLeftCentipede&) = default;
	MoveUpToLeftCentipede& operator=(const MoveUpToLeftCentipede&) = default;
	~MoveUpToLeftCentipede() = default;

	virtual const sf::Vector2f GetScale(int i) const override;
	virtual const MoveStateCentipede* GetNextState(Centipede* centi,
		MushroomSpawner* mushGrid) const override;
	virtual const void createMushroom(sf::Vector2f location,
		MushroomSpawner* mushGrid) const override;
private:

};
