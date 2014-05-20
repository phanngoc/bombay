#include "ControlLayer.h"

class JumpContactListener : public b2ContactListener
{
public:
	JumpContactListener(ControlLayer *control, HelloBom *hellobom) :control(control), hellobom(hellobom)
	{

	}
	void BeginContact(b2Contact* contact) {
		void *fixtureUserData = contact->GetFixtureA()->GetUserData();
		if ((int)fixtureUserData == 3)
		{
			control->jumpContact++;
		}
		fixtureUserData = contact->GetFixtureB()->GetUserData();
		if ((int)fixtureUserData == 3)
		{
			control->jumpContact++;
		}

		b2Body *bodyA = contact->GetFixtureA()->GetBody();
		b2Body *bodyB = contact->GetFixtureB()->GetBody();
		if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL) {
			CCSprite *spriteA = (CCSprite *)bodyA->GetUserData();
			CCSprite *spriteB = (CCSprite *)bodyB->GetUserData();

			   // Sprite A = mario, Sprite B = Block
			if (spriteA->getTag() == 0 && spriteB->getTag() == 1) {
				LoseLayer::init(hellobom);
			}  //Mario dung nam ^-^
			if (spriteA->getTag() == 0 && spriteB->getTag() == 2) {
				LoseLayer::init(hellobom);
			} // da dung nam
			if ((spriteA->getTag() == 1 && spriteB->getTag() == 2) || (spriteA->getTag() == 2 && spriteB->getTag() == 1)) {
				log("Da dung nam");
				hellobom->getMushRoom()->changeDirection(spriteA);
				hellobom->getMushRoom()->changeDirection(spriteB);
			} // nam dung nam
			if (spriteA->getTag() == 2 && spriteB->getTag() == 2) {
				log("Nam dung nam");
				hellobom->getMushRoom()->changeDirection(spriteB);
				hellobom->getMushRoom()->changeDirection(spriteA);
			} // bullet dung nam
			if ((spriteA->getTag() == 3 && spriteB->getTag() == 2) || (spriteA->getTag() == 2 && spriteB->getTag() == 3)) {
				log("bullet dung nam");

				spriteA->getTag() == 3 ? hellobom->getMushRoom()->setRemove(bodyB) : hellobom->getMushRoom()->setRemove(bodyA);
			}
		}

	}



	void EndContact(b2Contact* contact) {
		void *fixtureUserData = contact->GetFixtureA()->GetUserData();
		if ((int)fixtureUserData == 3)
		{
			control->jumpContact--;
		}
		fixtureUserData = contact->GetFixtureB()->GetUserData();
		if ((int)fixtureUserData == 3)
		{
			control->jumpContact--;
		}
	}
private:
	ControlLayer *control;
	HelloBom *hellobom;
};




void ControlLayer::init(HelloBom *hellobom) 
{
	this->hellobom = hellobom;
	this->mario = hellobom->getMario();
	this->bullet = hellobom->getBullet();

	button = Sprite::create("button.png");
	button->setScale(1.5f*HelloBom::PTM_RATIO_X / button->getContentSize().width, 1.5f*HelloBom::PTM_RATIO_Y / button->getContentSize().height);
	button->setPosition(9.0f*HelloBom::PTM_RATIO_X, 5.5f*HelloBom::PTM_RATIO_Y);
	this->addChild(button);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(ControlLayer::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(ControlLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithFixedPriority(touchListener, 1);

	JumpContactListener *jumpcontact = new JumpContactListener(this,hellobom);
	hellobom->getWorld()->SetContactListener(jumpcontact);
}

bool ControlLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	Rect rect = Rect(button->getBoundingBox());
	if (!rect.containsPoint(touch->getLocation()))
	{
		check = 1;
		this->schedule(schedule_selector(ControlLayer::longpress), 1.0f / 60.0f);
		point_start = touch->getLocation();
	}
	else
	{
		check = 0;
		bullet->fire();
	}
	return true;
}

void ControlLayer::longpress(float dt)
{

	int heso = (point_start.x > mario->getSprite()->getPosition().x) ? 1 : -1;
	mario->setDirection(heso);
	if (heso == 1)
	{
		mario->getSprite()->setTexture(TextureCache::getInstance()->addImage("mario/mario_right.png"));
	}
	else if (heso == -1)
	{
		mario->getSprite()->setTexture(TextureCache::getInstance()->addImage("mario/mario_left.png"));
	}
	b2Vec2 vect;
	vect.Set(heso * 5, 1);
	mario->getBody()->ApplyForce(vect, mario->getBody()->GetWorldCenter(), true);
}

void ControlLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (check)
	{
		unschedule(schedule_selector(ControlLayer::longpress));
		Point poin = touch->getLocation();
		if ((poin.y - point_start.y) >= (1.0f*HelloBom::PTM_RATIO_Y) && (jumpContact >= 1))
		{
			int heso = (poin.x >= point_start.x) ? 1 : -1;
			b2Vec2 vect;
			vect.Set(1 * heso, 3.5f);
			mario->getBody()->ApplyLinearImpulse(vect, mario->getBody()->GetWorldCenter(), true);
		}
	}
	
}
