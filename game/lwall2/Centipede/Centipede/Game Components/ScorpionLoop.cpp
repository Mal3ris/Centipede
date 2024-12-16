#include "TEAL/CommonElements.h"
#include "ScorpionLoop.h"
#include "ScorpionSpawner.h"

//Constructor setting up observer
ScorpionLoop::ScorpionLoop(ScorpionSpawner* spawn) {
	mySpawn = spawn;
}

//Alarm for Spawning
void ScorpionLoop::Alarm0() {
	mySpawn->spawnScorpion();
}