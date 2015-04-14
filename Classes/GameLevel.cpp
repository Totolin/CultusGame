#include "GameLevel.h"

GameLevel::GameLevel()
{
}

GameLevel::~GameLevel()
{
}

Scene* GameLevel::createScene()
{
	// Create empty Scene instance and customize it by adding this level's characteristics
	auto scene = Scene::create();

	// Add level background, with lowest priority on the screen
	scene->addChild(this->levelBackground->createParallaxBackground(), -100);

	return scene;
}

void GameLevel::setBoss(Boss* levelBoss)
{
	this->levelBoss = levelBoss;
}

void GameLevel::setBackground(ParallaxBackground* levelBackground)
{
	this->levelBackground = levelBackground;
}

void GameLevel::setPlayer(Player* mainCharacter)
{
	this->mainCharacter = mainCharacter;
}

void GameLevel::setAudioEngine(CocosDenshion::SimpleAudioEngine* audioEngine)
{
	this->audioEngine = audioEngine;
}

void GameLevel::setMusic(string backgroundMusic)
{
	this->backgroundMusic = backgroundMusic;
}

void GameLevel::addObjectFactory(InteractiveObjectFactory* objectFactory)
{
	this->objectFactories.push_back(objectFactory);
}