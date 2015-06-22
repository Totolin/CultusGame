#include "PauseMenu.h"
#include "GameLevel.h"


PauseMenu::PauseMenu()
{
}


PauseMenu::~PauseMenu()
{
}

PauseMenu* PauseMenu::create()
{
	// Initialize PauseMenu object
	PauseMenu* pauseMenu = new PauseMenu();

	// Initialize menu items vector
	Vector<MenuItem*> menuItems;

	// Create default menu items
	Label* resumeButtonLabel = Label::createWithTTF("Resume", "font.ttf", 35);
	MenuItem* resumeButton = MenuItemLabel::create(resumeButtonLabel, [&](Ref* sender){pauseMenu->resumeButtonCallback(); });

	Label* mainMenuButtonLabel = Label::createWithTTF("Return to menu", "font.ttf", 35);
	MenuItem* mainMenuButton = MenuItemLabel::create(mainMenuButtonLabel);

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

void PauseMenu::resumeButtonCallback()
{
	GameLevel* gameLevel = dynamic_cast<GameLevel*>(Director::getInstance()->getRunningScene());
	gameLevel->resumeButtonCallback();
}
