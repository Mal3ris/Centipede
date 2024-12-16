#pragma once

#include "TEAL\CommonElements.h"

class AttractorScreen : public Scene
{
public:


	AttractorScreen() = default;
	AttractorScreen(const AttractorScreen&) = delete;
	AttractorScreen& operator=(const AttractorScreen&) = delete;
	~AttractorScreen() = default;

	void Terminate();

	virtual void Initialize();


private:
};
