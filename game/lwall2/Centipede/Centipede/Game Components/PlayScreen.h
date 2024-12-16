#pragma once

#include "TEAL\CommonElements.h"

class GameController;

class Blaster;
class FleaSpawner;
class FleaFactory;
class MushroomSpawner;
class MushroomFactory;
class BulletFactory;
class CentipedeFactory;
class CentiBodFactory;
class CentipedeSpawner;
class ScorpionSpawner;
class ScorpionFactory;
class SpiderSpawner;
class SpiderFactory;
class ScoreManager;

class PlayScreen : public Scene
{
public:

	PlayScreen() = default;
	PlayScreen(const PlayScreen&) = delete;
	PlayScreen& operator=(const PlayScreen&) = delete;
	~PlayScreen() = default;

	virtual void Initialize();


private:
};
