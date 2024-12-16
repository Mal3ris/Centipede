#pragma once

#include "TEAL\CommonElements.h"

class MoveStateCentipede;

class MoveLeftAndDownCentipede;
class MoveLeftAndUpCentipede;
class MoveRightAndDownCentipede;
class MoveRightAndUpCentipede;
class MoveDownToRightCentipede;
class MoveUpToRightCentipede;
class MoveDownToLeftCentipede;
class MoveUpToLeftCentipede;
class MoveLeftPoisonCentipede;
class MoveRightPoisonCentipede;

class MoveFSM
{
public:
	static const MoveLeftAndDownCentipede StateMoveLeftDown;
	static const MoveLeftAndUpCentipede StateMoveLeftUp;
	static const MoveRightAndDownCentipede StateMoveRightDown;
	static const MoveRightAndUpCentipede StateMoveRightUp;
	static const MoveDownToRightCentipede StateMoveDownRight;
	static const MoveDownToLeftCentipede StateMoveDownLeft;
	static const MoveUpToRightCentipede StateMoveUpRight;
	static const MoveUpToLeftCentipede StateMoveUpLeft;
	static const MoveLeftPoisonCentipede StateMovePoisonLeft;
	static const MoveRightPoisonCentipede StateMovePoisonRight;
};