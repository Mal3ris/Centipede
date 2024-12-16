#pragma once

//Mute Strategy Derives from Sound Strat

#include "TEAL\CommonElements.h"
#include "SoundStrategy.h"

class CommandSound;

class SoundMute: public SoundStrategy
{
public:

	SoundMute() = default;
	SoundMute(const SoundMute&) = delete;
	SoundMute& operator=(const SoundMute&) = delete;
	~SoundMute() = default;

	virtual void process();
	virtual void send(CommandSound* c);

};