#include "ExplosionSmall.h"

ExplosionSmall::ExplosionSmall()
{
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("ExplosionSmall"), 3, 2);
	MainSprite.SetAnimation(0, 0);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(2, 2);

	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("Bullet");
	SetCollider(MainSprite, bitmap);
}


void ExplosionSmall::Initialize(sf::Vector2f p) {
	MainSprite.setPosition(p);
	posCounter = 0;
}

void ExplosionSmall::Update()
{
	MainSprite.SetAnimation(posCounter, posCounter);
	if (posCounter >= ANIMLENGTH) {
		MarkForDestroy();
	}
	posCounter++;
	
}


void ExplosionSmall::Draw()
{
	WindowManager::Window().draw(MainSprite);
}

void ExplosionSmall::Destroy()
{

}
