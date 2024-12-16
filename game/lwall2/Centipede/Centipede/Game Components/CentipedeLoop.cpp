#include "TEAL/CommonElements.h"
#include "CentipedeLoop.h"
#include "CentipedeSpawner.h"

CentipedeLoop::CentipedeLoop(CentipedeSpawner* spawn) {
	mySpawn = spawn;
}

void CentipedeLoop::Alarm0() {
	mySpawn->SpawnBottomCentipede();
}

void CentipedeLoop::Alarm1() {
	mySpawn->SpawnBottomCentipede();
}

void CentipedeLoop::Alarm2() {
	mySpawn->SpawnBottomCentipede();
}

void CentipedeLoop::Alarm3() {
	mySpawn->SpawnBottomCentipede();
}

void CentipedeLoop::Alarm4() {
	mySpawn->SpawnBottomCentipede();
}