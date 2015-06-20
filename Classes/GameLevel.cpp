#include "GameLevel.h"

GameLevel::GameLevel()
{
}

GameLevel::~GameLevel()
{
}


GameLevel* GameLevel::create(GameLayer* layer, PauseMenu* menu)
{
	GameLevel* gameLevel = createWithPhysics();
	gameLevel->getPhysicsWorld()->setGravity(Vect(0.0f, -700.0f));
	gameLevel->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	gameLevel->getPhysicsWorld()->setSpeed(2.0f);
	gameLevel->gameLayer = layer;
	gameLevel->pauseMenu = menu;
	gameLevel->isPaused = false;
	layer->setTag(LAYER_TAG);
	gameLevel->addChild(layer,100);
	gameLevel->scheduleUpdate();


	return  gameLevel;
}

GameLevel* GameLevel::createWithPhysics()
{
	GameLevel *ret = new (std::nothrow) GameLevel();
	if (ret && ret->initWithPhysics())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}