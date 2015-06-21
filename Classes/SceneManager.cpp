#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{

}

SceneManager& SceneManager::getInstance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::addSceneToMainStack(Scene* newScene)
{
	mainStack.pushBack(newScene);
}

void SceneManager::fillStack()
{
	// Get instance of director
	Director* director = Director::getInstance();

	// Empty the stack
	director->popToRootScene();

	// Add scenes to stack
	for (int i = mainStack.size() - 1; i >= 1; i--)
	{
		director->pushScene(mainStack.at(i));
	}

	// Run first scene from mainStack
	director->replaceScene(mainStack.at(0));
}

Vector<Scene*> SceneManager::mainStack;
