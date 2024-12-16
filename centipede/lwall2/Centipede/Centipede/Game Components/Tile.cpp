#include "Tile.h"

//Sets up Sprite and Collision Box
Tile::Tile() {
	SetDrawOrder(-1);
	

	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Mushroom"), 4, 2);
	MainSprite.scale(1, 1);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.SetAnimation(1, 1, false);

	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("Mushroom");
	SetCollider(MainSprite, bitmap);

	
}

//Sets manager and position
void  Tile::Initialize(sf::Vector2f p, MushroomSpawner* myManager) {
	myMushroomSpawner = myManager;

	RegisterCollision<Tile>(*this);

	MainSprite.setPosition(p);

}

//Deletes
void Tile::Destroy() {
	DeregisterCollision<Tile>(*this);
}

//Draws
void Tile::Draw()
{
	WindowManager::Window().draw(MainSprite);
}