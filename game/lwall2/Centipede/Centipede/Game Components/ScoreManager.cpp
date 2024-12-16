#include "ScoreManager.h"
#include "CommandScoreByValue.h"
#include "CommandScoreByDistance.h"
#include "PlayerManager.h"
#include "GameManager.h"
#include "WriteText.h"
#include "HighScoreScreen.h"
#include "AttractorScreen.h"


ScoreManager* ScoreManager::ptrInstance = nullptr;


ScoreManager::ScoreManager() {
	totalScore = 0;
	extraLife = 0;
	t = nullptr;

	for (int i = 0; i < 8; i++) {
		highScores[i].score = highScores[i].score + i*500;
	}

	std::sort(highScores, highScores + 8, privCompareHighscores);
}

bool ScoreManager::privCompareHighscores(const Highscore a, const Highscore b) {
	return a.score > b.score; // Sort in descending order
}


CommandScore* ScoreManager::GetScoreCommand(ScoreEvents ev)
{
	CommandScore* pCommand = nullptr;

	switch (ev)
	{
	case ScoreEvents::FleaKilled:
		pCommand = new CommandScoreByValue(FleaDeath);
		break;
	case ScoreEvents::ScorpionKilled:
		pCommand = new CommandScoreByValue(ScorpionDeath);
		break;
	case ScoreEvents::MushroomKilled:
		pCommand = new CommandScoreByValue(MushroomDeath);
		break;
	case ScoreEvents::SpiderKilled:
		pCommand = new CommandScoreByDistance(SpiderDistNear, SpiderDistMedium, SpiderDistFar,
			SpiderDeathNear, SpiderDeathMedium, SpiderDeathFar);
		break;
	case ScoreEvents::MushroomRecover:
		pCommand = new CommandScoreByValue(MushroomRecover);
		break;
	case ScoreEvents::HeadKilled:
		pCommand = new CommandScoreByValue(CentipedeHeadDeath);
		break;
	case ScoreEvents::BodyKilled:
		pCommand = new CommandScoreByValue(CentipedeBodyDeath);
		break;
	default:
		break;
	}

	return pCommand;
}

void ScoreManager::privHighScore() {
	if (PlayerManager::getPlayer().score >= highScores[7].score) {
		highScores[7].score = PlayerManager::getPlayer().score;
		SceneManager::ChangeScene(new HighScoreScreen());
	}
	else {
		ScoreManager::SceneSwap();
		PlayerManager::addScore(-1 * PlayerManager::getPlayer().score);
		SceneManager::ChangeScene(new AttractorScreen());
	}

}

void ScoreManager::privSceneSwap() {
	totalScore = 0;
	extraLife = 0;
}

void ScoreManager::privHighScoreNameSort(std::string n) {
	highScores[7].name = n;
	std::sort(highScores, highScores + 8, privCompareHighscores);

	PlayerManager::addScore(-1 * PlayerManager::getPlayer().score);
}

void ScoreManager::privSetWriteText(WriteText* pwt) {
	t = pwt;
}

Highscore ScoreManager::privGetHighScore(int i) {
	return highScores[i];
}

void ScoreManager::AddScore(int val)
{
	Instance().privAddScore(val);
}

void ScoreManager::privAddScore(int val) {
	totalScore += val;
	extraLife += val;
	if (totalScore > 99999) {
		totalScore = 99999;
	}
	if (extraLife / 12000 >= 1) {
		PlayerManager::changeHealth(1);
		extraLife = extraLife % 12000;
	}

	PlayerManager::setScore(totalScore);
	t->WriteLine();
	
}

void ScoreManager::SendScoreCommand(CommandScore* c)
{
	Instance().QueueCommands.push(c);
}

void ScoreManager::ProcessScores()
{
	Instance().privProcessScore();
}

void ScoreManager::privProcessScore()
{

	CommandScore* c;

	while (!QueueCommands.empty())
	{
		c = QueueCommands.front();
		c->Execute();

		QueueCommands.pop();
		
	}

}

void ScoreManager::DeleteSelf() {
	delete ptrInstance;
	ptrInstance = nullptr;
}
