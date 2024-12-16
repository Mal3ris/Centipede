#include "CommandSound.h"
#include "CommandSoundSingle.h"
#include <iostream>
#include "SoundManager.h"

//Constructor for sound
CommandSoundSingle::CommandSoundSingle(sf::Sound* tmp): sound(*tmp){
}


//Plays sound
void CommandSoundSingle::Execute()
{
	sound.play();
}
