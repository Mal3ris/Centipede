#include "CommandScoreByValue.h"
#include <iostream>
#include "ScoreManager.h"

CommandScoreByValue::CommandScoreByValue(int val)
	: points(val)
{
}

void CommandScoreByValue::Execute()
{
	ScoreManager::AddScore(points);
}