#pragma once

//Single Sound Derives from Command Sound

#include "CommandSound.h"

class CommandSoundLoop : public CommandSound
{
protected:
	sf::Sound& sound;	// sound to play

	bool active;

public:
	CommandSoundLoop(sf::Sound* tmp);
	CommandSoundLoop() = default;
	CommandSoundLoop(const CommandSoundLoop&) = delete;
	CommandSoundLoop& operator=(const CommandSoundLoop&) = delete;
	virtual ~CommandSoundLoop();

	void PauseSound();

	virtual void Execute() override;

};
