#include "BlasterPool.h"
#include "TEAL\CommonElements.h"
#include "Blaster.h"

Blaster* BlasterPool::GetBlaster() {
	Blaster* tempBlaster;

	if (recycledBlaster.empty()) {
		//ConsoleMsg::WriteLine("Fresh Blaster");
		tempBlaster = new Blaster();
	}
	else {
		//ConsoleMsg::WriteLine("Recycled Blaster");
		tempBlaster = recycledBlaster.top();
		recycledBlaster.pop();

		tempBlaster->RegisterToCurrentScene();
	}

	return tempBlaster;
}

void BlasterPool::ReturnBlaster(Blaster* b) {
	//BANDAID FIX CAUSE OBJECT WAS PUSHING TO STACK TWICE
	std::stack<Blaster*> tmp = recycledBlaster;
	while (!tmp.empty()) {
		if (tmp.top() == b) {
			return;
		}
		tmp.pop();
	}
	recycledBlaster.push(static_cast<Blaster*>(b));
}

BlasterPool::~BlasterPool() {
	while (!recycledBlaster.empty()) {
		recycledBlaster.top()->CleanCommands();
		delete recycledBlaster.top();
		recycledBlaster.pop();
	}
}