// CentipedeFactory

#include "TEAL\CommonElements.h"
#include "CentipedeFactory.h"
#include "Centipede.h"
#include <cmath>
#include "CentipedePool.h"
#include "MoveStateCentipede.h"
#include "CommandSound.h"
#include "CommandSoundLoop.h"
#include "SoundManager.h"
#include "GameManager.h"

CentipedePool* CentipedeFactory::myCentipedePool = nullptr;
CommandSound* CentipedeFactory::pSound = nullptr;
std::list<Centipede*> CentipedeFactory::headList;


CentipedeFactory::CentipedeFactory() {
	myCentipedePool = new CentipedePool();
	pSound = SoundManager::GetSoundCommand(SoundManager::SoundEvents::CentipedeLoop);
}

CentipedeFactory::~CentipedeFactory() {
	static_cast<CommandSoundLoop*>(pSound)->PauseSound();
	delete pSound;
	delete myCentipedePool;
}

Centipede* CentipedeFactory::CreateCentipede(sf::Vector2f location, MushroomSpawner* pMG, bool dir) {
	Centipede* tempCentipede = myCentipedePool->GetCentipede();
	tempCentipede->SetExternalManagement(RecycleCentipede);

	tempCentipede->Initialize(location, pMG, dir, this);
	headList.push_back(tempCentipede);

	SoundManager::SendSoundCommand(pSound);
	
	return tempCentipede;
}

Centipede* CentipedeFactory::ReplaceCentipede(sf::Vector2f location, MushroomSpawner* pMG,
	int pCount, const MoveStateCentipede* pState) {
	Centipede* tempCentipede = myCentipedePool->GetCentipede();
	tempCentipede->SetExternalManagement(RecycleCentipede);

	tempCentipede->Initialize(location, pMG, pCount, pState, this);

	headList.push_back(tempCentipede);

	return tempCentipede;
}

void CentipedeFactory::RecycleCentipede(GameObject* b) {
	myCentipedePool->ReturnCentipede(static_cast<Centipede*>(b));
}

void CentipedeFactory::recallAll() {
	while (headList.empty() == false) {
		headList.front()->MarkForDestroy();
		headList.pop_front();
	}
	static_cast<CommandSoundLoop*>(pSound)->PauseSound();
}

void CentipedeFactory::removeSpecific(Centipede* b) {

	headList.erase(std::find(headList.begin(), headList.end(), b));

	if (headList.empty() == true) {
		GameManager::LevelComplete();
		static_cast<CommandSoundLoop*>(pSound)->PauseSound();
	}
}

void CentipedeFactory::Pause() {
	static_cast<CommandSoundLoop*>(pSound)->PauseSound();
}

void CentipedeFactory::Play() {
	if (headList.empty() == false) {
		pSound->Execute();
	}
}