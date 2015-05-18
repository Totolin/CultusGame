#include "DummyPlayer.h"
#include "GameValues.h"
#include "ResourceLoader.h"
#include "Bullet.h"
#include "Weapon.h"

// Constructor for the DummyPlayer class.
// Method unused. Check create() for object creation.
DummyPlayer::DummyPlayer()
{
}

// Destructor for the DummyPlayer class.
DummyPlayer::~DummyPlayer()
{
}

// Creates an instance of DummyPlayer
// @param png - The path to the PNG representation of the sprite
// @param plist - The path to the PLIST representation of the sprite
DummyPlayer* DummyPlayer::create()
{
	// Create an instance of DummyPlayer
	DummyPlayer* DummyPlayerSprite = new DummyPlayer();

	// Get resource loader instance
	ResourceLoader resLoader = ResourceLoader::getInstance();

	// Get running animation
	Vector<SpriteFrame*> walkingAnimation = resLoader.getAnimation(PLAYER_ANIMATION_WALKING);

	// Generate DummyPlayer movement sprites
	if (DummyPlayerSprite->initWithSpriteFrame(walkingAnimation.at(0)))
	{
		auto animation = Animation::createWithSpriteFrames(walkingAnimation);

		// Set delay between frames
		animation->setDelayPerUnit(PLAYER_SPRITE_DELAY_WALKING);

		//Create walking action
		auto walkingAction = RepeatForever::create(Animate::create(animation));

		//Set tag for action
		walkingAction->setTag(PLAYER_ANIMATION_WALKING);

		// Run animation forever
		DummyPlayerSprite->runAction(walkingAction);

		// Set properties
		DummyPlayerSprite->autorelease();
		DummyPlayerSprite->setScale(2);
		DummyPlayerSprite->scheduleUpdate();

		// Return
		return DummyPlayerSprite;
	}

	CC_SAFE_DELETE(DummyPlayerSprite);
	return NULL;
}

void DummyPlayer::update(float delta)
{
}