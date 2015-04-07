# CultusGame
Game designed using Cocos2d framework

GameLevel
   Methods:
	GameLevel();
	~GameLevel();
	addBoss(Boss levelBoss);
	addBackground(ParallaxBackground background);
	addPlayer(Player player);
	addStartScore(int startScore);
	addLifebar(LifeBar life);
	addLifeValue(int value);
	addMusic( ? );
	addInteractiveObjectFactories(vector<InteractiveObjectFactory> objects)

   Members:
	vector<InteractiveObjects> objectsOnScreen;
	Boss levelBoss;
	Player levelPlayer;
	

InteractiveObject
...


InteractiveObjectFactory
   Members:
	int randomChance;
	int loweBoundIntervalPosition;
	int upperBoundIntervalPosition;
	int speed;
	Sprite* sprite;
	bool chanceValidation;
	Direction direction;

   Methods:
        bool getChanceValidation();
	InteractiveObject* createObject();
	

	
enum Direction
	LEFT, STATIC, RIGHT;
