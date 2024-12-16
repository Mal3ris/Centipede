#include "MoveRightAndDownCentipede.h"
#include "MushroomSpawner.h"
#include "MoveFSM.h"
#include "MoveDownToLeftCentipede.h"
#include "MoveUpToLeftCentipede.h"
#include "MoveLeftPoisonCentipede.h"
#include "GridConstants.h"
#include "Centipede.h"

const MoveLeftPoisonCentipede MoveFSM::StateMovePoisonLeft;


MoveRightAndDownCentipede::MoveRightAndDownCentipede() {
	for (int i = 0; i < GridConstants::HALFCELLSIZE; i++) {
		myMoveOffsets[i] = sf::Vector2f(2, 0);
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

const sf::Vector2f MoveRightAndDownCentipede::GetScale(int i) const {
	return sf::Vector2f(-2, 2);
}

const MoveStateCentipede* MoveRightAndDownCentipede::GetNextState(Centipede* centi,
	MushroomSpawner* mushGrid) const {

	const MoveStateCentipede* pNextState;


	MushroomSpawner::MushroomState obst = mushGrid->mushroomAt(sf::Vector2f(centi->getPos().x + GridConstants::CELLSIZE, centi->getPos().y));

	if (obst == MushroomSpawner::MushroomState::EMPTY) {
		pNextState = &MoveFSM::StateMoveRightDown;
	}
	else if (obst == MushroomSpawner::MushroomState::POISON) {
		pNextState = &MoveFSM::StateMovePoisonLeft;
	}
	else if (obst == MushroomSpawner::MushroomState::BLOCKED) {
		if (centi->getPos().y == GridConstants::BOTTOMZONE * GridConstants::CELLSIZE - GridConstants::HALFCELLSIZE) {
			pNextState = &MoveFSM::StateMoveUpLeft;
		}
		else {
			pNextState = &MoveFSM::StateMoveDownLeft;
		}
	}
	else {
		ConsoleMsg::WriteLine("poison");
		pNextState = nullptr;
	}

	return pNextState;
}

const void MoveRightAndDownCentipede::createMushroom(sf::Vector2f location,
	MushroomSpawner* mushGrid) const {
	mushGrid->spawnMushroomAt(sf::Vector2f((location.x -
		((int)location.x % GridConstants::CELLSIZE)) + GridConstants::CELLSIZE + GridConstants::HALFCELLSIZE,
		(location.y - ((int)location.y % GridConstants::CELLSIZE))
		+ GridConstants::HALFCELLSIZE));
}
