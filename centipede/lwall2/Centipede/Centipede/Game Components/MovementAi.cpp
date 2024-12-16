#include "MovementStrategy.h"
#include "MovementAi.h"
#include "Blaster.h"

void MovementAi::setBlaster(Blaster* blast) {
	myBlaster = blast;
}

bool MovementAi::CheckDown() {
	if (moving == false) {
		return false;
	}
	if (moveUp == false) {
		if (myBlaster->getPos().y >= GridConstants::BOTTOMZONE * GridConstants::CELLSIZE - GridConstants::HALFCELLSIZE) {
			moveUp = true;
		}
		return true;
	}
	else {
		return false;
	}
}

bool MovementAi::CheckUp() {
	if (moving == false) {
		return false;
	}
	if (moveUp == true) {
		if (myBlaster->getPos().y <= GridConstants::PLAYZONE * GridConstants::CELLSIZE + GridConstants::HALFCELLSIZE) {
			moveUp = false;
		}
		return true;
	}
	else {
		return false;
	}
}

bool MovementAi::CheckLeft() {
	if (moving == false) {
		return false;
	}
	if (moveRight == false) {
		if (myBlaster->getPos().x <= GridConstants::HALFCELLSIZE) {
			moveRight = true;
		}
		return true;
	}
	else {
		return false;
	}
}

bool MovementAi::CheckRight() {
	if (moving == false) {
		return false;
	}
	if (moveRight == true) {
		if (myBlaster->getPos().x >= WindowManager::Window().getView().getSize().x - GridConstants::HALFCELLSIZE) {
			moveRight = false;
		}
		return true;
	}
	else {
		return false;
	}
}

bool MovementAi::CheckFire() {
	frameCount++;
	if (frameCount % WAITTIME == 0) {
		moving = !moving;
	}
	return true;
}