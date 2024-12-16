#pragma once

#include "CommandScore.h"

class CommandScoreByValue : public CommandScore
{
protected:
	int points;	// points to add

public:
	CommandScoreByValue() = delete;
	CommandScoreByValue(const CommandScoreByValue&) = delete;
	CommandScoreByValue& operator=(const CommandScoreByValue&) = delete;
	virtual ~CommandScoreByValue() = default;

	CommandScoreByValue(int val);

	virtual void Execute() override;

};
