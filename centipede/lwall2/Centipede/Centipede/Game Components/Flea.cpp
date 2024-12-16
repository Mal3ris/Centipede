#include "Flea.h"
#include "MushroomSpawner.h"
#include "FleaSpawner.h"
#include "FleaFactory.h"
#include "GridConstants.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "CommandScore.h"
#include "CommandSound.h"
#include "GameManager.h"

Flea::Flea()
{
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Flea"), 2, 2);
	MainSprite.SetAnimation(0, 3);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(1, 1);


	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("Flea");
	SetCollider(MainSprite, bitmap);
	speed = 5;

	pSound = SoundManager::GetSoundCommand(SoundManager::SoundEvents::Kill);
	pDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::FleaKilled);
}

void Flea::Initialize(sf::Vector2f p, MushroomSpawner* mushroomGrid, FleaSpawner* fleaSpawner, 
	FleaFactory* myNewFact, float nSpeed, int nFrequency) {
	myMushroomGrid = mushroomGrid;
	myFleaSpawner = fleaSpawner;
	myFact = myNewFact;
	health = 0;
	speed = nSpeed;
	frequency = nFrequency;
	Pos = p;
	posCounter = 0;
	MainSprite.setPosition(Pos);


	RegisterCollision<Flea>(*this);
}

void Flea::Update()
{
	
	Pos.y += speed;

	if (Pos.y > WindowManager::Window().getView().getSize().y) {
		myFleaSpawner->spawnFlea();
		MarkForDestroy();
	}

	posCounter++;
	if (health == 0 && posCounter % (int)(GridConstants::CELLSIZE/speed) == 0) {
		if (rand() % 100 + 1 <= frequency && Pos.y <= WindowManager::Window().getView().getSize().y - (2*GridConstants::CELLSIZE)) {
			myMushroomGrid->spawnMushroomAt(sf::Vector2f(Pos.x-GridConstants::HALFCELLSIZE, Pos.y- GridConstants::HALFCELLSIZE));
		}
		posCounter = 0;
	}
	
	MainSprite.setPosition(Pos);
	MainSprite.Update();
}

void Flea::CleanCommands() {
	delete pSound;
	delete pDeath;
}

void Flea::Destroy()
{
	DeregisterCollision<Flea>( *this );
}

void Flea::Collision(Bullet* other)
{
	health++;
	if (health >= MAXHEALTH) {
		myFleaSpawner->spawnFlea();
		ScoreManager::SendScoreCommand(pDeath);
		myFact->removeSpecific(this);
		SoundManager::SendSoundCommand(pSound);
		GameManager::SpawnExplosion(0, Pos);
		MarkForDestroy();
	}
	else {
		speed *= SPEEDMULT;
	}
}

void Flea::Draw()
{
	WindowManager::Window().draw(MainSprite);
}
