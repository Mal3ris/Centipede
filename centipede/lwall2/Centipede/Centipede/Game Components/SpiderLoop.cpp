#include "TEAL/CommonElements.h"
#include "SpiderLoop.h"
#include "SpiderSpawner.h"

//Observer Pattern For spawner
SpiderLoop::SpiderLoop(SpiderSpawner* spawn) {
	mySpawn = spawn;
}

//Alarm
void SpiderLoop::Alarm0() {
	mySpawn->spawnSpider();
}