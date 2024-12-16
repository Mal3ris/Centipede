#include "ExplosionSpider.h"

ExplosionSpider::ExplosionSpider()
{
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("ExplosionSpider"), 1, 3);
	MainSprite.SetAnimation(0, 0);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(2, 2);

	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("Bullet");
	SetCollider(MainSprite, bitmap);
}


void ExplosionSpider::Initialize(sf::Vector2f p, int val) {
	MainSprite.setPosition(p);
	if (val == 300) {
		MainSprite.SetAnimation(0, 0);
	}
	else if (val == 600) {
		MainSprite.SetAnimation(1, 1);
	}
	else if (val == 900) {
		MainSprite.SetAnimation(2, 2);
	}
	else {
		MainSprite.SetAnimation(0, 0);
	}

	SetAlarm(0, WAITTIME);
}

void ExplosionSpider::Alarm0() {
	MarkForDestroy();
}

void ExplosionSpider::Update()
{
}


void ExplosionSpider::Draw()
{
	WindowManager::Window().draw(MainSprite);
}

void ExplosionSpider::Destroy()
{

}
