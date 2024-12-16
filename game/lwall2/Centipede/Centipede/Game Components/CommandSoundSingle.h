#pragma once

//Single Sound Derives from Command Sound

#include "CommandSound.h"


class CommandSoundSingle : public CommandSound
{
protected:
	sf::Sound& sound;	// sound to play

public:
	CommandSoundSingle(sf::Sound* tmp);
	CommandSoundSingle() = default;
	CommandSoundSingle(const CommandSoundSingle&) = delete;
	CommandSoundSingle& operator=(const CommandSoundSingle&) = delete;
	virtual ~CommandSoundSingle() = default;


	virtual void Execute() override;

};
