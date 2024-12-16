#include "SoundManager.h"

#include "CommandSoundSingle.h"
#include "CommandSoundLoop.h"
#include "PlayerManager.h"
#include "SoundStrategy.h"
#include "CentipedeFactory.h"
#include "SpiderFactory.h"
#include "ScorpionFactory.h"

SoundManager* SoundManager::ptrInstance = nullptr;

sf::Sound* SoundManager::laser = nullptr;
sf::Sound* SoundManager::kill = nullptr;
sf::Sound* SoundManager::death = nullptr;
sf::Sound* SoundManager::mushroom = nullptr;

sf::Sound* SoundManager::Centipede = nullptr;
sf::Sound* SoundManager::Spider = nullptr;
sf::Sound* SoundManager::Scorpion = nullptr;

CommandSoundLoop* SoundManager::scorpiActive = nullptr;
CommandSoundLoop* SoundManager::centiActive = nullptr;
CommandSoundLoop* SoundManager::spiderActive = nullptr;

bool SoundManager::scorpiActiveBool = nullptr;
bool SoundManager::centiActiveBool = nullptr;
bool SoundManager::spiderActiveBool = nullptr;

bool SoundManager::mute = false;

SoundStrategy* SoundManager::myStrat = nullptr;

std::queue<CommandSound*> SoundManager::QueueCommands;

//Constructor that Loads sounds and Creates Strategy
SoundManager::SoundManager() {

	myStrat = new SoundStrategy(SoundStrategy::MuteEvents::Unmute);

	laser = new sf::Sound();
	laser->setBuffer(ResourceManager::GetSound("Fire"));
	laser->setVolume(10);

	kill = new sf::Sound();
	kill->setBuffer(ResourceManager::GetSound("Kill"));
	kill->setVolume(10);

	death = new sf::Sound();
	death->setBuffer(ResourceManager::GetSound("Death"));
	death->setVolume(10);

	mushroom = new sf::Sound();
	mushroom->setBuffer(ResourceManager::GetSound("Bonus"));
	mushroom->setVolume(10);

	Centipede = new sf::Sound();
	Centipede->setBuffer(ResourceManager::GetSound("Beat"));
	Centipede->setVolume(10);

	Scorpion = new sf::Sound();
	Scorpion->setBuffer(ResourceManager::GetSound("Scorpion"));
	Scorpion->setVolume(10);

	Spider = new sf::Sound();
	Spider->setBuffer(ResourceManager::GetSound("Spider"));
	Spider->setVolume(10);
}

//Returns The Sound Command
CommandSound* SoundManager::GetSoundCommand(SoundEvents ev)
{
	CommandSound* pCommand = nullptr;

	switch (ev)
	{
	case SoundEvents::Blaster:
		pCommand = new CommandSoundSingle(laser);
		break;
	case SoundEvents::Death:
		pCommand = new CommandSoundSingle(death);
		break;
	case SoundEvents::Kill:
		pCommand = new CommandSoundSingle(kill);
		break;
	case SoundEvents::Mushroom:
		pCommand = new CommandSoundSingle(mushroom);
		break;
	case SoundEvents::CentipedeLoop:
		pCommand = new CommandSoundLoop(Centipede);
		break;
	case SoundEvents::ScorpionLoop:
		pCommand = new CommandSoundLoop(Scorpion);
		break;
	case SoundEvents::SpiderLoop:
		pCommand = new CommandSoundLoop(Spider);
		break;
	default:
		break;
	}

	return pCommand;
}

//Sends Command To Strategy
void SoundManager::privSendSoundCommand(CommandSound* c)
{
	myStrat->SendCommand(c);
}

//Processes Command
void SoundManager::ProcessSounds()
{
	Instance().privProcessSound();
}

//Sends Process to Strat
void SoundManager::privProcessSound()
{
	myStrat->ProcessSound();
}


void SoundManager::privMute(CentipedeFactory* c, SpiderFactory* sp, ScorpionFactory* sf){
	if (mute == false) {
		mute = true;
		myStrat->changePat(SoundStrategy::MuteEvents::Mute);
		c->Pause();
		sp->Pause();
		sf->Pause();
	}
	else {
		mute = false;
		myStrat->changePat(SoundStrategy::MuteEvents::Unmute);
		c->Play();
		sp->Play();
		sf->Play();
	}
}

void SoundManager::privForceMute(CentipedeFactory* c, SpiderFactory* sp, ScorpionFactory* sf) {
	CommandSound* com;

	while (!QueueCommands.empty())
	{
		com = QueueCommands.front();

		QueueCommands.pop();

	}
	myStrat->changePat(SoundStrategy::MuteEvents::Mute);
	c->Pause();
	sp->Pause();
	sf->Pause();
}

//Plays All Sounds
void SoundManager::privStartSound(CentipedeFactory* c, SpiderFactory* sp, ScorpionFactory* sf) {
	if (mute == false) {
		myStrat->changePat(SoundStrategy::MuteEvents::Unmute);
		c->Play();
		sp->Play();
		sf->Play();
	}
}

//Cleans Sounds
void SoundManager::DeleteSelf() {
	
	delete laser;
	delete kill;
	delete mushroom;
	delete death;

	delete Centipede;
	delete Scorpion;
	delete Spider;

	delete myStrat;
	delete ptrInstance;
	ptrInstance = nullptr;
}
