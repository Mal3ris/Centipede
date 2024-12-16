#include "MoveUpToLeftCentipede.h"
#include "MoveDownToRightCentipede.h"
#include "MoveUpToRightCentipede.h"
#include "MoveLeftAndUpCentipede.h"
#include "MushroomSpawner.h"
#include "MoveFSM.h"
#include "MoveLeftAndDownCentipede.h"
#include "GridConstants.h"
#include "Centipede.h"


const MoveUpToRightCentipede MoveFSM::StateMoveUpRight;


MoveUpToLeftCentipede::MoveUpToLeftCentipede() {
	for (int i = 0; i < GridConstants::HALFCELLSIZE; i++) {
		myMoveOffsets[i].x = round(GridConstants::HALFCELLSIZE / 2 * cosf(i * 3.14f / GridConstants::HALFCELLSIZE));
		myMoveOffsets[i].y = -1.0f * floor(GridConstants::HALFCELLSIZE / 2 * sinf(i * 3.14f / GridConstants::HALFCELLSIZE));
	}
	float temp = GridConstants::CELLSIZE;
	for (int i = 0; i < GridConstants::HALFCELLSIZE; i++) {
		temp += myMoveOffsets[i].y;
	}
	myMoveOffsets[GridConstants::HALFCELLSIZE - 1].y -= temp;
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

const sf::Vector2f MoveUpToLeftCentipede::GetScale(int i) const {
	if (i < 4) {
		return sf::Vector2f(-2, -2);
	}
	else {
		return sf::Vector2f(2, -2);
	}
}

const MoveStateCentipede* MoveUpToLeftCentipede::GetNextState(Centipede* centi,
	MushroomSpawner* mushGrid) const {

	const MoveStateCentipede* pNextState;


	MushroomSpawner::MushroomState obst = mushGrid->mushroomAt(sf::Vector2f(centi->getPos().x - GridConstants::CELLSIZE, centi->getPos().y));

	if (obst == MushroomSpawner::MushroomState::EMPTY) {
		pNextState = &MoveFSM::StateMoveLeftUp;
	}
	else if (obst == MushroomSpawner::MushroomState::BLOCKED) {
		if (centi->getPos().y == GridConstants::PLAYZONE * GridConstants::CELLSIZE - GridConstants::HALFCELLSIZE) {
			pNextState = &MoveFSM::StateMoveDownRight;
		}
		else {
			pNextState = &MoveFSM::StateMoveUpRight;
		}
	}
	else {
		ConsoleMsg::WriteLine("poison");
		pNextState = nullptr;
	}

	return pNextState;
}

const void MoveUpToLeftCentipede::createMushroom(sf::Vector2f location,
	MushroomSpawner* mushGrid) const {
	mushGrid->spawnMushroomAt(sf::Vector2f((location.x -
		((int)location.x % GridConstants::CELLSIZE)) - GridConstants::HALFCELLSIZE,
		(location.y - ((int)location.y % GridConstants::CELLSIZE))
		+ GridConstants::HALFCELLSIZE));
}