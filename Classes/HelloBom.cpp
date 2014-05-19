#define COCOS2D_DEBUG 1
#include "HelloBom.h"
#include "BackgroundLayer.h"




float HelloBom::width_game = 10.0f;
float HelloBom::height_game = 7.5f;

float HelloBom::PTM_RATIO_X = 1;
float HelloBom::PTM_RATIO_Y = 1;

void HelloBom::initStatic()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
     PTM_RATIO_X = visibleSize.width / width_game;
	 PTM_RATIO_Y = visibleSize.height / height_game;
}




// on "init" you need to initialize your instance
bool HelloBom::init()
{
	initStatic();
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloBom::menuCloseCallback, this));

	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);


	b2Vec2 gravity;
	gravity.Set(0.0f, -9.8f);
	world = new b2World(gravity);
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);


	b2BodyDef backgroundef;
	backgroundef.position.Set(0, 0);
	b2Body *body = world->CreateBody(&backgroundef);


	b2Vec2 bottomLeft;
	bottomLeft.Set(0, 0);
	b2Vec2 bottomRight;
	bottomRight.Set(width_game, 0);
	b2Vec2 topLeft;
	topLeft.Set(0, height_game*50);
	b2Vec2 topRight;
	topRight.Set(width_game,height_game*50);

	b2EdgeShape bottomshape;
	bottomshape.Set(bottomLeft, bottomRight);
	body->CreateFixture(&bottomshape, 0);
	b2EdgeShape leftshape;
	leftshape.Set(bottomLeft, topLeft);
	body->CreateFixture(&leftshape, 0);
	b2EdgeShape rightshape;
	rightshape.Set(bottomRight, topRight);
	body->CreateFixture(&rightshape, 0);
	startGame();

	return true;
}
b2World *HelloBom::getWorld()
{
	return this->world;
}

void HelloBom::startGame()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	mario = new Mario(world, this);
	thanh = new Thanh(world, this);
	rock = new Rock(world, this, mario);
	mush = new MushRoom(world, this, mario);
	bullet = new Bullet(world, this, mario);
	gold = new Gold(this);
	this->schedule(schedule_selector(HelloBom::update), 1.0f / 60.0f);
	this->schedule(schedule_selector(HelloBom::updateAll), 1.0f / 60.0f);
	this->runAction(Follow::create(mario->getSprite(), Rect(0, 0, visibleSize.width, visibleSize.height * 40)));

}
void HelloBom::playGame()
{
	this->schedule(schedule_selector(HelloBom::update), 1.0f / 60.0f);
	this->schedule(schedule_selector(HelloBom::updateAll), 1.0f / 60.0f);
//	Director::getInstance()->getActionManager()->resumeTargets(this);
}
void HelloBom::pauseGame()
{
	Director::getInstance()->getScheduler()->pauseTarget(this);
}
void HelloBom::resetGame()
{
	mario->reset();
	rock->reset();
	bullet->reset();
	mush->reset();
	gold->reset();
	info->reset();
	Director::getInstance()->getScheduler()->resumeTarget(this);
}


Mario *HelloBom::getMario()
{
	return this->mario;
}
Bullet *HelloBom::getBullet()
{
	return this->bullet;
}
MushRoom *HelloBom::getMushRoom()
{
	return this->mush;
}
void HelloBom::setInfo(Info *info)
{
	this->info = info;
}
Info *HelloBom::getInfo()
{
	return this->info;
}
void HelloBom::updateAll(float dt)
{
	rock->update();
	mush->update();
	bullet->update(dt);
	info->update(mario->getSprite()->getPosition().y);
	gold->update(dt);
}

void HelloBom::update(float dt)
{
	//It is recommended that a fixed time step is used with Box2D for stability
	//of the simulation, however, we are using a variable time step here.
	//You need to make an informed choice, the following URL is useful
	//http://gafferongames.com/game-physics/fix-your-timestep/

	int velocityIterations = 8;
	int positionIterations = 1;

	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	world->Step(dt, velocityIterations, positionIterations);
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL) {
			// Synchronize the AtlasSprites position and rotation with the corresponding body
			CCSprite* myActor = (CCSprite*)b->GetUserData();
			myActor->setPosition(CCPointMake(b->GetPosition().x * PTM_RATIO_X, b->GetPosition().y * PTM_RATIO_Y));
			myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}
void HelloBom::callback1(Node *sender){
	this->removeChild(sender);
}




void HelloBom::menuCloseCallback(Object* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
