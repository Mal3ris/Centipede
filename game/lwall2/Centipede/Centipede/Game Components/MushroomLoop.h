#pragma once

#include "TEAL\CommonElements.h"

class MushroomSpawner;

class MushroomLoop : public GameObject
{
public:			
	MushroomLoop() = default;								
	MushroomLoop(const MushroomLoop&) = delete;				
	MushroomLoop& operator=(const MushroomLoop&) = delete;	
	~MushroomLoop() = default;

	virtual void Alarm0();


private:
};