#include "Spider.h"
#include "MushroomSpawner.h"
#include "SpiderSpawner.h"
#include "SpiderFactory.h"
#include "GridConstants.h"
#include "Bullet.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "CommandScore.h"
#include "CommandScoreByDistance.h"
#include "CommandSound.h"
#include "GameManager.h"

//Constructor that Sets up Sprite as well as gets Commands
Spider::Spider()
{
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Spider"), 4, 2);
	MainSprite.SetAnimation(0, 7);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);


	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("Spider");
	SetCollider(MainSprite, bitmap);

	pSound = SoundManager::GetSoundCommand(SoundManager::SoundEvents::Kill);
	pDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::SpiderKilled);
	
}

//Initializes necessary data
void Spider::Initialize(sf::Vector2f p, bool moveRight, float nSpeed, SpiderFactory* myNewFact, SpiderSpawner* mySpawn) {
	myFact = myNewFact;
	mySpawner = mySpawn;
	
	if (moveRight) {
		speed = nSpeed;
		MainSprite.setScale(-2, 2);
	}
	else {
		speed = -nSpeed;
		MainSprite.setScale(2, 2);
	}
	Pos = p;
	MainSprite.setPosition(Pos);

	amountToMove = (int)((rand() % MAXBOUNCE + MINBOUNCE) / speed);
	posCounter = 0;
	moveFlip = false;

	RegisterCollision<Spider>(*this);
}

//Deletes Commands
void Spider::CleanCommands() {
	delete pSound;
	delete pDeath;
}

//Update
void Spider::Update()
{
	if (moving == true && moveFlip == false) {
		Pos.x += speed;
		Pos.y += abs(speed);
	}
	else if (moving == true && moveFlip == true) {
		Pos.x += speed;
		Pos.y -= abs(speed);
	}

	if (bouncing == true && moveFlip == false) {
		Pos.y += abs(speed);
	}
	else if (bouncing == true && moveFlip == true) {
		Pos.y -= abs(speed);
	}

	posCounter++;

	if (posCounter % amountToMove == 0 && moving == true) {
		moveFlip = !moveFlip;
	}
	else if (posCounter % amountToBounce == 0 && bouncing == true) {
		moveFlip = !moveFlip;
	}
	
	if (posCounter % (2 * amountToMove) == 0 && moving == true) {
		if (rand() % 100 <= 50) {
			bouncing = true;
			moving = false;
			amountToBounce = (int)((rand() % MAXBOUNCE + MINBOUNCE)/speed);
		}
		amountToMove = (int)((rand() % MAXBOUNCE + MINBOUNCE)/speed);
		posCounter = 0;
		moveFlip = false;
	}
	else if (posCounter % (2 * amountToBounce) == 0 && bouncing == true) {
		bouncing = false;
		moving = true;
		amountToMove = (int)((rand() % MAXBOUNCE + MINBOUNCE)/speed);
		amountToBounce = (int)((rand() % MAXBOUNCE + MINBOUNCE)/speed);
		posCounter = 0;
		moveFlip = false;
	}

	//Destroys Spider once off screen
	if (Pos.x >= WindowManager::Window().getView().getSize().x + GridConstants::CELLSIZE || Pos.x < -1* GridConstants::CELLSIZE) {
		myFact->removeSpecific(this);
		MarkForDestroy();
	}
	
	MainSprite.setPosition(Pos);
	MainSprite.Update();
}

//Resets the Alarm
void Spider::Destroy()
{
	mySpawner->resetAlarm();

	DeregisterCollision<Spider>( *this );
}

//Gets Distance then sends necessary commands
void Spider::Collision(Bullet* other)
{
	int tmp = static_cast<CommandScoreByDistance*>(pDeath)->CalcDist((int)(other->getStartPos().y - Pos.y));

	ScoreManager::SendScoreCommand(pDeath);
	SoundManager::SendSoundCommand(pSound);
	GameManager::SpawnExplosion(0, Pos);
	GameManager::SpawnExplosion(2, Pos, tmp);

	myFact->removeSpecific(this);

	MarkForDestroy();
}

//Draw
void Spider::Draw()
{
	WindowManager::Window().draw(MainSprite);
}



