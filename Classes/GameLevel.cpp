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
	this->addChild(levelBackground);
}

void GameLevel::setPlayer(Player* mainCharacter)
{
	this->mainCharacter = mainCharacter;
	this->addChild(mainCharacter);
}

void GameLevel::setDistanceToBoss(long long distance)
{
	this->distance = distance;
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

	Label* scoreLabel = Label::createWithTTF("Score: 0", "font.ttf", 15);
	scoreLabel->setPosition(70, Director::getInstance()->getWinSize().height - 20);
	gameLevel->setScoreLabel(scoreLabel);


	return gameLevel;
}

void GameLevel::update(float delta)
{
	for (int i = 0; i < objectFactories.size(); i++)
	{
		objectFactories.at(i)->createObject();
	}


	if (this->distance == this->mainCharacter->getDistanceTravelled())
	{
		this->levelBackground->slowlyStop();
		this->mainCharacter->setBossMode(true);
	}

	updateScore();
	

}

void GameLevel::updateScore()
{
	int score = mainCharacter->getScore();

	this->scoreLabel->setString("Score: " + to_string(score));
}

void GameLevel::setScoreLabel(Label* label)
{
	this->scoreLabel = label;
	this->addChild(label,100);
}
