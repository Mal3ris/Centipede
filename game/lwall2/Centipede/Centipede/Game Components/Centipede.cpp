#include "Centipede.h"
#include "MushroomSpawner.h"
#include "CentipedeFactory.h"
#include "Bullet.h"
#include "MoveDownToLeftCentipede.h"
#include "MoveDownToRightCentipede.h"
#include "MoveFSM.h"
#include "CentiBod.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "CommandScore.h"
#include "CommandSound.h"
#include "GameManager.h"

Centipede::Centipede()
{
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("CentipedeHead"), 8, 2);
	MainSprite.SetAnimation(0, 7);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(2, 2);


	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("CentipedeHead");
	SetCollider(MainSprite, bitmap);

	pSound = SoundManager::GetSoundCommand(SoundManager::SoundEvents::Kill);
	pDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::HeadKilled);
}

void Centipede::Initialize(sf::Vector2f p, MushroomSpawner* pMushroomGrid, 
	 bool moveRight, CentipedeFactory* myNewFact) {
	if (moveRight) {
		pCurrState = &MoveFSM::StateMoveDownLeft;
	}
	else {
		pCurrState = &MoveFSM::StateMoveDownRight;
	}
	
	myFact = myNewFact;

	nextBod = nullptr;

	myMushroomGrid = pMushroomGrid;

	Pos = p;
	posCounter = 0;
	pDeathReleased = false;
	MainSprite.setPosition(Pos);

	RegisterCollision<Centipede>(*this);
}

void Centipede::Initialize(sf::Vector2f p, MushroomSpawner* pMushroomGrid,
	int pCount, const MoveStateCentipede* pState, CentipedeFactory* myNewFact) {
	
	pDeathReleased = false;
	pCurrState = pState;

	nextBod = nullptr;
	myFact = myNewFact;

	myMushroomGrid = pMushroomGrid;

	Pos = p;
	posCounter = pCount;

	if (posCounter % 8 == 0) {
		if (nextBod != nullptr) {
			nextBod->setNextState(pCurrState);
		}
		pCurrState = pCurrState->GetNextState(this, myMushroomGrid);
		posCounter = 0;
	}

	MainSprite.setPosition(Pos);
	
	RegisterCollision<Centipede>(*this);
}

void Centipede::CleanCommands() {
	delete pSound;
	delete pDeath;
}


void Centipede::Update()
{
	Pos += pCurrState->GetMoveOffset(posCounter);
	MainSprite.SetAnimation(pCurrState->GetSpriteOffset(posCounter), pCurrState->GetSpriteOffset(posCounter));
	MainSprite.setScale(pCurrState->GetScale(posCounter).x, pCurrState->GetScale(posCounter).y);

	posCounter += 1;

	if (posCounter % 8 == 0) {
		if (nextBod != nullptr) {
			nextBod->setNextState(pCurrState);
		}
		pCurrState = pCurrState->GetNextState(this, myMushroomGrid);
		posCounter = 0;
		
		
	}

	MainSprite.setPosition(Pos);
	MainSprite.Update();

}

void Centipede::setNextBod(CentiBod* next) {
	nextBod = next;
}

void Centipede::Draw()
{
	WindowManager::Window().draw(MainSprite);
}

void Centipede::Destroy()
{
	DeregisterCollision<Centipede>(*this);
}

const MoveStateCentipede* Centipede::getState() {
	return pCurrState;
}

void Centipede::Collision(Bullet* other)
{
	pCurrState->createMushroom(Pos, myMushroomGrid);
	
	if (nextBod != nullptr) {
		nextBod->swapForHead();
	}

	myFact->removeSpecific(this);

	ScoreManager::SendScoreCommand(pDeath);
	pDeathReleased = true;

	SoundManager::SendSoundCommand(pSound);
	GameManager::SpawnExplosion(0, Pos);

	MarkForDestroy();
}

sf::Vector2f Centipede::getPos() { return Pos; }