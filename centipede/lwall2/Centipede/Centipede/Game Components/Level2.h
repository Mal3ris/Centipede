// Level1
// Andre Berthiaume, March 2013

#ifndef _Level2
#define _Level2

#include "TEAL\CommonElements.h"

class Level2 : public Scene
{
public:
	Level2() = default;
	Level2(const Level2&) = delete;
	Level2& operator=(const Level2&) = delete;
	~Level2() = default;

	virtual void Initialize();
	virtual void Terminate();
};

#endif _Level1