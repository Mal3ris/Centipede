// ScorpionFactory

#include "TEAL\CommonElements.h"
#include "ScorpionFactory.h"
#include "Scorpion.h"
#include "ScorpionPool.h"
#include "ScorpionSpawner.h"
#include "SoundManager.h"
#include "CommandSound.h"
#include "CommandSoundLoop.h"
#include <list>

ScorpionPool* ScorpionFactory::myScorpionPool = nullptr;
std::list<Scorpion*> scorpionList;

CommandSound* ScorpionFactory::pSound = nullptr;

//Constructor setting up everything I need
ScorpionFactory::ScorpionFactory(ScorpionSpawner* pSpawner)
{
	myMushroomGrid = nullptr;
	myScorpionSpawner = pSpawner;
	myScorpionPool = new ScorpionPool();
	pSound = SoundManager::GetSoundCommand(SoundManager::SoundEvents::ScorpionLoop);

	
}

//Sets up Scorpion where Necessary
void ScorpionFactory::CreateScorpion(sf::Vector2f location, bool moveRight, float speed) {
	Scorpion* tempScorpion = myScorpionPool->GetScorpion();
	tempScorpion->SetExternalManagement(RecycleScorpion);

	tempScorpion->Initialize(location, moveRight, speed, this, myScorpionSpawner);

	scorpionList.push_back(tempScorpion);
	SoundManager::SendSoundCommand(pSound);
}

//Recycles Scorpions
void ScorpionFactory::RecycleScorpion(GameObject* b) {
	myScorpionPool->ReturnScorpion(static_cast<Scorpion*>(b));
}

//Brings all active scorpions back to factory
void ScorpionFactory::recallAll() {
	static_cast<CommandSoundLoop*>(pSound)->PauseSound();
	while (scorpionList.empty() == false) {
		scorpionList.front()->MarkForDestroy();
	}
}

//Used to remove scorpion from the active list once destroyed
void ScorpionFactory::removeSpecific(Scorpion* b) {
	scorpionList.erase(std::find(scorpionList.begin(), scorpionList.end(), b));
	if (scorpionList.empty()) {
		static_cast<CommandSoundLoop*>(pSound)->PauseSound();
	}
}

//Pauses Sound
void ScorpionFactory::Pause() {
	static_cast<CommandSoundLoop*>(pSound)->PauseSound();
}

//Plays Sound
void ScorpionFactory::Play() {
	if (scorpionList.empty() == false) {
		pSound->Execute();
	}
}

//Deletes Pool and Command
ScorpionFactory::~ScorpionFactory() {
	delete pSound;
	delete myScorpionPool;
}