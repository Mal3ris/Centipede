#include "MushroomPool.h"
#include "TEAL\CommonElements.h"
#include "Mushroom.h"

Mushroom* MushroomPool::GetMushroom() {
	Mushroom* tempMushroom;

	if (recycledMushroom.empty()) {
		//ConsoleMsg::WriteLine("Fresh Mushroom");
		tempMushroom = new Mushroom();
	}
	else {
		//ConsoleMsg::WriteLine("Recycled Mushroom");
		tempMushroom = recycledMushroom.top();
		recycledMushroom.pop();

		tempMushroom->RegisterToCurrentScene();
	}

	return tempMushroom;
}

void MushroomPool::ReturnMushroom(Mushroom* b) {
	recycledMushroom.push(static_cast<Mushroom*>(b));
}

MushroomPool::~MushroomPool() {
	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledMushroom.size()) + " Mushrooms");
	while (!recycledMushroom.empty())
	{
		recycledMushroom.top()->CleanCommands();
		delete recycledMushroom.top();
		recycledMushroom.pop();
	}
}