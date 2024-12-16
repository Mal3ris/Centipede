#pragma once

#include "TEAL\CommonElements.h"

class CentipedeSpawner;

class CentipedeLoop : public GameObject
{
public:
	CentipedeLoop() = delete;								
	CentipedeLoop(CentipedeSpawner* spawn);					
	CentipedeLoop(const CentipedeLoop&) = delete;			
	CentipedeLoop& operator=(const CentipedeLoop&) = delete;
	~CentipedeLoop() = default;

	//I dont like how this works
	virtual void Alarm0();
	virtual void Alarm1();
	virtual void Alarm2();
	virtual void Alarm3();
	virtual void Alarm4();


private:
	CentipedeSpawner* mySpawn;
};