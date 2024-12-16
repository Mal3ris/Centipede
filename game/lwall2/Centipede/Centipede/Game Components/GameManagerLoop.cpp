#include "GameManagerLoop.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "ScoreManager.h"
#include "PlayerManager.h"

#include "PlayScreen.h"
#include "AttractorScreen.h"

#include "WriteText.h"


//Sets up loop and takes in a string to know what active screen is
GameManagerLoop::GameManagerLoop(std::string Screen) {
	screen = Screen;

	myText = new WriteText(TileFactory::getFactory(), screen);
	ScoreManager::setWriteText(myText);
	if (screen == "highscore") {
		myText->WriteHighScoreScreen();
	}
	else {
		if (screen == "attractor")
		{
			myText->WriteHighScores();
		}
		myText->WriteLine();
		myText->WriteCopyright();
	}
	

	RegisterInput(InputFlags::KeyPressed);
}

void GameManagerLoop::KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey)
{
	//Attractor only needs num 1 press
	if (screen == "attractor") {
		if (k == sf::Keyboard::Num1)
		{
			ScoreManager::ProcessScores();
			PlayerManager::addScore(-1 * PlayerManager::getPlayer().score);
			GameManager::SwapScene();
			PlayerManager::setScore(0);
			ScoreManager::SceneSwap();
			SceneManager::ChangeScene(new PlayScreen());
			
		}
	}
	//Can only Mute and Unmute during Gameplay
	else if (screen == "gameplay") {
		if (k == sf::Keyboard::M) {
			GameManager::Mute();
		}
	}
	//Highscore takes in all inputs and parses accordingly
	else if (screen == "highscore") {
		if (k == sf::Keyboard::BackSpace) {
			if (initials.empty() == false) {
				initials.pop_back();
			}
		}
		else if (k == sf::Keyboard::Enter) {
			if (initials.length() < INITIALSLEN) {
				for (int i = initials.length(); i < (int)INITIALSLEN; i++) {
					initials.push_back(' ');
				}
			}
			ScoreManager::HighScoreNameSort(initials);
			PlayerManager::setScore(0);
			GameManager::SwapScene();
			ScoreManager::SceneSwap();
			SceneManager::ChangeScene(new AttractorScreen());
		}
		else if (k == sf::Keyboard::Space) {
			if (initials.length() < INITIALSLEN) {
				initials.push_back(' ');
			}
		}
		else if (k >= 0 && k < 26) {
			if (initials.length() < INITIALSLEN) {
				initials.push_back(k + 97);
			}
		}
		myText->WriteInitials(initials);
	}
	//NEVER SHOULD BE HERE
	else {
		ConsoleMsg::WriteLine("ERROR IN MANAGER LOOP");
		assert(false);
	}
}

//Used for displaying score
void GameManagerLoop::Write() {
	myText->WriteLine();
}

//Necessary Update Loop For Processing Commands
void GameManagerLoop::Update() {
	ScoreManager::ProcessScores();
	SoundManager::ProcessSounds();
}

//Destructor
void GameManagerLoop::Destroy() {
	DeregisterInput();
}