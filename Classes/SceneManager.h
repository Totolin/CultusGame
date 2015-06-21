#pragma once
#include "cocos2d.h"
#include <vector>

USING_NS_CC;
using namespace std;

class SceneManager
{
public:
	static SceneManager& getInstance();
	void addSceneToMainStack(Scene* newScene);
	void fillStack();
private:
	SceneManager();
	~SceneManager();
	static Vector<Scene*> mainStack;
};

