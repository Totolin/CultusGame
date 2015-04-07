#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorldScene::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorldScene::create();
	scene->addChild(layer);
	return scene;
}

bool HelloWorldScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	sprite = Sprite::create("veyron.png");
	sprite->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY());
	this->addChild(sprite, 0);

	this->scheduleUpdate();
	return true;
}

void HelloWorldScene::update(float delta){
	auto position = sprite->getPosition();
	position.x -= 250 * delta;
	if (position.x  < 0 - (sprite->getBoundingBox().size.width / 2))
		position.x = this->getBoundingBox().getMaxX() + sprite->getBoundingBox().size.width / 2;
	sprite->setPosition(position);
}