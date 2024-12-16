// PlayScreen

#include "TEAL\CommonElements.h"

#include "PlayScreen.h"
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


void PlayScreen::Initialize()
{
	WindowManager::SetBackgroundColor(sf::Color(0, 0, 0, 255));

	PlayerManager::setPlayer(0);

	GameManager::Initialize("gameplay");

	CollisionTestPair<Blaster, Flea>();
	CollisionTestPair<Blaster, Mushroom>();
	CollisionTestPair<Blaster, Centipede>();
	CollisionTestPair<Blaster, CentiBod>();
	CollisionTestPair<Blaster, Spider>();

	CollisionTestPair<Bullet, Mushroom>();
	CollisionTestPair<Bullet, Flea>();
	CollisionTestPair<Bullet, Centipede>();
	CollisionTestPair<Bullet, CentiBod>();
	CollisionTestPair<Bullet, Scorpion>();
	CollisionTestPair<Bullet, Tile>();
	CollisionTestPair<Bullet, Spider>();

	
	CollisionTestPair<Mushroom, Spider>();
	CollisionTestPair<Mushroom, Scorpion>();

}

