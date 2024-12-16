#include "HighScoreScreen.h"
#include "GameManager.h"

void HighScoreScreen::Initialize()
{
	WindowManager::SetBackgroundColor(sf::Color(0, 0, 0, 255));

	GameManager::Initialize("highscore");
}