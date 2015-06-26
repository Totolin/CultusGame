#include "cocos2d.h"
#include "Boss.h"
#include "ParallaxBackground.h"
#include "SimpleAudioEngine.h"
#include "InteractiveObjectFactory.h"
#include <vector>
#include <string>
#include "DummyPlayer.h"

USING_NS_CC;
using namespace std;

class IntermediaryScene : public Scene
{
public:
	enum Type
	{
		CREDITS, MENU, UPGRADES
	};

	static IntermediaryScene* create(Type type);

	void setType(Type type);

	void setCreditsInterval(int framesDelay);
	void addCreditsText(string text);

	void addMenuItem(MenuItem* item);

	bool createMenu();
	bool createCredits();
	bool createUpgrade();

	void setBackground(ParallaxBackground* levelBackground);
	void setPlayer(DummyPlayer* mainCharacter);
	void setMusic(string backgroundMusic);

	void setDuration(int duration);

	virtual void update(float delta) override;

private:
	IntermediaryScene();
	~IntermediaryScene();
	string creditsText;
	Vector<MenuItem*> menuItems;
	
	Menu* menu;
	Label* label;

	Type type;
	int creditsInterval;
	ParallaxBackground* levelBackground;
	DummyPlayer* mainCharacter;
	string music;
	int duration;
};
