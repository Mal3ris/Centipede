#include "ExplosionLarge.h"

ExplosionLarge::ExplosionLarge()
{
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("ExplosionLarge"), 4, 2);
	MainSprite.SetAnimation(0, 0);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(1, 1);

	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("Bullet");
	SetCollider(MainSprite, bitmap);
}


void ExplosionLarge::Initialize(sf::Vector2f p) {
	MainSprite.setPosition(p);
	posCounter = 0;
}

void ExplosionLarge::Update()
{
	MainSprite.SetAnimation(posCounter, posCounter);
	if (posCounter >= ANIMLENGTH) {
		MarkForDestroy();
	}
	posCounter++;

}


void ExplosionLarge::Draw()
{
	WindowManager::Window().draw(MainSprite);
}

void ExplosionLarge::Destroy()
{

}
