#include "ParallaxBackground.h"

ParallaxBackground::ParallaxBackground()
{
	this->background = ParallaxNode::create();
}

ParallaxBackground::~ParallaxBackground()
{
}

void ParallaxBackground::addBackground(string imageName, Vec2 imageRatio, Vec2 imageOffset, Vec2 imagePosition)
{
	Sprite* backgroundSprite = Sprite::create(imageName);
	backgroundSprite->setPosition(imagePosition);
	this->background->addChild(backgroundSprite, currentPositioning++, imageRatio, imageOffset);
}

ParallaxNode* ParallaxBackground::createParallaxBackground()
{
	// 	auto goUp = MoveBy::create(1, Vec2(0, -250));
	// 	auto goDown = goUp->reverse();
	// 	auto go = MoveBy::create(1, Vec2(-500, 0));
	// 	auto goBack = go->reverse();
	// 	auto seq = Sequence::create(goUp, go, goDown, goBack, nullptr);
	auto goRight = MoveTo::create(1, Vec2(500, 500));
	auto goLeft = MoveTo::create(0, Vec2(0, 0));
	auto seq = Sequence::create(goRight, goLeft, nullptr);
	this->background->runAction((RepeatForever::create(seq)));

	return background;
}