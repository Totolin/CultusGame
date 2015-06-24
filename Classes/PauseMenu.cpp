#include "PauseMenu.h"
#include "GameLevel.h"
#include "SceneManager.h"


PauseMenu::PauseMenu()
{
}


PauseMenu::~PauseMenu()
{
}

PauseMenu* PauseMenu::create(MenuType menuType)
{
	if (menuType == PAUSE) {
		// Initialize PauseMenu object
		PauseMenu* pauseMenu = new PauseMenu();

		// Initialize menu items vector
		Vector<MenuItem*> menuItems;

		// Create default menu items
		Label* resumeButtonLabel = Label::createWithTTF("Resume", "font.ttf", 35);
		MenuItem* resumeButton = MenuItemLabel::create(resumeButtonLabel, [&](Ref* sender){pauseMenu->resumeButtonCallback(); });

		Label* mainMenuButtonLabel = Label::createWithTTF("Return to menu", "font.ttf", 35);
		MenuItem* mainMenuButton = MenuItemLabel::create(mainMenuButtonLabel, [&](Ref* sender){Director::getInstance()->replaceScene(SceneManager::getInstance().generateLevel(0)); });

		Label* exitButtonLabel = Label::createWithTTF("Exit", "font.ttf", 35);
		MenuItem* exitButton = MenuItemLabel::create(exitButtonLabel, [&](Ref* sender){Director::getInstance()->end(); });

		menuItems.pushBack(resumeButton);
		menuItems.pushBack(mainMenuButton);
		menuItems.pushBack(exitButton);

		float width = Director::getInstance()->getWinSize().width;
		float height = Director::getInstance()->getWinSize().height;
		Vec2 menuPosition(width / 2, height / 1.3);

		auto menu = Menu::createWithArray(menuItems);
		menu->setPosition(menuPosition);
		menu->alignItemsHorizontallyWithPadding(50);
		pauseMenu->addChild(menu);

		return pauseMenu;
	}
	  
	if (menuType == DEAD) {
		// Initialize PauseMenu object
		PauseMenu* pauseMenu = new PauseMenu();

		// Initialize menu items vector
		Vector<MenuItem*> menuItems;

		// Create default menu items
		Label* mainMenuButtonLabel = Label::createWithTTF("Return to menu", "font.ttf", 35);
		MenuItem* mainMenuButton = MenuItemLabel::create(mainMenuButtonLabel, [&](Ref* sender){Director::getInstance()->replaceScene(SceneManager::getInstance().generateLevel(0)); });

		Label* exitButtonLabel = Label::createWithTTF("Exit", "font.ttf", 35);
		MenuItem* exitButton = MenuItemLabel::create(exitButtonLabel, [&](Ref* sender){Director::getInstance()->end(); });

		menuItems.pushBack(mainMenuButton);
		menuItems.pushBack(exitButton);

		float width = Director::getInstance()->getWinSize().width;
		float height = Director::getInstance()->getWinSize().height;
		Vec2 menuPosition(width / 2, height / 2);

		auto menu = Menu::createWithArray(menuItems);
		menu->setPosition(menuPosition);
		menu->alignItemsHorizontallyWithPadding(50);

		Label* GAMEOVER = Label::createWithTTF("GAME OVER", "font.ttf", 170);
		Vec2 gameOverTextPosition(width / 2, height / 1.3);
		GAMEOVER->setPosition(gameOverTextPosition);

		GameLevel* gameLevel = dynamic_cast<GameLevel*>(Director::getInstance()->getRunningScene());
		int score = gameLevel->getGameLayer()->getMainCharacter()->getScore();
		string lb = "Score: " + to_string(score);
		Label* scoreText = Label::createWithTTF(lb, "font.ttf", 40);
		Vec2 scoreTextPosition(width / 2, height / 1.59);
		scoreText->setPosition(scoreTextPosition);

		pauseMenu->addChild(menu);
		pauseMenu->addChild(GAMEOVER);
		pauseMenu->addChild(scoreText);

		return pauseMenu;
	}
}

void PauseMenu::resumeButtonCallback()
{
	GameLevel* gameLevel = dynamic_cast<GameLevel*>(Director::getInstance()->getRunningScene());
	gameLevel->resumeButtonCallback();
}
