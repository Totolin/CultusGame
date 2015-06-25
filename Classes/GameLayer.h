#pragma once

#include "cocos2d.h"
#include "Boss.h"
#include "ParallaxBackground.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
#include "InteractiveObjectFactory.h"
#include <vector>
#include "UIBar.h"
#include "BossBullet.h"

class BossCannon;
USING_NS_CC;
using namespace std;
using namespace ui;

class GameLayer : public Layer
{
public:
	GameLayer();
	~GameLayer();
	Player* getMainCharacter();
	static GameLayer* create();

	void setBoss(Boss* levelBoss);
	void setBackground(ParallaxBackground* levelBackground);
	void setPlayer(Player* mainCharacter);
	void setDistanceToBoss(long long distance);
	void addObjectFactory(InteractiveObjectFactory* objectFactory);
	virtual void update(float delta) override;
	void updateUI();

private:
	bool collisionPlayerBossBulet(Player* player, BossBullet* bossBullet);
	void collisionBulletBossBullet(Bullet* bullet, BossBullet* bossBullet);
	bool collisionBossBulletGround(BossBullet* bossBullet);
	bool onContactBegin(PhysicsContact &contact);

	Boss* levelBoss;
	Player* mainCharacter;
	ParallaxBackground* levelBackground;
	vector<InteractiveObjectFactory*> objectFactories;
	CocosDenshion::SimpleAudioEngine* audioEngine;
	string backgroundMusic;
	long long distance;
	UIBar* statusBar;
	bool bossMode;

	//TODO: Remove this
	std::map < cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point > keys;

	void collisionBulletRocket(Bullet* bullet, InteractiveObject* rocket);
	void collisionBulletMailBox(Bullet* bullet, InteractiveObject* mailbox);
	void collisionBulletEnemyCannon(Bullet* bullet, BossCannon* cannon);
	void collisionMailBoxRocket(InteractiveObject* mailbox, InteractiveObject* rocket);
	void collsionPlayerRocket(Player* player, InteractiveObject* rocket);
	void collsionPlayerSpike(Player* player, InteractiveObject* hole);
	void collisionMailBoxSpike(InteractiveObject* mailbox, InteractiveObject* spike);
	void collisionMailBoxMailBox(InteractiveObject* mailbox1, InteractiveObject* mailbox2);
	void collsionSpikeSpike(InteractiveObject* spike1, InteractiveObject* spike2);
};
