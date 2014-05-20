#include "Mario.h"


Mario::Mario(b2World *world,HelloBom *helo) :hellobom(helo), _world(world)
{
	setUpMario();
}
void Mario::setUpMario()
{
	mario = Sprite::create("mario/mario_right.png");
	mario->setPosition(Point(100, 100));
	mario->setScale(0.5f*HelloBom::PTM_RATIO_X / mario->getContentSize().width, 0.5f*HelloBom::PTM_RATIO_Y / mario->getContentSize().height);
	char *name = "mario";
	mario->setUserData(name);
	mario->retain();
	mario->setTag(0);
	hellobom->addChild(mario,5);
	b2BodyDef bodydef;
	bodydef.type = b2BodyType::b2_dynamicBody;
	bodydef.position.Set(100 / HelloBom::PTM_RATIO_X, 100 / HelloBom::PTM_RATIO_Y);

	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.25f);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 2.0f;
	fixture.friction = 0.7f;
	mariobody = _world->CreateBody(&bodydef);
	mariobody->CreateFixture(&fixture);

	shape.SetAsBox(0.03f, 0.03f, b2Vec2(0, -0.3), 0);
	fixture.isSensor = true;
	b2Fixture *foot = mariobody->CreateFixture(&fixture);
	foot->SetUserData((void*)3);
	mariobody->SetUserData(mario);
	mariobody->SetFixedRotation(true);
}
Sprite *Mario::getSprite(){
	return mario;
}
b2Body *Mario::getBody()
{
	return mariobody;
}
Mario::~Mario()
{
	mario->release();
	delete _world;
	delete hellobom;
}
void Mario::setDirection(int dic)
{
	this->direction = dic;
}
int Mario::getDirection()
{
	return this->direction;
}
void Mario::reset()
{
	mario->setPosition(Point(100, 100));
	b2Vec2 vect;
	vect.Set(100 / HelloBom::PTM_RATIO_X, 100 / HelloBom::PTM_RATIO_Y);
	mariobody->SetTransform(vect, 0);
}