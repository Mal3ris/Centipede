#pragma once

//Loop In charge of Alarms for Scorpion

#include "TEAL\CommonElements.h"

class ScorpionSpawner;

class ScorpionLoop : public GameObject
{
public:			
	ScorpionLoop() = delete;							
	ScorpionLoop(ScorpionSpawner* spawn);				
	ScorpionLoop(const ScorpionLoop&) = delete;			
	ScorpionLoop& operator=(const ScorpionLoop&) = delete;	
	~ScorpionLoop() = default;


	virtual void Alarm0();


private:
	ScorpionSpawner* mySpawn;
};