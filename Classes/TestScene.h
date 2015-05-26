#pragma once

#include "cocos2d.h"


USING_NS_CC;
using namespace std;

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();
	static Scene* create();

   static TestScene* createWithPhysics();
	 
	virtual void update(float delta) override;
};