#include "Scorpion.h"
#include "MushroomSpawner.h"
#include "ScorpionSpawner.h"
#include "ScorpionFactory.h"
#include "GridConstants.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "CommandScore.h"
#include "CommandSoundLoop.h"
#include "GameManager.h"

//Constructor Getting Command and Setting up Sprite
Scorpion::Scorpion()
{
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Scorpion"), 4, 1);
	MainSprite.SetAnimation(0, 3);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	
	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("Scorpion");
	SetCollider(MainSprite, bitmap);

	pDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::ScorpionKilled);
	pSound = SoundManager::GetSoundCommand(SoundManager::SoundEvents::Kill);
}

//Initializer that uses Wave Data
void Scorpion::Initialize(sf::Vector2f p, bool moveRight, float nSpeed, ScorpionFactory* myNewFact, ScorpionSpawner* mySpawn) {
	mySpawner = mySpawn;
	myFact = myNewFact;
	if (moveRight) {
		speed = nSpeed;
		MainSprite.setScale(-1, 1);
	}
	else {
		speed = -nSpeed;
		MainSprite.setScale(1, 1);
	}
	Pos = p;
	MainSprite.setPosition(Pos);

	pDeathReleased = false;
	

	RegisterCollision<Scorpion>(*this);
}

//Update
void Scorpion::Update()
{
	Pos.x += speed;

	//Destroys once Offscreen
	if (Pos.x >= WindowManager::Window().getView().getSize().x + GridConstants::CELLSIZE || Pos.x < -1* GridConstants::CELLSIZE) {
		MarkForDestroy();
	}
	
	MainSprite.setPosition(Pos);
	MainSprite.Update();
}

//Deletes Commands
void Scorpion::CleanCommands() {
	delete pSound;
	delete pDeath;
}

//Scorpion Destroyer that also frees from fact and restarts the timer
void Scorpion::Destroy()
{
	mySpawner->restartAlarm();
	myFact->removeSpecific(this);

	DeregisterCollision<Scorpion>( *this );
}

//Bullet Collision
void Scorpion::Collision(Bullet* other)
{
	ScoreManager::SendScoreCommand(pDeath);

	SoundManager::SendSoundCommand(pSound);
	
	GameManager::SpawnExplosion(0, Pos);
	
	MarkForDestroy();
}

//Draw
void Scorpion::Draw()
{
	WindowManager::Window().draw(MainSprite);
}
