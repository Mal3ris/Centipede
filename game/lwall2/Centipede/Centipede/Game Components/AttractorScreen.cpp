#include "TEAL\CommonElements.h"

#include "AttractorScreen.h"
#include "Blaster.h"
#include "Bullet.h"
#include "Mushroom.h"
#include "Flea.h"
#include "Scorpion.h"
#include "Spider.h"
#include "Centipede.h"
#include "CentiBod.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "PlayerManager.h"
#include "GameManager.h"

void AttractorScreen::Initialize()
{
	WindowManager::SetBackgroundColor(sf::Color(0, 0, 0, 255));

	SoundManager::ProcessSounds();

	PlayerManager::setPlayer(2);

	GameManager::Initialize("attractor");

	CollisionTestPair<Bullet, Mushroom>();

	CollisionTestPair<Bullet, Tile>();
	//Disabled cause get stuck
	//CollisionTestPair<Blaster, Mushroom>();
	CollisionTestPair<Bullet, Flea>();
	CollisionTestPair<Blaster, Flea>();
	CollisionTestPair<Bullet, Centipede>();
	CollisionTestPair<Bullet, CentiBod>();
	CollisionTestPair<Bullet, Scorpion>();
	CollisionTestPair<Mushroom, Scorpion>();
	CollisionTestPair<Bullet, Spider>();
	CollisionTestPair<Blaster, Centipede>();
	CollisionTestPair<Blaster, CentiBod>();
	CollisionTestPair<Blaster, Spider>();
	CollisionTestPair<Mushroom, Spider>();

}

void AttractorScreen::Terminate() {
}
