#include "ParallaxBackground.h"
#include "ParallaxSprite.h"
#define DEFAULT_Z_ORDER -100
#define DEFAULT_SCROLL_SPEED 250
ParallaxBackground::ParallaxBackground()
{
	zOrder = DEFAULT_Z_ORDER;
}

void ParallaxBackground::addImage(string imageName, Vec2 imagePosition, Vec2 imageVelocity)
{

	int height = Director::getInstance()->getWinSize().height;
	int width = Director::getInstance()->getWinSize().width;

	ParallaxSprite* sprite = ParallaxSprite::create(imageName);
	sprite->setPosition(imagePosition);
	sprite->setVelocity(imageVelocity);
	sprite->setScale(width/sprite->getBoundingBox().size.width);
	this->addChild(sprite, zOrder, imageName);

	ParallaxSprite* sprite2 = ParallaxSprite::create(imageName);
	sprite2->setPosition(imagePosition.x + width, imagePosition.y);
	sprite2->setVelocity(imageVelocity);
	sprite2->setScale(width / sprite2->getBoundingBox().size.width);
	this->addChild(sprite2, zOrder++, imageName);
}

void ParallaxBackground::update(float delta)
{
	Vector<Node*> sprites  = this->getChildren();


	for (int i = 0; i < sprites.size(); i += 2)
	{
		ParallaxSprite* child1 = dynamic_cast<ParallaxSprite*>(sprites.at(i));
		ParallaxSprite* child2 = dynamic_cast<ParallaxSprite*>(sprites.at(i+1));
		Vec2 position1 = child1->getPosition();
		Vec2 position2 = child2->getPosition();

		if (position1.x < 0 - child1->getBoundingBox().size.width / 2)
		{
			position1.x = Director::getInstance()->getWinSize().width / 2;
			position2.x = 3 * Director::getInstance()->getWinSize().width / 2 ;
		}
		else
		{
			position1.x -= DEFAULT_SCROLL_SPEED * child1->getVelocity().x * delta;
			position2.x -= DEFAULT_SCROLL_SPEED * child2->getVelocity().x * delta;
		}
		child1->setPosition(position1);
		child2->setPosition(position2);

	}



}

void ParallaxBackground::initialize()
{
	this->scheduleUpdate();
}