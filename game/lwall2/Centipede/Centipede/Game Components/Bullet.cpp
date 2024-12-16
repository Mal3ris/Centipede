#include "Bullet.h"
#include "BulletFactory.h"
#include "SoundManager.h"
#include "CommandSound.h"

BulletFactory* Bullet::pFactory = nullptr;

Bullet::Bullet()
{
	MainSprite = AnimatedSprite(  ResourceManager::GetTexture("Bullet"), 1, 1);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(1, 1);


	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("Bullet");
	SetCollider(MainSprite, bitmap);
	pSound = SoundManager::GetSoundCommand(SoundManager::SoundEvents::Blaster);
}

void Bullet::ClearCommands() {
	delete pSound;
}

void Bullet::Initialize(sf::Vector2f p, BulletFactory* pFactoryNew) {
	pFactory = pFactoryNew;
	Pos = p;
	startPos = p;
	RegisterCollision<Bullet>(*this);

	

	SoundManager::SendSoundCommand(pSound);
}

void Bullet::Update()
{
	
	Pos.y -= SPEED;

	if (Pos.y < 0) {
		
		
		MarkForDestroy();
	}


	MainSprite.setPosition(Pos);
}

sf::Vector2f Bullet::getStartPos() {
	return startPos;
}

void Bullet::Draw()
{
	WindowManager::Window().draw(MainSprite);
}

void Bullet::Destroy()
{
	//HERE WHERE REMOVE
	pFactory->setActiveBullet(false);
	DeregisterCollision<Bullet>( *this );
	
}

void Bullet::Collision( Mushroom *other )
{
	pFactory->removeSpecific(this);
	MarkForDestroy();
}

void Bullet::Collision(Tile* other)
{
	pFactory->removeSpecific(this);
	MarkForDestroy();
}

void Bullet::Collision(Flea* other)
{
	pFactory->removeSpecific(this);
	MarkForDestroy();
}

void Bullet::Collision(CentiBod* other)
{
	pFactory->removeSpecific(this);
	MarkForDestroy();
}

void Bullet::Collision(Centipede* other)
{
	pFactory->removeSpecific(this);
	MarkForDestroy();
}

void Bullet::Collision(Scorpion* other)
{
	pFactory->removeSpecific(this);
	MarkForDestroy();
}

void Bullet::Collision(Spider* other)
{
	pFactory->removeSpecific(this);
	MarkForDestroy();
}