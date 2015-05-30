#include "Player.h"
#include "GameValues.h"
#include "ResourceLoader.h"
#include "Bullet.h"
#include "Weapon.h"

// Constructor for the Player class.
// Method unused. Check create() for object creation.
Player::Player()
{
}

// Destructor for the Player class.
Player::~Player()
{
}

void Player::setBossMode(bool b)
{
	this->bossMode = b;
}

// Creates an instance of Player
// @param png - The path to the PNG representation of the sprite
// @param plist - The path to the PLIST representation of the sprite
Player* Player::create()
{
	// Create an instance of Player
	Player* playerSprite = new Player();

	// Reset travelled distance
	playerSprite->setDistanceTravelled(0);

	// Get resource loader instance
	ResourceLoader resLoader = ResourceLoader::getInstance();

	// Get running animation
	Vector<SpriteFrame*> runningAnimation = resLoader.getAnimation(PLAYER_ANIMATION_RUNNING);

	// Generate player movement sprites
	if (playerSprite->initWithSpriteFrame(runningAnimation.at(0)))
	{
		auto animation = Animation::createWithSpriteFrames(runningAnimation);

		// Set delay between frames
		animation->setDelayPerUnit(PLAYER_SPRITE_DELAY_RUNNING);

		//Create running action
		auto runningAction = RepeatForever::create(Animate::create(animation));

		//Set tag for action
		runningAction->setTag(PLAYER_ANIMATION_RUNNING);

		// Run animation forever
		playerSprite->runAction(runningAction);

		// Set properties
		playerSprite->autorelease();
		playerSprite->initOptions();
		playerSprite->setScale(2);
		playerSprite->scheduleUpdate();

		// Add weapon
		Weapon* weapon = Weapon::create();
		playerSprite->setWeapon(weapon);

		//Create physical body
		auto spriteBody = PhysicsBody::createBox(playerSprite->boundingBox().size, PhysicsMaterial(1.0f, 0.5f, 0.5f));
		spriteBody->setAngularVelocityLimit(0.0f);
		spriteBody->setMass(1);
	//	spriteBody->setCategoryBitmask(1);
		spriteBody->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
		spriteBody->setContactTestBitmask(true);
		playerSprite->setPhysicsBody(spriteBody);


		// Return
		return playerSprite;
	}

	CC_SAFE_DELETE(playerSprite);
	return NULL;
}

// Set initial predefined options for the Player
void Player::initOptions()
{
	// Create keyboard mapping
	auto eventListener = EventListenerKeyboard::create();
	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);

	// Set events on press and release
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
		if (keys.find(keyCode) == keys.end()){
			keys[keyCode] = std::chrono::high_resolution_clock::now();
		}
		switch (keyCode){
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			this->callback_WorUp();
			break;
		case EventKeyboard::KeyCode::KEY_W:
			this->callback_WorUp();
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			this->slide();
			break;
		case EventKeyboard::KeyCode::KEY_S:
			this->slide();
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			this->fire();
			break;
		default:
			break;
		}
	};

	// Set mapping
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
		keys.erase(keyCode);
	};

	// Set listener
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
}

void Player::update(float delta)
{
	distanceTravelled++;
	score++;

	if (this->currentAction != Action::RUNNING 
		&& this->getPhysicsBody()->getVelocity().y > -1.0f
		&& this->getPhysicsBody()->getVelocity().y < 1.0f)
	{
		// Get resource loader instance
		ResourceLoader resLoader = ResourceLoader::getInstance();

		// Get running animation
		Vector<SpriteFrame*> runningAnimation = resLoader.getAnimation(PLAYER_ANIMATION_RUNNING);

		auto animation = Animation::createWithSpriteFrames(runningAnimation);
		animation->setDelayPerUnit(PLAYER_SPRITE_DELAY_RUNNING);
		auto runningAction = RepeatForever::create(Animate::create(animation));
		runningAction->setTag(PLAYER_ANIMATION_RUNNING);
		this->runAction(runningAction);

		this->currentAction = Action::RUNNING;
	}

	if ((isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || isKeyPressed(EventKeyboard::KeyCode::KEY_A)) &&(bossMode))
	{
		this->getPhysicsBody()->applyImpulse(Vect(-25, 0));
	}

	if ((isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || isKeyPressed(EventKeyboard::KeyCode::KEY_D)) &&(bossMode))
	{
		this->getPhysicsBody()->applyImpulse(Vect(25, 0));
	}

	// Update it's weapon
	this->weapon->update();
}

