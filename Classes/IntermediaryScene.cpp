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
	this->creditsText = text;
}

void IntermediaryScene::addMenuItem(MenuItem* item)
{
	this->menuItems.pushBack(item);
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

bool IntermediaryScene::createMenu()
{
	if (this->type == Type::CREDITS) { return false; }

	float width = Director::getInstance()->getWinSize().width;
	float height = Director::getInstance()->getWinSize().height;
	Vec2 menuPosition(width / 2, height / 1.3);

	this->menu = Menu::createWithArray(menuItems);
	this->menu->setPosition(menuPosition);
	this->menu->alignItemsHorizontallyWithPadding(50);
	this->addChild(menu);
	return true;
}

bool IntermediaryScene::createCredits()
{
	this->label = Label::createWithTTF("0", "font.ttf", 20);
	this->label->setDimensions(Director::getInstance()->getWinSize().width - 200, Director::getInstance()->getWinSize().height * 3);

	return true;
}

bool IntermediaryScene::createUpgrade()
{
	return false;
}
