#include "Player.h"
#define MOVEMENT_PIXELS 15
Player::Player()
{
}

Player::~Player()
{
}

Player* Player::create(string png, string plist)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist + ".plist");

	Player* playerSprite = new Player();

	if (playerSprite->initWithSpriteFrameName(png + "0.png"))
	{
		auto animation = Animation::create();
		for (int i = 0; i <= 7; i++)
		{
			char name[100] = { 0 };
			sprintf(name, "%s%d.png", png.c_str(), i);
			animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName(name));
		}

		animation->setDelayPerUnit(0.1f);
		playerSprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));

		playerSprite->autorelease();
		playerSprite->initOptions();
		playerSprite->setScale(2);
		playerSprite->scheduleUpdate();
		return playerSprite;
	}

	CC_SAFE_DELETE(playerSprite);
	return NULL;
}

void Player::initOptions()
{
	auto eventListener = EventListenerKeyboard::create();
	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);

	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
		if (keys.find(keyCode) == keys.end()){
			keys[keyCode] = std::chrono::high_resolution_clock::now();
		}
		Vec2 loc = event->getCurrentTarget()->getPosition();
		switch (keyCode){
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			this->jump();
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			this->slide();
			break;
		}
	};

	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
		keys.erase(keyCode);
	};




	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
}

void Player::update(float delta)
{
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || isKeyPressed(EventKeyboard::KeyCode::KEY_S))
	{
		this->moveY(-MOVEMENT_PIXELS);
	}

	if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || isKeyPressed(EventKeyboard::KeyCode::KEY_A))
	{
		this->moveX(-MOVEMENT_PIXELS);
	}

	if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || isKeyPressed(EventKeyboard::KeyCode::KEY_D))
	{
		this->moveX(MOVEMENT_PIXELS);
	}
}

bool Player::isKeyPressed(EventKeyboard::KeyCode code) {
	// Check if the key is currently pressed by seeing it it's in the std::map keys
	// In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
	if (keys.find(code) != keys.end())
		return true;
	return false;
}

void Player::moveX(int pixelsToMove)
{
	Vec2 loc = this->getPosition();
	loc.x += pixelsToMove;
	this->setPosition(loc);
}

void Player::moveY(int pixelsToMove)
{
	Vec2 loc = this->getPosition();
	loc.y += pixelsToMove;
	this->setPosition(loc);
}

void Player::jump()
{
	Vec2 currentPosition = this->getPosition();

	auto moveUpFast = MoveBy::create(0.5, Vec2(0,100));
	auto moveUpSlow = MoveBy::create(1, Vec2(0, 100));
	auto moveDownSlow = MoveBy::create(1, Vec2(0, -100));
	auto moveDownFast = MoveBy::create(0.5, Vec2(0, -100));

	//auto seq = Sequence::create(moveUpFast, moveUpSlow, moveDownSlow, moveDownFast, nullptr);
	auto seq = Sequence::create(moveUpFast,moveUpSlow,moveDownSlow,moveDownFast, nullptr);
	this->runAction(seq);

}

void Player::slide()
{
}

std::map < cocos2d::EventKeyboard::KeyCode,
	std::chrono::high_resolution_clock::time_point > Player::keys;