#include "Bullet.h"

Bullet::Bullet(b2World *world, HelloBom *hellobom, Mario *mario) :_world(world), hellobom(hellobom), mario(mario)
{
 //sd 
}
void Bullet::fire()
{
	float x_start = mario->getSprite()->getPosition().x;
	float y_start = mario->getSprite()->getPosition().y;
	auto but = Sprite::create("fire.png");
	but->setScale(0.25f*HelloBom::PTM_RATIO_X / but->getContentSize().width, 0.25f*HelloBom::PTM_RATIO_Y / but->getContentSize().height);
	but->setPosition(x_start + mario->getDirection()*0.25f*HelloBom::PTM_RATIO_X, y_start);
	but->setTag(3);
	but->retain();
	hellobom->addChild(but, 5);
	b2BodyDef bodydef;
	bodydef.position.Set(x_start/HelloBom::PTM_RATIO_X + mario->getDirection()*0.25f, y_start/HelloBom::PTM_RATIO_Y);
	bodydef.type = b2BodyType::b2_dynamicBody;
	b2Body *body = _world->CreateBody(&bodydef);
	b2CircleShape shape;
	shape.m_radius = 0.25f;
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 0.0f;
	body->CreateFixture(&fixture);
	body->SetUserData(but);
	bull com;
	com.sprite = but;
	com.direction = mario->getDirection();
	com.body = body;
	com.x_start = x_start / HelloBom::PTM_RATIO_X;
	com.y_start = y_start / HelloBom::PTM_RATIO_Y;
	bullets.push_back(com);
}
void Bullet::update(float dt)
{
	float half_screen_width = HelloBom::height_game*HelloBom::PTM_RATIO_Y / 2;
	if (mario->getSprite()->getPosition().y > half_screen_width)
		new_screen = (mario->getSprite()->getPosition().y + half_screen_width) / HelloBom::PTM_RATIO_Y;
	else new_screen = 7.5f;

	float pos_destroy = 100;
	for (int i = 0; i < bullets.size(); i++)
	{
		float x_new = bullets[i].x_start + bullets[i].direction * dt * 2;
		bullets[i].x_start = x_new;
		float y_new = 0.375f*sin(x_new * 3) + bullets[i].y_start;
		float x = x_new*HelloBom::PTM_RATIO_X;
		float y = y_new*HelloBom::PTM_RATIO_Y;
		bullets[i].sprite->setPosition(x,y);
		b2Vec2 vect;
		vect.Set(x_new, y_new);
		bullets[i].body->SetTransform(vect,0);

		/*check xem thu dan da ra ngoai chua,neu ra ngoai thi xoa khoi man hinh va mang bullets */
		if (x_new>HelloBom::width_game || x_new<0 || y_new>new_screen)
		{
			pos_destroy = i;
		}
	}
	if (pos_destroy != 100)
	{
		bullets[pos_destroy].sprite->release();
		hellobom->removeChild(bullets[pos_destroy].sprite);
		_world->DestroyBody(bullets[pos_destroy].body);
		bullets.erase(bullets.begin() + pos_destroy);
	}
}
void Bullet::reset()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		_world->DestroyBody(bullets[i].body);
		hellobom->removeChild(bullets[i].sprite);
	}
	bullets.clear();
}