#include "IntermediaryScene.h"

IntermediaryScene::IntermediaryScene()
{
}

IntermediaryScene::~IntermediaryScene()
{
}

IntermediaryScene* IntermediaryScene::create(Type type)
{
	IntermediaryScene* intScene = new IntermediaryScene();
	intScene->setType(type);
	intScene->scheduleUpdate();

	return intScene;
}

void IntermediaryScene::setType(Type type)
{
	this->type = type;
}

void IntermediaryScene::setCreditsInterval(int framesDelay)
{
	this->creditsInterval = creditsInterval;
}

void IntermediaryScene::addCreditsText(string text)
{
	this->credits.push_back(text);
}

void IntermediaryScene::addMenuItem(MenuItem* item)
{
	this->menuItems.push_back(item);
}

void IntermediaryScene::setBackground(ParallaxBackground* levelBackground)
{
	this->levelBackground = levelBackground;
	this->addChild(levelBackground);
}

void IntermediaryScene::setPlayer(DummyPlayer* mainCharacter)
{
	this->mainCharacter = mainCharacter;
	this->addChild(mainCharacter);
}

void IntermediaryScene::setMusic(string backgroundMusic)
{
	this->music = backgroundMusic;
}

void IntermediaryScene::setDuration(int duration)
{
	this->duration = duration;
}

void IntermediaryScene::update(float delta)
{
	if (this->type == CREDITS)
	{
		duration--;

		if (duration == 0)
		{
			//TODO Change Scene
		}
	}
}