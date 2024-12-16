#pragma once

//Derives From SoundStrat that is used for Play

#include "TEAL\CommonElements.h"
#include "SoundStrategy.h"

class CommandSound;

class SoundPlay : public SoundStrategy
{
public:

	SoundPlay() = default;
	SoundPlay(const SoundPlay&) = delete;
	SoundPlay& operator=(const SoundPlay&) = delete;
	~SoundPlay() = default;

	virtual void process();
	virtual void send(CommandSound* c);

};