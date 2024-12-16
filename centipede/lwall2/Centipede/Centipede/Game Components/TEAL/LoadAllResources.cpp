// LoadAllResources.cpp
//
// The user fills the method with all resources that need loading

#include "ResourceManager.h"
#include "../PlayScreen.h"
#include "../AttractorScreen.h"
#include "../HighScoreScreen.h"

void ResourceManager::LoadAllResources()
{
	SetStartScene(new AttractorScreen());

	AddTexture("Blaster", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sprites\\blaster.png");
	AddTexture("Bullet", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sprites\\bullet.png");
	AddTexture("Flea", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sprites\\flea.png");
	AddTexture("Scorpion", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sprites\\scorpion.png");
	AddTexture("Spider", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sprites\\spider.png");
	AddTexture("Mushroom", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sprites\\mushroom.png");
	AddTexture("CentipedeHead", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sprites\\centipede_head.png");
	AddTexture("CentipedeBody", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sprites\\centipede_segment.png");
	AddTexture("Alphabet", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sprites\\FONTwPLAYER.bmp");
	AddTexture("ExplosionSmall", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sprites\\spawn.png");
	AddTexture("ExplosionLarge", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sprites\\death.png");
	AddTexture("ExplosionSpider", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sprites\\spiderscores.png");

	AddSound("Beat", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sounds\\beat.wav");
	AddSound("Bonus", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sounds\\bonus.wav");
	AddSound("Death", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sounds\\death.wav");
	AddSound("Fire", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sounds\\fire1.wav");
	AddSound("Kill", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sounds\\kill.wav");
	AddSound("Scorpion", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sounds\\scorpion_new.wav");
	AddSound("Spider", "\\..\\..\\..\\..\\..\\reference\\Asset\\Sounds\\spiderloop.wav");
}

