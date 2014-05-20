#include "MushRoom.h"

MushRoom::MushRoom(b2World *world, HelloBom *helo, Mario *mario) :_world(world), hellobom(helo), mario(mario)
{
	for (int i = 1; i <= number; i++)
	{
		addChild();
	}
	CCLOG("trong contructor xong");
	CCLOG("trong contructor %d", mush[0].direction);
}

void MushRoom::addChild()
{

	Sprite *daeve = Sprite::create("nam.png");
	daeve->setScale(0.5f*HelloBom::PTM_RATIO_X / daeve->getContentSize().width, 0.5f*HelloBom::PTM_RATIO_Y / daeve->getContentSize().height);
	char *name = "ball";
	daeve->setUserData(name);
	daeve->setTag(2);
	daeve->retain();
	hellobom->addChild(daeve, 5);
	float x = rand() % 10;
	float half_screen_width = HelloBom::height_game*HelloBom::PTM_RATIO_Y / 2;

	if (mario->getSprite()->getPosition().y > half_screen_width)
		new_screen = (mario->getSprite()->getPosition().y + half_screen_width) / HelloBom::PTM_RATIO_Y;
	else new_screen = 7.5f;

	daeve->setPosition(x*HelloBom::PTM_RATIO_X, new_screen*HelloBom::PTM_RATIO_Y);
	
	b2PolygonShape box;
	box.SetAsBox(0.25f, 0.25f);
	b2FixtureDef fix;
	fix.density = 1.0f;
	fix.shape = &box;
	fix.friction = 0;
	fix.restitution = 0.0f;
	b2BodyDef bodydef;
	bodydef.type = b2BodyType::b2_dynamicBody;
	bodydef.position.Set(x, new_screen);
	b2Body *daevebody = _world->CreateBody(&bodydef);
	daevebody->CreateFixture(&fix);
	daevebody->SetFixedRotation(true);
	daevebody->SetUserData(daeve);
	int heso = (rand() % 2 == 1 )? 1 : -1;


	combine mus;
	mus.body = daevebody;
	mus.direction = heso;
	mus.sprite = daeve;
	mus.check_move = 1;
	mush.push_back(mus);
	
}
void MushRoom::remove(Sprite *sprite)
{
	b2Body *desbody = NULL;
	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL)
		{
			CCSprite* myActor = (CCSprite*)b->GetUserData();
			if (myActor == sprite)
			{
				log("destroy body");
				desbody = b;
			}
		}
	}
	if (desbody!=NULL) _world->DestroyBody(desbody);
	std::vector<combine>::iterator iter = mush.begin();
	for (int i = 0; i < mush.size(); i++)
	{
		if (mush[i].sprite == sprite)
		{
			mush.erase(mush.begin()+i);
			break;
		}
	}
	hellobom->removeChild(sprite, true);
	addChild();
}
int MushRoom::check()
{
	
	for (int i = 0; i < mush.size(); i++)
	{
		float x = mush[i].sprite->getPosition().x;
		float y = mush[i].sprite->getPosition().y;
		if (new_screen>7.6f)
		{
			if (y < (new_screen - 7.5f)*HelloBom::PTM_RATIO_Y)
			{
				return i;
			}
		}
		else
		{
			if ((x <= 0.35*HelloBom::PTM_RATIO_X&&y < 1 * HelloBom::PTM_RATIO_Y) || (x >= 9.6*HelloBom::PTM_RATIO_X&&y < 1 * HelloBom::PTM_RATIO_Y))
			{
				CCLOG("vao2 x:%f,y:%f", x, y);
				return i;
			}
		}
	}
	return 1000;
}
void MushRoom::bunchOutSide()
{
	for (int i = 0; i < mush.size(); i++)
	{
		float x = mush[i].sprite->getPosition().x;
		float y = mush[i].sprite->getPosition().y;
		if (x <= 0.3f*HelloBom::PTM_RATIO_X)
		{
			mush[i].direction = 1;
		}
		if (x > 9.7f*HelloBom::PTM_RATIO_X)
		{
			mush[i].direction = -1;
		}
	}
}
void MushRoom::update()
{
	if (spri_remove != NULL)
	{
		remove(spri_remove);
		spri_remove = NULL;
	}
	

	float half_screen_width = HelloBom::height_game*HelloBom::PTM_RATIO_Y / 2;
	if (mario->getSprite()->getPosition().y > half_screen_width)
		new_screen = (mario->getSprite()->getPosition().y + half_screen_width) / HelloBom::PTM_RATIO_Y;
	else new_screen = 7.5f;
	int chec = check();
	if (chec != 1000)
	{
		Sprite *sprite = mush[chec].sprite;
		sprite->release();
		remove(sprite);
	}
	bunchOutSide();
	for (int i = 0; i < mush.size(); i++)
	{
		if (mush[i].check_move)
		{
			b2Vec2 vel = mush[i].body->GetLinearVelocity();
			switch (mush[i].direction)
			{
			case 1:  vel.x = 1; break;
			case -1:  vel.x = -1; break;
			}
			mush[i].body->SetLinearVelocity(vel);
		}
	}
	
}
MushRoom::~MushRoom()
{

}
void MushRoom::reset()
{
	for (int i = 0; i < mush.size(); i++)
	{
		_world->DestroyBody(mush[i].body);
		hellobom->removeChild(mush[i].sprite);
	}
	mush.clear();
	for (int i = 1; i <= number; i++)
	{
		addChild();
	}
}

void MushRoom::changeDirection(Sprite *sprite)
{
	for (int i = 0; i < mush.size(); i++)
	{
		if (mush[i].sprite == sprite)
		{
			mush[i].direction *= -1;
		}
	}
}
void MushRoom::setRemove(b2Body *body)
{
	Sprite *sprite = (Sprite*)body->GetUserData();
	body->SetLinearVelocity(b2Vec2(0, 0));
	for (int i = 0; i < mush.size(); i++)
	{
		if (mush[i].sprite == sprite)
		{
			mush[i].check_move = 0;
		}
	}
	//auto action = Sequence::create(CCDelayTime::create(0.5f), CallFunc::create(std::bind(&MushRoom::callbackRemove, this,sprite)), NULL);
	//sprite->runAction(action);
	this->spri_remove = sprite;
	ParticleExplosion *_emitter1 = ParticleExplosion::create();
	_emitter1->retain();
	hellobom->addChild(_emitter1, 10);

	_emitter1->setTexture(Director::getInstance()->getTextureCache()->addImage("fire.png"));
	_emitter1->setStartSize(2);
	_emitter1->setEndSize(1);
	_emitter1->setDuration(0.5);
	_emitter1->setPosition(sprite->getPosition().x, sprite->getPosition().y);
	ccColor4F color;
	color.r = 255;
	color.g = 159;
	color.b = 2;
	color.a = 1;
	_emitter1->setStartColor(color);
	_emitter1->setSpeed(10);
	_emitter1->setLife(0.5);
	_emitter1->setLifeVar(0);
	_emitter1->setAutoRemoveOnFinish(true);
}
void MushRoom::callbackRemove(Sprite *sprite)
{
	this->spri_remove = sprite;
}