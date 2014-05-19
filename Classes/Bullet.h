#ifndef BULLET_H
#define BULLET_H
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "Mario.h"
#include "HelloBom.h"
class Mario;
class HelloBom;

struct bull{
	b2Body *body;
	int direction;
	float x_start;
	float y_start;
	Sprite *sprite;
};
class Bullet{
	public:
		Bullet(b2World *world, HelloBom *hellobom, Mario *mario);
		void fire();
		void update(float dt);
		void reset();
	private:
		b2World *_world;
		HelloBom *hellobom;
		Mario *mario;
		float number = 2;
		float new_screen = 0;
		std::vector<bull> bullets;

};
#endif
