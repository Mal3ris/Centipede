#include "Mushroom.h"
#include "MushroomSpawner.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "CommandSound.h"
#include "CommandScore.h"
#include "GameManager.h"

Mushroom::Mushroom()
{
	health = 0;
	

	MainSprite = AnimatedSprite(  ResourceManager::GetTexture("Mushroom"), 4, 2);

	MainSprite.scale( 1, 1 );
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.SetAnimation(health, health, false);


	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("Mushroom");
	SetCollider(MainSprite, bitmap);

	pSound = SoundManager::GetSoundCommand(SoundManager::SoundEvents::Mushroom);
	pDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::MushroomKilled);
	pRestore = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::MushroomRecover);
}

void Mushroom::Initialize(sf::Vector2f p, MushroomSpawner* myManager) {
	
	isPoison = false;

	Pos = p;
	manager = myManager;
	
	health = 0;

	RegisterCollision<Mushroom>(*this);

	MainSprite.setPosition(Pos);

	MainSprite.SetAnimation(health, health, false);
}

void Mushroom::Update()
{
	MainSprite.Update();
}

void Mushroom::Draw()
{
	WindowManager::Window().draw(MainSprite);
}

void Mushroom::Collision( Bullet *other )
{
	health += 1;
	
	if (health >= 4) {
		
		ScoreManager::SendScoreCommand(pDeath);
		manager->destroyMushroomAt(getPos());
	} else{ 
		if (isPoison) {
			MainSprite.SetAnimation(health+4, health+4, false);
		}
		else {
			MainSprite.SetAnimation(health, health, false);
		}
		
	}
}

void Mushroom::Collision(Scorpion* other)
{
	isPoison = true;
	MainSprite.SetAnimation(health + 4, health + 4, false);
}

void Mushroom::Collision(Spider* other)
{
	manager->destroyMushroomAt(getPos());
}

void Mushroom::CleanCommands() {
	delete pSound;
	delete pDeath;
	delete pRestore;
}

bool Mushroom::getPoison() {
	return isPoison;
}

void Mushroom::reset() {
	if (isPoison == true) {
		ScoreManager::SendScoreCommand(pRestore);
	}
	else if(health > 0) {
		ScoreManager::SendScoreCommand(pRestore);
		
	}

	GameManager::SpawnExplosion(0, Pos);

	health = 0;
	isPoison = 0;
	MainSprite.SetAnimation(health, health, false);

	SoundManager::SendSoundCommand(pSound);
}

sf::Vector2f Mushroom::getPos() {
	return Pos;
}

float Mushroom::getWidth() {
	return (float)MainSprite.getTextureRect().width;
}

float Mushroom::getHeight() {
	return (float)MainSprite.getTextureRect().height;
}

void Mushroom::Alarm0() {
	reset();
}

void Mushroom::Destroy()
{
	isPoison = false;
	DeregisterCollision<Mushroom>( *this );
}