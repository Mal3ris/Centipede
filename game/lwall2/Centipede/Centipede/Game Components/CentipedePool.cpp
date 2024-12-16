#include "CentipedePool.h"
#include "TEAL\CommonElements.h"
#include "Centipede.h"

Centipede* CentipedePool::GetCentipede() {
	Centipede* tempCentipede;

	if (recycledCentipede.empty()) {
		//ConsoleMsg::WriteLine("Fresh Centipede");
		tempCentipede = new Centipede();
	}
	else {
		//ConsoleMsg::WriteLine("Recycled Centipede");
		tempCentipede = recycledCentipede.top();
		recycledCentipede.pop();

		tempCentipede->RegisterToCurrentScene();
	}

	return tempCentipede;
}

void CentipedePool::ReturnCentipede(Centipede* b) {
	//BANDAID FIX CAUSE OBJECT WAS PUSHING TO STACK TWICE
	std::stack<Centipede*> tmp = recycledCentipede;
	while (!tmp.empty()) {
		if (tmp.top() == b) {
			return;
		}
		tmp.pop();
	}
	recycledCentipede.push(static_cast<Centipede*>(b));
}

CentipedePool::~CentipedePool() {
	while (!recycledCentipede.empty()) {
		recycledCentipede.top()->CleanCommands();
		delete recycledCentipede.top();
		recycledCentipede.pop();
	}
}