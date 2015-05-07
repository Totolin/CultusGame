#include "GameLevel.h"

GameLevel::GameLevel()
{
}

GameLevel::~GameLevel()
{
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

GameLevel* GameLevel::create()
{
	GameLevel* gameLevel = new GameLevel();
	gameLevel->scheduleUpdate();
	return gameLevel;
}

void GameLevel::update(float delta)
{
	for (int i = 0; i < objectFactories.size(); i++)
	{
		objectFactories.at(i)->createObject();
	}
}