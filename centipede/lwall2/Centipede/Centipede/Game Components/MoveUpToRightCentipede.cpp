#include "MoveUpToRightCentipede.h"
#include "MoveDownToLeftCentipede.h"
#include "MoveRightAndUpCentipede.h"
#include "MoveUpToLeftCentipede.h"
#include "MushroomSpawner.h"
#include "MoveFSM.h"
#include "MoveRightAndDownCentipede.h"
#include "GridConstants.h"
#include "Centipede.h"

const MoveUpToLeftCentipede MoveFSM::StateMoveUpLeft;


MoveUpToRightCentipede::MoveUpToRightCentipede() {
	for (int i = 0; i < GridConstants::HALFCELLSIZE; i++) {
		myMoveOffsets[i].x = -1.0f * round(GridConstants::HALFCELLSIZE / 2 * cosf(i * 3.14f / GridConstants::HALFCELLSIZE));
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

const sf::Vector2f MoveUpToRightCentipede::GetScale(int i) const{
	if (i < 4) {
		return sf::Vector2f(2, -2);
	}
	else {
		return sf::Vector2f(-2, -2);
	}
}

const MoveStateCentipede* MoveUpToRightCentipede::GetNextState(Centipede* centi,
	MushroomSpawner* mushGrid) const {

	const MoveStateCentipede* pNextState;


	MushroomSpawner::MushroomState obst = mushGrid->mushroomAt(sf::Vector2f(centi->getPos().x + GridConstants::CELLSIZE, centi->getPos().y));
	
	if (obst == MushroomSpawner::MushroomState::EMPTY) {
		pNextState = &MoveFSM::StateMoveRightUp;
	}
	else if (obst == MushroomSpawner::MushroomState::BLOCKED) {
		if (centi->getPos().y == GridConstants::PLAYZONE * GridConstants::CELLSIZE - GridConstants::HALFCELLSIZE) {
			pNextState = &MoveFSM::StateMoveDownLeft;
		}
		else {
			pNextState = &MoveFSM::StateMoveUpLeft;
		}
	}
	else {
		ConsoleMsg::WriteLine("poison");
		pNextState = nullptr;
	}

	return pNextState;
}

const void MoveUpToRightCentipede::createMushroom(sf::Vector2f location,
	MushroomSpawner* mushGrid) const {
	mushGrid->spawnMushroomAt(sf::Vector2f((location.x -
		((int)location.x % GridConstants::CELLSIZE)) + GridConstants::HALFCELLSIZE,
		(location.y - ((int)location.y % GridConstants::CELLSIZE))
		+ GridConstants::HALFCELLSIZE));
}