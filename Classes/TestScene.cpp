#include "TestScene.h"
#include "Player.h"
#include "MyBodyParser.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

void TestScene::update(float delta)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	int chance = random(1, 100);
	float yPos = random(0.0f, visibleSize.height);
	if (chance <= 5)
	{
		Sprite* mailbox = Sprite::create("mailbox.png");
		auto spriteBody = PhysicsBody::createBox(mailbox->boundingBox().size, PhysicsMaterial(1.0f, 0.5f, 0.5f));
		mailbox->setPhysicsBody(spriteBody);
		mailbox->setPosition(Point(visibleSize.width + origin.x, yPos + origin.y));
		mailbox->getPhysicsBody()->setVelocity(Vect(-500, 0));
		this->addChild(mailbox);
	}


}

Scene* TestScene::create()
{
	TestScene* scene = TestScene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, -700.0f));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->scheduleUpdate();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	PhysicsBody* edgeBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.1f, 0.0f, 0.5f), 3);
	

	Node* edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);
	

	scene->addChild(edgeNode);



	Player* sprite = Player::create();
	sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));


	/*Sprite* sprite = Sprite::create("testSprite.png");
	sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	MyBodyParser::getInstance()->parseJsonFile("test.json");

	auto spriteBody = MyBodyParser::getInstance()->bodyFormJson(sprite, "Test", PhysicsMaterial(1, 1, 0));

	if (spriteBody != nullptr)
	{
		spriteBody->setDynamic(true);
		sprite->setPhysicsBody(spriteBody);
	}*/

	scene->addChild(sprite);


	return scene;
}

TestScene* TestScene::createWithPhysics()
{
	TestScene *ret = new (std::nothrow) TestScene();
	if (ret && ret->initWithPhysics())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}
