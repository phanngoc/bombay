#include "Rock.h"
#include "stdlib.h"
Rock::Rock(b2World *world, HelloBom *helo, Mario *mario) :_world(world), hellobom(helo), mario(mario)
{
	for (int i = 1; i <= number; i++)
	{
		addChild();
	}
}

void Rock::addChild()
{
	
	Sprite *daeve = Sprite::create("Ball.png");
	daeve->setScale(0.5f*HelloBom::PTM_RATIO_X / daeve->getContentSize().width, 0.5f*HelloBom::PTM_RATIO_Y / daeve->getContentSize().height);
	daeve->setTag(1);
	daeve->retain();

	hellobom->addChild(daeve,5);
	float x = rand() % 10 ;
	float half_screen_width = HelloBom::height_game*HelloBom::PTM_RATIO_Y / 2;
	float y;
	if (mario->getSprite()->getPosition().y > half_screen_width)
		y = (mario->getSprite()->getPosition().y + half_screen_width)/HelloBom::PTM_RATIO_Y;
	else y = 7.5f;
	new_screen = y;
	daeve->setPosition(x*HelloBom::PTM_RATIO_X, y*HelloBom::PTM_RATIO_Y);
	da.push_back(daeve);
	b2CircleShape circle;
	circle.m_radius = 0.25f;
	b2FixtureDef fix;
	fix.density = 2.0f;
	fix.shape = &circle;
	fix.friction = 0;
	fix.restitution = 0.5f;
	b2BodyDef bodydef;
	bodydef.type = b2BodyType::b2_dynamicBody;
	bodydef.position.Set(x, y);
	b2Body *daevebody = _world->CreateBody(&bodydef);
	daevebody->CreateFixture(&fix);
	daevebody->SetUserData(daeve);
	int heso = rand() % 2 == 1 ? 1 : -1;
	b2Vec2 vect;
	vect.Set(2 * heso, 0);
	daevebody->SetLinearVelocity(vect);
	daeve->setUserData(daevebody);
}
void Rock::remove(Sprite *sprite)
{
	std::vector<Sprite*>::iterator iter = da.begin();

	da.erase(std::remove(std::begin(da), std::end(da),sprite), std::end(da));
	b2Body *desbody;
	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL)
		{
			CCSprite* myActor = (CCSprite*)b->GetUserData();
			if (myActor == sprite)
			{
				CCLOG("destroy body");
				desbody = b;
			}
		}
	}
	_world->DestroyBody(desbody);
}
int Rock::check()
{
	for (int i = 0; i < da.size(); i++)
	{
		float x = da[i]->getPosition().x;
		float y = da[i]->getPosition().y;
		if (new_screen>7.6f)
		{
			if (y < (new_screen - 7.5f)*HelloBom::PTM_RATIO_Y)
			{
				return i;
			}
		}else 
		{
			if ((x <= 0.35*HelloBom::PTM_RATIO_X&&y < 1 * HelloBom::PTM_RATIO_Y) || (x >= 9.6*HelloBom::PTM_RATIO_X&&y < 1 * HelloBom::PTM_RATIO_Y))
			{
				return i;
			}
		}
	}
	return 1000;
}
void Rock::bunchOutSide()
{
	//CCLOG("data size ne:%d", da.size());
	for (int i = 0; i < da.size(); i++)
	{
		float x = da[i]->getPosition().x;
		float y = da[i]->getPosition().y;
		if (x <= 0.3f*HelloBom::PTM_RATIO_X)
		{
			for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
			{
				if (b->GetUserData() != NULL) {
					if (b->GetUserData() == da[i])
					{
						b2Vec2 vect;
						vect.Set(1, 0);
						b->ApplyLinearImpulse(vect, b->GetWorldCenter(),true);
					}
				}
			}
		}
		if (x > 9.7f*HelloBom::PTM_RATIO_X)
		{
			for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
			{
				if (b->GetUserData() != NULL) {
					if (b->GetUserData() == da[i])
					{
						b2Vec2 vect;
						vect.Set(-1, 0);
						b->ApplyLinearImpulse(vect, b->GetWorldCenter(), true);
					}
				}
			}
		}
	}
}
void Rock::update()
{
	float half_screen_width = HelloBom::height_game*HelloBom::PTM_RATIO_Y / 2;
	if (mario->getSprite()->getPosition().y > half_screen_width)
		new_screen = (mario->getSprite()->getPosition().y + half_screen_width) / HelloBom::PTM_RATIO_Y;
	else new_screen = 7.5f;

	int chec = check();
	if (chec != 1000)
	{
		Sprite *sprite = da[chec];
		sprite->release();
		hellobom->removeChild(sprite,true);
		remove(sprite);
		addChild();
	}
	bunchOutSide();
}
Rock::~Rock()
{

}
void Rock::reset()
{
	for (int i = 0; i < da.size(); i++)
	{
		_world->DestroyBody((b2Body*)da[i]->getUserData());
		hellobom->removeChild(da[i]);
	}
	da.clear();
	for (int i = 1; i <= number; i++)
	{
		addChild();
	}
}