#include "Boss.h"

Boss::Boss()
{
	// unused
}

Boss::~Boss()
{
	// unused
}

void Boss::update(float delta)
{
	
}

void Boss::setState(State state)
{
	this->currentState = state;
}

void Boss::nextState()
{
	this->currentState++;
}

// Move a player on the X axis by a set number of pixels
// @param pixelsToMove - Number of pixels to move
// @return - Bool which states if the key is pressed or not
void Boss::moveX(int pixelsToMove)
{
	Vec2 loc = this->getPosition();
	loc.x += pixelsToMove;
	this->setPosition(loc);
}

// Move a player on the Y axis by a set number of pixels
// @param pixelsToMove - Number of pixels to move
void Boss::moveY(int pixelsToMove)
{
	Vec2 loc = this->getPosition();
	loc.y += pixelsToMove;
	this->setPosition(loc);
}

void Boss::moveIn(Vec2 position)
{
	// must be overridden
}


