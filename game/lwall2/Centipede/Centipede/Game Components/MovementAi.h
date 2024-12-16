#pragma once

#include "TEAL\CommonElements.h"
#include "GridConstants.h"

// Forward declarations
class Blaster;


class MovementAi : public MovementStrategy
{
public:
	MovementAi() = default;
	MovementAi(const MovementAi&) = delete;
	MovementAi& operator=(const MovementAi&) = delete;
	~MovementAi() = default;

	void setBlaster(Blaster* blast);

	virtual bool CheckUp();
	virtual bool CheckDown();
	virtual bool CheckLeft();
	virtual bool CheckRight();
	virtual bool CheckFire();

private:
	bool moveUp = false;
	bool moveRight = false;

	int frameCount = 0;
	const int WAITTIME = 60;
	bool moving = false;

	Blaster* myBlaster;

};