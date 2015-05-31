#include "UIBar.h"


UIBar* UIBar::create(string name)
{
	UIBar* bar = new UIBar();
	bar->scheduleUpdate();
	bar->initWithFile("heathbarempty.png");
	bar->score = 0;
	bar->fillingBar = LoadingBar::create("healthbarfilling.png");
	bar->fillingBar->setPercent(50);
	bar->fillingBar->setDirection(LoadingBar::Direction::LEFT);
	bar->scoreLabel = Label::createWithTTF("0", "font.ttf", 20);
	bar->scoreLabel->setAnchorPoint(Vec2(1, 0.5));
	bar->nameLabel = Label::createWithTTF(name, "font.ttf", 20);

	bar->addChild(bar->fillingBar,-1);
	bar->addChild(bar->scoreLabel);
	bar->addChild(bar->nameLabel);

	bar->fillingBar->setPosition(Vec2(300,152));
	bar->nameLabel->setPosition(Vec2(70, 151));
	bar->scoreLabel->setPosition(Vec2(460,120));

	return bar;
}

void UIBar::setPercent(float percentage)
{
	fillingBar->setPercent(percentage);
}

void UIBar::addPercent(float percentage)
{
	fillingBar->setPercent(fillingBar->getPercent() + percentage);
}

void UIBar::substractPercent(float percentage)
{
	fillingBar->setPercent(fillingBar->getPercent() - percentage);
}

float UIBar::getPercent()
{
	return fillingBar->getPercent();
}

void UIBar::resetScore()
{
	score = 0;
}

void UIBar::addScore(int score)
{
	this->score += score;
}

int UIBar::getScore()
{
	return score;
}

void UIBar::update(float delta)
{
	this->scoreLabel->setString(to_string(this->score));
}