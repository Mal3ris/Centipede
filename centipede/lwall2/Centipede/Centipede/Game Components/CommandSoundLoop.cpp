#include "CommandSound.h"
#include "CommandSoundLoop.h"
#include <iostream>
#include "SoundManager.h"

//Adds command then also sets it as a loop
CommandSoundLoop::CommandSoundLoop(sf::Sound* tmp) : sound(*tmp) {
	sound.setLoop(true);
	active = false;
}

//Plays Command
void CommandSoundLoop::Execute()
{
	if (active == false) {
		sound.play();
		active = true;
	}
}

//Pauses Sound and Deletes loop
CommandSoundLoop::~CommandSoundLoop() {
	sound.stop();
	active = false;
}

//Pauses Sound for Muting
void CommandSoundLoop::PauseSound() {
	sound.stop();
	active = false;
}