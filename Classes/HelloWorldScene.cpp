#include "HelloWorldScene.h"
#include "ParallaxBackground.h"
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

	/*SpriteBatchNode* spritebatch = SpriteBatchNode::create("runner.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("runner.plist");
	auto Sprite1 = Sprite::createWithSpriteFrameName("runner0.png");
	Sprite1->setScale(2, 2);
	Sprite1->setPosition(Vec2(200, 200));
	spritebatch->addChild(Sprite1);
	addChild(spritebatch);
	Vector<SpriteFrame*> animFrames(15);

	char str[100] = { 0 };
	for (int i = 0; i <= 7; i++)
	{
		sprintf(str, "runner%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Sprite1->runAction(RepeatForever::create(Animate::create(animation)));

	this->scheduleUpdate();
	return true;*/

	



}

void HelloWorldScene::update(float delta){
}