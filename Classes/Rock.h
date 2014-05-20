#ifndef ROCK_H
#define ROCK_H
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "HelloBom.h"
#include "Mario.h"
class HelloBom;
class Mario;
class Rock{
	public:
		
		Rock(b2World *world, HelloBom *hellobom,Mario *mario);
		void addChild();
		void remove(Sprite *da);
		int check();
		void bunchOutSide();
		void update();
		void reset();
		~Rock();
	private:
		b2World *_world;
		HelloBom *hellobom;
		Mario *mario;
		float number = 2;
		float new_screen=0;
		std::vector<Sprite*> da;
		
};
#endif
