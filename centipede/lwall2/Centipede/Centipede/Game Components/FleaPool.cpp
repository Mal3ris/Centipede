#include "FleaPool.h"
#include "TEAL\CommonElements.h"
#include "Flea.h"

Flea* FleaPool::GetFlea() {
	Flea* tempFlea;

	if (recycledFlea.empty()) {
		//ConsoleMsg::WriteLine("Fresh Flea");
		tempFlea = new Flea();
	}
	else {
		//ConsoleMsg::WriteLine("Recycled Flea");
		tempFlea = recycledFlea.top();
		recycledFlea.pop();

		tempFlea->RegisterToCurrentScene();
	}

	return tempFlea;
}

void FleaPool::ReturnFlea(Flea* b) {
	//BANDAID FIX CAUSE OBJECT WAS PUSHING TO STACK TWICE
	std::stack<Flea*> tmp = recycledFlea;
	while (!tmp.empty()) {
		if (tmp.top() == b) {
			return;
		}
		tmp.pop();
	}
	recycledFlea.push(static_cast<Flea*>(b));
}

FleaPool::~FleaPool() {
	while (!recycledFlea.empty()) {
		recycledFlea.top()->CleanCommands();
		delete recycledFlea.top();
		recycledFlea.pop();
	}
}