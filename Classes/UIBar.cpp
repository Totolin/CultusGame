#include "UIBar.h"


UIBar* UIBar::create(string name)
{
	UIBar* bar = new UIBar();
	bar->initWithFile("heathbarempty.png");
	bar->fillingBar = LoadingBar::create("healthbarfilling.png");
	bar->fillingBar->setPercent(100);
	bar->fillingBar->setDirection(LoadingBar::Direction::LEFT);
	bar->scoreLabel = Label::createWithTTF("0", "font.ttf", 20);
	bar->scoreLabel->setAnchorPoint(Vec2(1, 0.5));
	bar->nameLabel = Label::createWithTTF(name, "font.ttf", 20);
	bar->nameLabel->setAnchorPoint(Vec2(1, 0.5));


	bar->addChild(bar->fillingBar,-1);
	bar->addChild(bar->scoreLabel);
	bar->addChild(bar->nameLabel);

	bar->fillingBar->setPosition(Vec2(300,152));
	bar->nameLabel->setPosition(Vec2(140, 151));
	bar->scoreLabel->setPosition(Vec2(460,120));

	return bar;
}

void UIBar::setPercent(float percentage)
{
	fillingBar->setPercent(percentage);
}


void UIBar::setScore(int score)
{
	this->scoreLabel->setString(to_string(score));
}
