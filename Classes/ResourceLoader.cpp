#include "ResourceLoader.h"

ResourceLoader::ResourceLoader()
{
}

Vector<SpriteFrame*> ResourceLoader::getAnimation(int key)
{
	return animations.at(key);
}

ResourceLoader& ResourceLoader::getInstance()
{
	static ResourceLoader instance;
	return instance;
}

void ResourceLoader::addAnimation(string animationName, int numberOfFrames, int key)
{
	// Create a frame cache to animate the player using plist
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(animationName + ".plist");
	Vector<SpriteFrame*> frames;
	for (int i = 0; i < numberOfFrames; i++)
	{
		char name[100] = { 0 };
		sprintf(name, "%s%d.png", animationName.c_str(), i);
		frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	animations[key] = frames;
}

std::string ResourceLoader::getBulletFile(int index)
{
	return bulletFiles.at(index);
}

void ResourceLoader::addBulletFile(string bulletFile, int index)
{
	bulletFiles[index] = bulletFile;
}

vector<string> ResourceLoader::bulletFiles(100);

map<int, Vector<SpriteFrame*>> ResourceLoader::animations;