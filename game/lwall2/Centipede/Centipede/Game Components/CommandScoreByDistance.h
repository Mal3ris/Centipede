#pragma once

#include "CommandScore.h"

class CommandScoreByDistance : public CommandScore
{
private:
	int dNear;
	int dMed;
	int dFar;
	int vNear;
	int vMed;
	int vFar;

	int score;

public:
	CommandScoreByDistance() = delete;
	CommandScoreByDistance(const CommandScoreByDistance&) = delete;
	CommandScoreByDistance& operator=(const CommandScoreByDistance&) = delete;
	virtual ~CommandScoreByDistance() = default;

	CommandScoreByDistance(int dNear, int dMed, int dFar,
		int vNear, int vMed, int vFar);

	virtual void Execute() override;

	int CalcDist(int i);
};
