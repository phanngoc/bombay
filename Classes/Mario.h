#ifndef MARIO_H
#define MARIO_H

#include "Box2D\Box2D.h"
#include "HelloBom.h"
#include "cocos2d.h"
USING_NS_CC;
class HelloBom;
class Mario{
public:
	Mario(b2World *world,HelloBom *hellobom);
	~Mario();
	void setUpMario();
	Sprite *getSprite();
	b2Body *getBody();
	int getDirection();
	void setDirection(int dic);
	void reset();

private:
		CCSprite *mario;
		b2Body *mariobody;
		b2World *_world;
		HelloBom *hellobom;
		int direction=1;
};
#endif
