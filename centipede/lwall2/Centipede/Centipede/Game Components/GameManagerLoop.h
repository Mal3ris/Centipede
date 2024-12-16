#pragma once

//Buddy Object for Game Manager Singleton that fulfills GameObject roles
//In charge of Update Loop and Key Inputs

#include "TEAL\CommonElements.h"

//forward declaration
class WriteText;

class GameManagerLoop : public GameObject
{
public:
	GameManagerLoop() = delete;									
	GameManagerLoop(std::string screen);						
	GameManagerLoop(const GameManagerLoop&) = delete;			
	GameManagerLoop& operator=(const GameManagerLoop&) = delete;
	~GameManagerLoop() = default;

	virtual void KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey);


	virtual void Destroy();
	virtual void Update();

	void Write();

private:
	std::string screen;
	std::string initials;

	WriteText* myText;

	const unsigned int INITIALSLEN = 3;

};