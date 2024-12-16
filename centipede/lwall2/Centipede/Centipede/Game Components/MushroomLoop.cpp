#include "TEAL/CommonElements.h"
#include "MushroomLoop.h"
#include "MushroomSpawner.h"
#include "GameManager.h"

void MushroomLoop::Alarm0() {
	GameManager::StartPlay();
}
