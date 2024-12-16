#pragma once

//Singleton for Score

#include <queue>
#include "TEAL\CommonElements.h"

class CommandScore;
class WriteText;

struct Highscore {
	std::string name = "aaa";
	int score = 10000;
};

class ScoreManager
{
private:
	// Score values;
	static const int FleaDeath = 200;
	static const int ScorpionDeath = 1000;
	static const int MushroomDeath = 1;
	static const int MushroomRecover = 5;

	static const int SpiderDeathFar = 300;
	static const int SpiderDistFar = 9999;

	static const int SpiderDeathMedium = 600;
	static const int SpiderDistMedium = 96;

	static const int SpiderDeathNear = 900;
	static const int SpiderDistNear = 48;

	static const int CentipedeHeadDeath = 100;
	static const int CentipedeBodyDeath = 10;

	int totalScore;
	Highscore highScores[8];

	int extraLife;

	WriteText* t;

	std::queue<CommandScore*> QueueCommands;

	static ScoreManager* ptrInstance;

	ScoreManager();
	ScoreManager(const ScoreManager&) = delete;
	ScoreManager& operator=(const ScoreManager&) = delete;
	virtual ~ScoreManager() = default;

	static ScoreManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ScoreManager();
		return *ptrInstance;
	};

	void privProcessScore();

	void privAddScore(int val);
	void privHighScore();
	void privSceneSwap();
	Highscore privGetHighScore(int i);
	
	void privHighScoreNameSort(std::string n);

	void privSetWriteText(WriteText* pt);



public:
	// events
	enum class ScoreEvents { FleaKilled, ScorpionKilled, MushroomKilled, MushroomRecover, SpiderKilled, HeadKilled, BodyKilled };

	static void AddScore(int val);
	static void CheckHighScore() { Instance().privHighScore(); }
	static Highscore GetHighScore(int i) { return Instance().privGetHighScore(i); }
	static void setWriteText(WriteText* pt) { Instance().privSetWriteText(pt); }

	static void HighScoreNameSort(std::string n) { Instance().privHighScoreNameSort(n); };

	static CommandScore* GetScoreCommand(ScoreEvents ev);

	static void SendScoreCommand(CommandScore* c);
	static void ProcessScores();

	static void SceneSwap() { Instance().privSceneSwap(); };
	static void DeleteSelf();


private:
	static bool privCompareHighscores(const Highscore a, const Highscore b);

};