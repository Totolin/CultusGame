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
	bullet->setPosition(X, Y);
	this->bullets.push_back(bullet);

	Director::getInstance()->getRunningScene()->addChild(bullet);
}

void Weapon::update()
{
	if (bullets.size() >= 1)
	{
		float bulletWidth = bullets.at(0)->getBoundingBox().size.width;
		float bulletXpos = bullets.at(0)->getPositionX();
		float screenWidth = Director::getInstance()->getWinSize().width;
		if (bulletXpos - (bulletWidth / 2) >= screenWidth)
		{
			bullets.at(0)->getParent()->removeChild(bullets.at(0));
			bullets.erase(bullets.begin());
		}
	}
}

void Weapon::nextLevel()
{
	this->bulletLevel++;
}