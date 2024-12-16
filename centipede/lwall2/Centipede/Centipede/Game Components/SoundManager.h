#pragma once

//Command Pattern Sound

#include <queue>
#include "TEAL\CommonElements.h"

class CommandSound;
class CommandSoundLoop;
class SoundStrategy;
class CentipedeFactory;
class SpiderFactory;
class ScorpionFactory;

class SoundManager
{
private:
	// Sound values;
	static sf::Sound* laser;
	static sf::Sound* mushroom;
	static sf::Sound* death;
	static sf::Sound* kill;

	static sf::Sound* Centipede;
	static sf::Sound* Scorpion;
	static sf::Sound* Spider;

	static CommandSoundLoop* centiActive;
	static CommandSoundLoop* spiderActive;
	static CommandSoundLoop* scorpiActive;

	static bool centiActiveBool;
	static bool spiderActiveBool;
	static bool scorpiActiveBool;

	static bool mute;


	static std::queue<CommandSound*> QueueCommands;

	static SoundManager* ptrInstance;

	SoundManager();
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;
	virtual ~SoundManager() = default;

	static SoundManager& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new SoundManager();
		return *ptrInstance;
	};

	void privProcessSound();

	void privSendSoundCommand(CommandSound* c);
	
	void privMute(CentipedeFactory* c, SpiderFactory* sp, ScorpionFactory* sf);

	
	static SoundStrategy* myStrat;


public:

	// events
	enum class SoundEvents { CentipedeLoop, SpiderLoop, ScorpionLoop, Blaster, Death, Mushroom, Kill };

	static CommandSound* GetSoundCommand(SoundEvents ev);

	static void Mute(CentipedeFactory* c, SpiderFactory* sp, ScorpionFactory* sf) { Instance().privMute(c, sp, sf); };

	static void SendSoundCommand(CommandSound* c) {
		Instance().privSendSoundCommand(c); };
	static void ProcessSounds();
	static std::queue<CommandSound*>& getQueue() { return Instance().privGetQueue(); };
	static void ForceMute(CentipedeFactory* c, SpiderFactory* sp, ScorpionFactory* sf) 
	{ Instance().privForceMute(c, sp, sf); };
	static void StartSound(CentipedeFactory* c, SpiderFactory* sp, ScorpionFactory* sf)
	{
		Instance().privStartSound(c, sp, sf);
	};


	static void DeleteSelf();

private:
	void privForceMute(CentipedeFactory* c, SpiderFactory* sp, ScorpionFactory* sf);
	void privStartSound(CentipedeFactory* c, SpiderFactory* sp, ScorpionFactory* sf);

	std::queue<CommandSound*>& privGetQueue() { return QueueCommands; };

};