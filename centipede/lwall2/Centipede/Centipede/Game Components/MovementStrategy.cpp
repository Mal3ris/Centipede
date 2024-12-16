#include "MovementStrategy.h"
#include "MovementKeys.h"
#include "MovementAi.h"
#include "Blaster.h"

//Gotta Do this otherwise causes stack overflow
void MovementStrategy::Initialize() {
	ai = new MovementAi();
	keys = new MovementKeys();
}

void MovementStrategy::SetStrat(char* strat, Blaster* pBlaster) {
	myBlaster = pBlaster;

	if (strat == "keys") {
		currPat = keys;
	}
	else if (strat == "ai") {
		static_cast<MovementAi*>(ai)->setBlaster(pBlaster);
		currPat = ai;
	}
	else {
		currPat = keys;
	}
}

void MovementStrategy::AffectMove() {

	if (currPat->CheckFire()) {
		myBlaster->Fire();
	}

	if (currPat->CheckUp()) {
		myBlaster->MoveUp();
	}
	else if (currPat->CheckDown()) {
		myBlaster->MoveDown();
	}

	if (currPat->CheckRight()) {
		myBlaster->MoveRight();
	}
	else if (currPat->CheckLeft()) {
		myBlaster->MoveLeft();
	}

	
}

bool MovementStrategy::CheckDown() { return false; }
bool MovementStrategy::CheckUp() { return false; }
bool MovementStrategy::CheckLeft() { return false; }
bool MovementStrategy::CheckRight() { return false; }
bool MovementStrategy::CheckFire() { return false; }


//Gotta Do this otherwise keeps calling base destructor
void MovementStrategy::Terminate() {
	delete ai;
	delete keys;
}


