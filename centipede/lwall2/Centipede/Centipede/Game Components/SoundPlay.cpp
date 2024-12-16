#include "SoundPlay.h"
#include "SoundStrategy.h"
#include "SoundManager.h"
#include "CommandSound.h"

//Processes Scores
void SoundPlay::process() {
	CommandSound* c;

	while (!SoundManager::getQueue().empty()) {
		c = SoundManager::getQueue().front();
		c->Execute();

		SoundManager::getQueue().pop();
	}
}

//Pushes Commands
void SoundPlay::send(CommandSound* c) {
	
	SoundManager::getQueue().push(c);
}