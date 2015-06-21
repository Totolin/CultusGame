#include "GameLevel.h"
#include "PauseMenu.h"

GameLevel::GameLevel()
{
}

GameLevel::~GameLevel()
{
}


GameLevel* GameLevel::create(GameLayer* layer)
{
	GameLevel* gameLevel = createWithPhysics();
	gameLevel->getPhysicsWorld()->setGravity(Vect(0.0f, -700.0f));
	gameLevel->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	gameLevel->getPhysicsWorld()->setSpeed(2.0f);
	gameLevel->gameLayer = layer;
	//gameLevel->pauseMenu = menu;
	gameLevel->isPaused = false;
	layer->setTag(LAYER_TAG);
	gameLevel->addChild(layer,100);
	gameLevel->scheduleUpdate();
	gameLevel->initOptions();

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

void GameLevel::resumeButtonCallback()
{
	this->gameLayer->resume();
	this->gameLayer->setOpacity(255);
	this->removeChildByTag(1234,false);
}

// Set initial predefined options for the Player
void GameLevel::initOptions()
{
	// Create keyboard mapping
	auto eventListener = EventListenerKeyboard::create();
	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);

	// Set events on press and release
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
		switch (keyCode){
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			this->escapeButtonCallback();
			break;
		default:
			break;
		}
	};

	// Set listener
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
}

void GameLevel::escapeButtonCallback()
{
	Vector<Node*> children = this->gameLayer->getChildren();
	this->gameLayer->setOpacity(40);
	this->gameLayer->pause();
	for (Node* child : children)
	{
		child->pause();
	}
	//this->gameLayer->pause();

	PauseMenu* newPauseMenu = PauseMenu::create(this);
	newPauseMenu->setTag(1234);
	this->addChild(newPauseMenu,10000);
}
