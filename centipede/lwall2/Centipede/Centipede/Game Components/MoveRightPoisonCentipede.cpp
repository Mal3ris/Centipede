#include "MoveRightPoisonCentipede.h"
#include "MushroomSpawner.h"
#include "MoveFSM.h"
#include "MoveRightAndDownCentipede.h"
#include "MoveRightAndUpCentipede.h"
#include "MoveLeftPoisonCentipede.h"
#include "MoveUpToLeftCentipede.h"
#include "GridConstants.h"
#include "Centipede.h"


MoveRightPoisonCentipede::MoveRightPoisonCentipede() {
	for (int i = 0; i < GridConstants::HALFCELLSIZE; i++) {
		myMoveOffsets[i].x = -1.0f * round(GridConstants::HALFCELLSIZE / 2 * cosf(i * 3.14f / GridConstants::HALFCELLSIZE));
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

const sf::Vector2f MoveRightPoisonCentipede::GetScale(int i) const {
	if (i < 4) {
		return sf::Vector2f(2, 2);
	}
	else {
		return sf::Vector2f(-2, 2);
	}
}

const MoveStateCentipede* MoveRightPoisonCentipede::GetNextState(Centipede* centi,
	MushroomSpawner* mushGrid) const {

	const MoveStateCentipede* pNextState;

	if (centi->getPos().y == GridConstants::BOTTOMZONE * GridConstants::CELLSIZE - GridConstants::HALFCELLSIZE) {
		pNextState = &MoveFSM::StateMoveRightUp;
	}
	else {
		pNextState = &MoveFSM::StateMovePoisonLeft;
	}

	return pNextState;
}

const void MoveRightPoisonCentipede::createMushroom(sf::Vector2f location,
	MushroomSpawner* mushGrid) const {
	mushGrid->spawnMushroomAt(sf::Vector2f((location.x -
		((int)location.x % GridConstants::CELLSIZE)) + GridConstants::HALFCELLSIZE,
		(location.y - ((int)location.y % GridConstants::CELLSIZE))
		+ GridConstants::HALFCELLSIZE));
}