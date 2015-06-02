#include "Weapon.h"
#include "ResourceLoader.h"
#include "GameValues.h"

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

Weapon* Weapon::create()
{
	// Create an instance of Player
	Weapon* playerWeapon = new Weapon();

	return playerWeapon;
}

void Weapon::fireBullet(float X, float Y)
{
	Bullet* bullet = Bullet::create(bulletLevel);
	bullet->setPosition(X + bullet->getBoundingBox().size.width/2, Y);

	Director::getInstance()->getRunningScene()->addChild(bullet);
}


void Weapon::nextLevel()
{
	this->bulletLevel++;
}