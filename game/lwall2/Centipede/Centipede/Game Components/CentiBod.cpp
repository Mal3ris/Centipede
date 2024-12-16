#include "CentiBod.h"
#include "Centipede.h"
#include "MushroomSpawner.h"
#include "Bullet.h"
#include "MoveStateCentipede.h"
#include "MoveLeftAndDownCentipede.h"
#include "MoveRightAndDownCentipede.h"
#include "MoveFSM.h"
#include "CentipedeFactory.h"
#include "CentiBodFactory.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "CommandScore.h"
#include "CommandSound.h"
#include "GameManager.h"

CentiBod::CentiBod()
{
	

	MainSprite = AnimatedSprite(ResourceManager::GetTexture("CentipedeBody"), 8, 2);
	MainSprite.SetAnimation(0, 7);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(2, 2);


	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("CentipedeBody");
	SetCollider(MainSprite, bitmap);

	pSound = SoundManager::GetSoundCommand(SoundManager::SoundEvents::Kill);
	pDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::BodyKilled);
}

void CentiBod::Initialize(sf::Vector2f p, MushroomSpawner* pMushroomGrid, 
	CentipedeFactory* newHeadFact, bool moveRight, CentiBodFactory* newBodyFact) {
	
	pDeathReleased = false;
	myHeadFactory = newHeadFact;
	myBodyFactory = newBodyFact;
	if (moveRight) {
		myCurrState = &MoveFSM::StateMoveRightDown;
		myPrevState = &MoveFSM::StateMoveRightDown;
	}
	else {
		myCurrState = &MoveFSM::StateMoveLeftDown;
		myPrevState = &MoveFSM::StateMoveLeftDown;
	}

	pNextBod = nullptr;
	prevIsHead = false;

	myMushroomGrid = pMushroomGrid;

	Pos = p;
	posCounter = 0;

	MainSprite.setPosition(Pos);


	RegisterCollision<CentiBod>(*this);
}

void CentiBod::setNextState(const MoveStateCentipede* nextState) {

	myPrevState = nextState;
}

void CentiBod::setCurrState(const MoveStateCentipede* nextState) {

	myCurrState = nextState;
}

void CentiBod::setNextBod(CentiBod* next) {
	pNextBod = next;
}

void CentiBod::setPrevBod(CentiBod* prev) {
	pPrevBod = prev;
}

void CentiBod::setPrevHead(Centipede* prev) {
	pPrevHead = prev;
	prevIsHead = true;
}

void CentiBod::Update()
{

	if (posCounter % 8 == 0) {
		
		if (pNextBod != nullptr) {
			pNextBod->setNextState(myCurrState);
			
		}
		myCurrState = myPrevState;
		posCounter = 0;
	}

	Pos += myCurrState->GetMoveOffset(posCounter);
	MainSprite.SetAnimation(myCurrState->GetSpriteOffset(posCounter), myCurrState->GetSpriteOffset(posCounter));
	MainSprite.setScale(myCurrState->GetScale(posCounter).x, myCurrState->GetScale(posCounter).y);

	posCounter += 1;
	

	MainSprite.setPosition(Pos);
	MainSprite.Update();
}

void CentiBod::Draw()
{
	WindowManager::Window().draw(MainSprite);
}

void CentiBod::Destroy()
{
	DeregisterCollision<CentiBod>(*this);
}

void CentiBod::swapForHead() {
	Centipede* tmpCenti = myHeadFactory->ReplaceCentipede(Pos,
		myMushroomGrid, posCounter, myCurrState);
	if (pNextBod != nullptr) {
		pNextBod->setPrevBod(nullptr);
		pNextBod->setPrevHead(tmpCenti);
		
	}
	tmpCenti->setNextBod(pNextBod);
	myBodyFactory->removeSpecific(this);
	
	MarkForDestroy();
}

void CentiBod::Collision(Bullet* other)
{
	myCurrState->createMushroom(Pos, myMushroomGrid);

	if (prevIsHead == true) {
		pPrevHead->setNextBod(nullptr);
	}
	else {
		pPrevBod->setNextBod(nullptr);
	}

	if (pNextBod != nullptr) {
		pNextBod->swapForHead();
	}

	myBodyFactory->removeSpecific(this);
	ScoreManager::SendScoreCommand(pDeath);

	SoundManager::SendSoundCommand(pSound);
	GameManager::SpawnExplosion(0, Pos);

	pDeathReleased = true;

	MarkForDestroy();
	
}

void CentiBod::CleanCommands() {
	delete pSound;
	delete pDeath;
}

sf::Vector2f CentiBod::getPos() { return Pos; }