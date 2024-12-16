#include "ScorpionPool.h"
#include "TEAL\CommonElements.h"
#include "Scorpion.h"

//Returns the Scorpion from the pool
Scorpion* ScorpionPool::GetScorpion() {
	Scorpion* tempScorpion;

	if (recycledScorpion.empty()) {
		//ConsoleMsg::WriteLine("Fresh Scorpion");
		tempScorpion = new Scorpion();
	}
	else {
		//ConsoleMsg::WriteLine("Recycled Scorpion");
		tempScorpion = recycledScorpion.top();
		recycledScorpion.pop();

		tempScorpion->RegisterToCurrentScene();
	}

	return tempScorpion;
}

//Puts deleted objects back into pool
void ScorpionPool::ReturnScorpion(Scorpion* b) {
	//BANDAID FIX CAUSE OBJECT WAS PUSHING TO STACK TWICE
	std::stack<Scorpion*> tmp = recycledScorpion;
	while (!tmp.empty()) {
		if (tmp.top() == b) {
			return;
		}
		tmp.pop();
	}
	recycledScorpion.push(static_cast<Scorpion*>(b));
}

//Cleans out Scorpions and sends func to delete commands
ScorpionPool::~ScorpionPool() {
	while (!recycledScorpion.empty()) {
		recycledScorpion.top()->CleanCommands();
		delete recycledScorpion.top();
		recycledScorpion.pop();
	}
}