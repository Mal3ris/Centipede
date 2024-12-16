#include "TEAL\CommonElements.h"
#include "SpiderFactory.h"
#include "Spider.h"
#include "SpiderPool.h"
#include "SpiderSpawner.h"
#include "SoundManager.h"
#include "CommandSound.h"
#include "CommandSoundLoop.h"
#include <list>

SpiderPool* SpiderFactory::mySpiderPool = nullptr;
SpiderSpawner* SpiderFactory::mySpiderSpawner = nullptr;
MushroomSpawner* SpiderFactory::myMushroomGrid = nullptr;
std::list<Spider*> SpiderFactory::spiderList;

//Constructor For Creating Pool and looping pSound
SpiderFactory::SpiderFactory()
{
	pSound = SoundManager::GetSoundCommand(SoundManager::SoundEvents::SpiderLoop);
	mySpiderPool = new SpiderPool();
}

//Sets the Spiders Spawner
void SpiderFactory::setSpawner(SpiderSpawner* tmp) {
	mySpiderSpawner = tmp;
}

//Creates and Initializes Spider
void SpiderFactory::CreateSpider(sf::Vector2f location, bool moveRight, float speed) {
	Spider* tempSpider = mySpiderPool->GetSpider();
	tempSpider->SetExternalManagement(RecycleSpider);
	
	tempSpider->Initialize(location, moveRight,speed, this, mySpiderSpawner);

	spiderList.push_back(tempSpider);
	SoundManager::SendSoundCommand(pSound);
}

//Recycles Spider
void SpiderFactory::RecycleSpider(GameObject* b) {
	mySpiderPool->ReturnSpider(static_cast<Spider*>(b));
}

//Returns all of the spiders back to the factory
void SpiderFactory::recallAll() {
	while (!spiderList.empty()) {
		spiderList.front()->MarkForDestroy();
		spiderList.pop_front();
	}
	static_cast<CommandSoundLoop*>(pSound)->PauseSound();
}

//Removes a Specific Spider from the active list
void SpiderFactory::removeSpecific(Spider* b) {

	spiderList.erase(std::find(spiderList.begin(), spiderList.end(), b));
	if (spiderList.empty() == true) {
		static_cast<CommandSoundLoop*>(pSound)->PauseSound();
	}
}

//Pauses Sound
void SpiderFactory::Pause() {
	static_cast<CommandSoundLoop*>(pSound)->PauseSound();
}

//Plays Sound
void SpiderFactory::Play() {
	if (spiderList.empty() == false) {
		pSound->Execute();
	}
}

//Destructor that deletes pool and sound command
SpiderFactory::~SpiderFactory() {
	delete pSound;
	delete mySpiderPool;
}
