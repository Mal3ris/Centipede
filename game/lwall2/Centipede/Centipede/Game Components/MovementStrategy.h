#pragma once

#include "TEAL\CommonElements.h"

// Forward declarations
class Blaster;


class MovementStrategy
{
public:
	MovementStrategy() = default;
	MovementStrategy(const MovementStrategy&) = delete;
	MovementStrategy& operator=(const MovementStrategy&) = delete;
	~MovementStrategy() = default;

	void Initialize();
	void Terminate();

	void AffectMove();

	void SetStrat(char* strat, Blaster* pBlaster);

	virtual bool CheckUp();
	virtual bool CheckDown();
	virtual bool CheckLeft();
	virtual bool CheckRight();
	virtual bool CheckFire();

private:
	
	MovementStrategy* currPat = nullptr;
	MovementStrategy* ai;
	MovementStrategy* keys;

	Blaster* myBlaster = nullptr;

};
