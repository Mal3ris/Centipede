#pragma once

//Scorpion Factory

#include "TEAL\CommonElements.h"

// Forward declarations
class ScorpionPool;
class GameObject;
class MushroomSpawner;
class ScorpionSpawner;
class Scorpion;
class CommandSound;

class ScorpionFactory
{
public:
	ScorpionFactory(ScorpionSpawner* pSpawner);
	ScorpionFactory(const ScorpionFactory&) = delete;
	ScorpionFactory& operator=(const ScorpionFactory&) = delete;
	~ScorpionFactory();


	void CreateScorpion(sf::Vector2f location, bool moveRight, float speed);

	static void RecycleScorpion(GameObject* b);

	void recallAll();

	void removeSpecific(Scorpion* b);
	
	void Pause();
	void Play();


private:
	static ScorpionPool* myScorpionPool;

	MushroomSpawner* myMushroomGrid;

	ScorpionSpawner* myScorpionSpawner;
	
	static CommandSound* pSound;
};
