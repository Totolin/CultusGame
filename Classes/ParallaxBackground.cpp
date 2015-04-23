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

	for (int i = 0; i <= 1; i++)
	{
		ParallaxSprite* sprite = ParallaxSprite::create(imageName);
		sprite->setPosition(imagePosition.x + i * width, imagePosition.y);
		sprite->setVelocityFactor(imageVelocity);
		sprite->setScale(width / sprite->getBoundingBox().size.width);
		this->addChild(sprite, zOrder, imageName);
	}
	zOrder++;
}

void ParallaxBackground::update(float delta)
{
	Vector<Node*> sprites = this->getChildren();

	for (int i = 0; i < sprites.size(); i += 2)
	{
		ParallaxSprite* child1 = dynamic_cast<ParallaxSprite*>(sprites.at(i));
		ParallaxSprite* child2 = dynamic_cast<ParallaxSprite*>(sprites.at(i + 1));
		Vec2 position1 = child1->getPosition();
		Vec2 position2 = child2->getPosition();

		float pixelsMoved = DEFAULT_SCROLL_SPEED * delta;

		position1.x -= child1->getVelocityFactor().x * pixelsMoved;
		position2.x -= child2->getVelocityFactor().x * pixelsMoved;

		if (position1.x < 0 - child1->getBoundingBox().size.width / 2)
		{
			position1.x = Director::getInstance()->getWinSize().width / 2;
			position2.x = 3 * Director::getInstance()->getWinSize().width / 2;
		}

		child1->setPosition(position1);
		child2->setPosition(position2);
	}
}

void ParallaxBackground::animate()
{
	int height = Director::getInstance()->getWinSize().height;
	int width = Director::getInstance()->getWinSize().width;
	Vector<Node*> sprites = this->getChildren();

	for (int i = 0; i < sprites.size(); i += 2)
	{
		ParallaxSprite* child1 = dynamic_cast<ParallaxSprite*>(sprites.at(i));
		ParallaxSprite* child2 = dynamic_cast<ParallaxSprite*>(sprites.at(i + 1));

		MoveTo* moveTo11 = MoveTo::create(i + 2, Vec2(-width / 2, height / 2));
		MoveTo* moveTo12 = MoveTo::create(0, Vec2(width / 2, height / 2));
		auto seq1 = Sequence::create(moveTo11, moveTo12, nullptr);

		MoveTo* moveTo21 = MoveTo::create(i + 2, Vec2(width / 2, height / 2));
		MoveTo* moveTo22 = MoveTo::create(0, Vec2(3 * width / 2, height / 2));
		auto seq2 = Sequence::create(moveTo21, moveTo22, nullptr);

		child1->runAction(RepeatForever::create(seq1));
		child2->runAction(RepeatForever::create(seq2));
	}
}