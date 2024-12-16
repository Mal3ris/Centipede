#pragma once

#include "TEAL\CommonElements.h"



class HighScoreScreen : public Scene
{
public:

	HighScoreScreen() = default;
	HighScoreScreen(const HighScoreScreen&) = delete;
	HighScoreScreen& operator=(const HighScoreScreen&) = delete;
	~HighScoreScreen() = default;

	virtual void Initialize();

};
