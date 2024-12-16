#pragma once

#include "TEAL\CommonElements.h"

class MovementKeys : public MovementStrategy
{
public:
	MovementKeys() = default;
	MovementKeys(const MovementKeys&) = delete;
	MovementKeys& operator=(const MovementKeys&) = delete;
	~MovementKeys() = default;

	virtual bool CheckUp();
	virtual bool CheckDown();
	virtual bool CheckLeft();
	virtual bool CheckRight();
	virtual bool CheckFire();

private:

};
