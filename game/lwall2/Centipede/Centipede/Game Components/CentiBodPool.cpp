#include "CentiBodPool.h"
#include "TEAL\CommonElements.h"
#include "CentiBod.h"

CentiBod* CentiBodPool::GetCentiBod() {
	CentiBod* tempCentiBod;

	if (recycledCentiBod.empty()) {
		//ConsoleMsg::WriteLine("Fresh CentiBod");
		tempCentiBod = new CentiBod();
	}
	else {
		//ConsoleMsg::WriteLine("Recycled CentiBod");
		tempCentiBod = recycledCentiBod.top();
		recycledCentiBod.pop();

		tempCentiBod->RegisterToCurrentScene();
	}

	return tempCentiBod;
}

void CentiBodPool::ReturnCentiBod(CentiBod* b) {
	//BANDAID FIX CAUSE OBJECT WAS PUSHING TO STACK TWICE
	std::stack<CentiBod*> tmp = recycledCentiBod;
	while (!tmp.empty()) {
		if (tmp.top() == b) {
			return;
		}
		tmp.pop();
	}
	recycledCentiBod.push(static_cast<CentiBod*>(b));
}

CentiBodPool::~CentiBodPool() {
	while (!recycledCentiBod.empty()) {
		recycledCentiBod.top()->CleanCommands();
		delete recycledCentiBod.top();
		recycledCentiBod.pop();
	}
}