#include "MoveLeftAndUpCentipede.h"
#include "MushroomSpawner.h"
#include "MoveFSM.h"
#include "MoveDownToRightCentipede.h"
#include "MoveUpToRightCentipede.h"
#include "GridConstants.h"
#include "Centipede.h"

const MoveDownToRightCentipede MoveFSM::StateMoveDownRight;
const MoveLeftAndUpCentipede MoveFSM::StateMoveLeftUp;


MoveLeftAndUpCentipede::MoveLeftAndUpCentipede() {
	for (int i = 0; i < GridConstants::HALFCELLSIZE; i++) {
		myMoveOffsets[i] = sf::Vector2f(-2, 0);
	}

	//Doing this by hand cause easier to logic
	mySpritesOffset[0] = 0;
	mySpritesOffset[1] = 1;
	mySpritesOffset[2] = 2;
	mySpritesOffset[3] = 3;
	mySpritesOffset[4] = 4;
	mySpritesOffset[5] = 5;
	mySpritesOffset[6] = 6;
	mySpritesOffset[7] = 7;
}

const sf::Vector2f MoveLeftAndUpCentipede::GetScale(int i) const {
	return sf::Vector2f(2, 2);
}

const MoveStateCentipede* MoveLeftAndUpCentipede::GetNextState(Centipede* centi,
	MushroomSpawner* mushGrid) const {

	const MoveStateCentipede* pNextState;


	MushroomSpawner::MushroomState obst = mushGrid->mushroomAt(sf::Vector2f(centi->getPos().x - GridConstants::CELLSIZE, centi->getPos().y));

	if (obst == MushroomSpawner::MushroomState::EMPTY) {
		pNextState = &MoveFSM::StateMoveLeftUp;
	}
	else if (obst == MushroomSpawner::MushroomState::BLOCKED) {
		if (centi->getPos().y == GridConstants::PLAYZONE * GridConstants::CELLSIZE + GridConstants::HALFCELLSIZE) {
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

const void MoveLeftAndUpCentipede::createMushroom(sf::Vector2f location,
	MushroomSpawner* mushGrid) const {
	mushGrid->spawnMushroomAt(sf::Vector2f((location.x -
		((int)location.x % GridConstants::CELLSIZE)) - GridConstants::HALFCELLSIZE,
		(location.y - ((int)location.y % GridConstants::CELLSIZE))
		+ GridConstants::HALFCELLSIZE));
}