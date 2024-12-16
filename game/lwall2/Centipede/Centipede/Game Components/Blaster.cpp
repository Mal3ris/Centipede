#include "Blaster.h"
#include "BulletFactory.h"
#include "MovementStrategy.h"
#include "PlayerManager.h"
#include "SoundManager.h"
#include "GameManager.h"
#include "CommandSound.h"

Blaster::Blaster()
{
	myMovement = nullptr;
	myBulletFactory = nullptr;


	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Blaster"), 1, 1);

	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(1, 1);
	MainSprite.setPosition(Pos);

	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("Blaster");
	SetCollider(MainSprite, bitmap, true);

	SetDrawOrder(1000);

	pSound = SoundManager::GetSoundCommand(SoundManager::SoundEvents::Death);
}

void Blaster::Initialize(BulletFactory* pBulletFactory, MovementStrategy* pStrat) {

	myBulletFactory = pBulletFactory;


	myMovement = pStrat;
	myMovement->SetStrat(PlayerManager::getPlayer().currPat, this);

	Pos = sf::Vector2f(WindowManager::Window().getView().getSize().x / 2.0f, (WindowManager::Window().getView().getSize().y / 2.0f) + 150.0f);
	PrevPos = Pos;

	MainSprite.setPosition(Pos);

	RegisterInput(InputFlags::KeyPressed);
	RegisterCollision<Blaster>(*this);
}


void Blaster::Destroy()
{
	DeregisterInput();
	DeregisterCollision<Blaster>(*this);
}

void Blaster::Update()
{
	PrevPos = Pos;

	myMovement->AffectMove();

	Tools::Clamp<float>(Pos.x, (float)MainSprite.getTextureRect().width / 2, WindowManager::Window().getView().getSize().x - MainSprite.getTextureRect().width / 2);
	Tools::Clamp<float>(Pos.y, PLAYTOP, PLAYBOTTOM);
	MainSprite.setPosition(Pos);
}

void Blaster::MoveUp() {
	Pos.y -= SPEED;
}
void Blaster::MoveDown() {
	Pos.y += SPEED;
}
void Blaster::MoveLeft() {
	Pos.x -= SPEED;
}
void Blaster::MoveRight() {
	Pos.x += SPEED;
}
void Blaster::Fire() {
	
	myBulletFactory->shootBullet(Pos);
}

void Blaster::CleanCommands() {
	delete pSound;
}

void Blaster::Collision(Mushroom *other)
{
	Pos = PrevPos;
	MainSprite.setPosition(PrevPos);

}

void Blaster::Collision(Flea* other)
{
	
	GameManager::SpawnExplosion(1, Pos);
	GameManager::PlayerDeath();

	SoundManager::SendSoundCommand(pSound);
	
	MarkForDestroy();
}

void Blaster::Collision(Centipede* other)
{
	
	GameManager::SpawnExplosion(1, Pos);
	GameManager::PlayerDeath();

	SoundManager::SendSoundCommand(pSound);
	MarkForDestroy();
}

void Blaster::Collision(CentiBod* other)
{
	
	GameManager::SpawnExplosion(1, Pos);
	GameManager::PlayerDeath();

	SoundManager::SendSoundCommand(pSound);

	MarkForDestroy();
}
void Blaster::Collision(Spider* other)
{
	
	GameManager::SpawnExplosion(1, Pos);
	GameManager::PlayerDeath();

	SoundManager::SendSoundCommand(pSound);

	MarkForDestroy();
}

void Blaster::Draw()
{
	WindowManager::Window().draw(MainSprite);
	
}

