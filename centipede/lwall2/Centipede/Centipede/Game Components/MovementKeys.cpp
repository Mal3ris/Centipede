#include "MovementStrategy.h"
#include "MovementKeys.h"


bool MovementKeys::CheckDown() {
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
}

bool MovementKeys::CheckUp() {
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
}

bool MovementKeys::CheckLeft() {
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
}

bool MovementKeys::CheckRight() {
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
}

bool MovementKeys::CheckFire() {
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
}