// Checks if a key is pressed
// @param code - EventKeyboard code of the respective key
// @return - Bool which states if the key is pressed or not
bool Player::isKeyPressed(EventKeyboard::KeyCode code) {
	if (keys.find(code) != keys.end())
		return true;
	return false;
}

// Move a player on the X axis by a set number of pixels
// @param pixelsToMove - Number of pixels to move
// @return - Bool which states if the key is pressed or not
void Player::moveX(int pixelsToMove)
{
	Vec2 loc = this->getPosition();
	loc.x += pixelsToMove;
	this->setPosition(loc);
}

// Move a player on the Y axis by a set number of pixels
// @param pixelsToMove - Number of pixels to move
void Player::moveY(int pixelsToMove)
{
	Vec2 loc = this->getPosition();
	loc.y += pixelsToMove;
	this->setPosition(loc);
}

void Player::fire()
{
	float bullet_Y = getPosition().y;
	float bullet_X = getPosition().x + getBoundingBox().size.width / 2;
	this->weapon->fireBullet(bullet_X, bullet_Y);
}

// Jump action of the Player
// Creates an animation , smooth jumping, and possibility of double-jumping if
// jump key is pressed during this action.
// Sets action to JUMPING
void Player::jump()
{
	// Set current action to JUMPING
	this->currentAction = Action::JUMPING;

	//Stop running animation and replace the sprite png to the jumping one
	this->getActionManager()->removeActionByTag(PLAYER_ANIMATION_RUNNING, this);

	//TODO: Insert the jumping animation instead of a single frame

	// Get resource loader instance
	ResourceLoader resLoader = ResourceLoader::getInstance();

	// Get running animation
	Vector<SpriteFrame*> runningAnimation = resLoader.getAnimation(PLAYER_ANIMATION_RUNNING);
	this->setDisplayFrame(runningAnimation.at(1));

	//JUMP
	this->getPhysicsBody()->applyImpulse(Vect(0, 500));

}

// DoubleJump action of the Player
// Creates an animation , smooth jumping, and is called when the Jump
// key is pressed during the JUMPING action
// Sets action to DOUBLE_JUMPING
void Player::doubleJump()
{
	// Set action to DOUBLE_JUMPING
	this->currentAction = Action::DOUBLE_JUMPING;

	//JUMP AGAIN
	this->getPhysicsBody()->applyImpulse(Vect(0, 300));
}


void Player::setDistanceTravelled(long long dist)
{
	distanceTravelled = dist;
}

long long Player::getDistanceTravelled()
{
	return distanceTravelled;
}

int Player::getScore()
{
	return score;
}

void Player::setScore(int score)
{
	this->score = score;
}

// Callback of the W / UpArrow keys
// Runs actions according to this key
void Player::callback_WorUp()
{
	// If no action is occurring, and the player is RUNNING , JUMP
	// If JUMP action is occurring, DOUBLE JUMP
	// If DOUBLE JUMP action is occurring, do nothing

	if (this->currentAction == Action::DOUBLE_JUMPING)
	{
		return;
	}

	if (this->currentAction == Action::JUMPING)
	{
		doubleJump();

		return;
	}
	jump();
}

void Player::slide()
{


}

void Player::setWeapon(Weapon* weapon)
{
	this->weapon = weapon;
}

bool Player::onScreenLeft()
{
	float playerWidth = this->getBoundingBox().size.width;
	float screenWidth = Director::getInstance()->getWinSize().width;
	float playerXPos = this->getPositionX();

	if (playerXPos - playerWidth / 2 <= 0)
	{
		return false;
	}

	return true;
}

bool Player::onScreenRight()
{
	float playerWidth = this->getBoundingBox().size.width;
	float screenWidth = Director::getInstance()->getWinSize().width;
	float playerXPos = this->getPositionX();

	if (playerXPos + playerWidth / 2 >= screenWidth)
	{
		return false;
	}

	return true;
}