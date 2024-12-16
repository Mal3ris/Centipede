#include "SpiderPool.h"
#include "TEAL\CommonElements.h"
#include "Spider.h"

//Grabs spider from pool and returns
Spider* SpiderPool::GetSpider() {
	Spider* tempSpider;

	if (recycledSpider.empty()) {
		//ConsoleMsg::WriteLine("Fresh Spider");
		tempSpider = new Spider();
	}
	else {
		//ConsoleMsg::WriteLine("Recycled Spider");
		tempSpider = recycledSpider.top();
		recycledSpider.pop();

		tempSpider->RegisterToCurrentScene();
	}

	return tempSpider;
}

//Returns Spider
void SpiderPool::ReturnSpider(Spider* b) {
	//BANDAID FIX CAUSE OBJECT WAS PUSHING TO STACK TWICE
	std::stack<Spider*> tmp = recycledSpider;
	while (!tmp.empty()) {
		if (tmp.top() == b) {
			return;
		}
		tmp.pop();
	}
	recycledSpider.push(static_cast<Spider*>(b));
}

//cleans out the pool and also cleans commands
SpiderPool::~SpiderPool() {
	while (!recycledSpider.empty()) {
		recycledSpider.top()->CleanCommands();
		delete recycledSpider.top();
		recycledSpider.pop();
	}
}