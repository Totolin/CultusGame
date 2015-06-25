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
	gameLevel->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	gameLevel->getPhysicsWorld()->setSpeed(2.0+ (3* Director::getInstance()->getWinSize().height/4.0)/600.0);
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
	Vector<Node*> children = this->gameLayer->getChildren();
	for (Node* child : children)
	{
		child->resume();
		child->setOpacity(255);
		Vector<Node*> children2 = child->getChildren();
		for (Node* child2 : children2)
		{
			child2->resume();
			child2->setOpacity(255);
		}
	}
	this->removeChildByTag(PAUSE_TAG, false);

	Player* player = dynamic_cast<Player*>(this->gameLayer->getChildByTag(PLAYER_TAG));
	player->resumePlayer();
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
	if (isPaused) { isPaused = false; return resumeButtonCallback(); }
	isPaused = true;

	Vector<Node*> children = this->gameLayer->getChildren();
	this->gameLayer->pause();
	for (Node* child : children)
	{
		child->pause();
		child->setOpacity(40);
		Vector<Node*> children2 = child->getChildren();
		for (Node* child2 : children2)
		{
			child2->pause();
			child2->setOpacity(40);
		}
	}
	
	Player* player = dynamic_cast<Player*>(this->gameLayer->getChildByTag(PLAYER_TAG));
	player->pausePlayer();

	PauseMenu* newPauseMenu = PauseMenu::create(PauseMenu::PAUSE);
	newPauseMenu->setTag(PAUSE_TAG);
	this->addChild(newPauseMenu,900);
}

void GameLevel::gameOver()
{
	if (isPaused) { return; }

	Vector<Node*> children = this->gameLayer->getChildren();
	this->gameLayer->pause();
	for (Node* child : children)
	{
		child->pause();
		child->setOpacity(100);
		Vector<Node*> children2 = child->getChildren();
		for (Node* child2 : children2)
		{
			child2->pause();
			child2->setOpacity(100);
		}
	}

	PauseMenu* newPauseMenu = PauseMenu::create(PauseMenu::DEAD);
	newPauseMenu->setTag(PAUSE_TAG);
	this->addChild(newPauseMenu, 900);
}

GameLayer* GameLevel::getGameLayer()
{
	return gameLayer;
}