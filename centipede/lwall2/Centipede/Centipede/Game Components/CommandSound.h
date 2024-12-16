#pragma once

//Basic Command File for Sounds

#include "TEAL\CommonElements.h"

class CommandSound
{
public:
	CommandSound() = default;
	CommandSound(const CommandSound&) = delete;
	CommandSound& operator=(const CommandSound&) = delete;
	virtual ~CommandSound() = default;

	// Note: the Excecute method must NOT have _any_ paramters
	virtual void Execute() = 0;
};
