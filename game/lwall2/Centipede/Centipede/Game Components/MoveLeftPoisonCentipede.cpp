#include "MoveLeftPoisonCentipede.h"
#include "MoveDownToRightCentipede.h"
#include "MoveLeftAndUpCentipede.h"
#include "MushroomSpawner.h"
#include "MoveFSM.h"
#include "MoveLeftAndDownCentipede.h"
#include "MoveRightPoisonCentipede.h"
#include "GridConstants.h"
#include "Centipede.h"

const MoveRightPoisonCentipede MoveFSM::StateMovePoisonRight;


MoveLeftPoisonCentipede::MoveLeftPoisonCentipede() {
	for (int i = 0; i < GridConstants::HALFCELLSIZE; i++) {
		myMoveOffsets[i].x = round(GridConstants::HALFCELLSIZE / 2 * cosf(i * 3.14f / GridConstants::HALFCELLSIZE));
		myMoveOffsets[i].y = floor(GridConstants::HALFCELLSIZE / 2 * sinf(i * 3.14f / GridConstants::HALFCELLSIZE));
	}
	float temp = GridConstants::CELLSIZE;
	for (int i = 0; i < GridConstants::HALFCELLSIZE; i++) {
		temp -= myMoveOffsets[i].y;
	}
	myMoveOffsets[GridConstants::HALFCELLSIZE - 1].y += temp;
	myMoveOffsets[0].x = 0;

	//Doing this by hand cause easier to logic
	mySpritesOffset[0] = 8;
	mySpritesOffset[1] = 9;
	mySpritesOffset[2] = 10;
	mySpritesOffset[3] = 11;
	mySpritesOffset[4] = 8;
	mySpritesOffset[5] = 9;
	mySpritesOffset[6] = 10;
	mySpritesOffset[7] = 11;
}

const sf::Vector2f MoveLeftPoisonCentipede::GetScale(int i) const {
	if (i < 4) {
		return sf::Vector2f(-2, 2);
	}
	else {
		return sf::Vector2f(2, 2);
	}
}

const MoveStateCentipede* MoveLeftPoisonCentipede::GetNextState(Centipede* centi,
	MushroomSpawner* mushGrid) const {

	const MoveStateCentipede* pNextState;

	if (centi->getPos().y == GridConstants::BOTTOMZONE * GridConstants::CELLSIZE - GridConstants::HALFCELLSIZE) {
		pNextState = &MoveFSM::StateMoveLeftUp;
	}
	else {
		pNextState = &MoveFSM::StateMovePoisonRight;
	}

	return pNextState;
}

const void MoveLeftPoisonCentipede::createMushroom(sf::Vector2f location,
	MushroomSpawner* mushGrid) const {
	mushGrid->spawnMushroomAt(sf::Vector2f((location.x -
		((int)location.x % GridConstants::CELLSIZE)) - GridConstants::HALFCELLSIZE,
		(location.y - ((int)location.y % GridConstants::CELLSIZE))
		+ GridConstants::HALFCELLSIZE));
}