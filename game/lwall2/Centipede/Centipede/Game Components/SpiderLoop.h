#pragma once

//Little Buddy Loop for Spider Spawner
//In charge of the alarms as well

#include "TEAL\CommonElements.h"

class SpiderSpawner;

class SpiderLoop : public GameObject
{
public:
	SpiderLoop() = delete;								
	SpiderLoop(SpiderSpawner* spawn);					 
	SpiderLoop(const SpiderLoop&) = delete;				
	SpiderLoop& operator=(const SpiderLoop&) = delete;	
	~SpiderLoop() = default;


	virtual void Alarm0();


private:
	SpiderSpawner* mySpawn;
};