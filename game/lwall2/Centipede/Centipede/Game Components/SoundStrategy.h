#pragma once

//Strategy Pattern for sound Base Class

#include "TEAL\CommonElements.h"

class CommandSound;

class SoundStrategy
{
public:
	enum class MuteEvents { Mute, Unmute };

	SoundStrategy(MuteEvents m);
	SoundStrategy() = default;
	SoundStrategy(const SoundStrategy&) = delete;
	SoundStrategy& operator=(const SoundStrategy&) = delete;
	~SoundStrategy();

	void ProcessSound();
	void SendCommand(CommandSound* c);

	virtual void process();
	virtual void send(CommandSound* c);

	
	void changePat(MuteEvents m);

private:
	SoundStrategy* currPat = nullptr;
	SoundStrategy* mute = nullptr;
	SoundStrategy* play = nullptr;
};
