#ifndef MUSH_ROOM_H
#define MUSH_ROOM_H
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "HelloBom.h"
#include "Mario.h"
class HelloBom;
class Mario;

struct combine{
	b2Body *body;
	int direction;
	int check_move;
	Sprite *sprite;
};

class MushRoom{
public:

	MushRoom(b2World *world, HelloBom *hellobom, Mario *mario);
	void addChild();
	void remove(Sprite *da);
	int check();
	void bunchOutSide();
	void update();
	void reset();
	void changeDirection(Sprite *sprite);
	void setRemove(b2Body *body);
	void callbackRemove(Sprite *sprite);
	~MushRoom();
private:
	b2World *_world;
	HelloBom *hellobom;
	Mario *mario;
	float number = 2;
	float new_screen = 0;
	std::vector<combine> mush;
	Sprite *spri_remove = NULL;
	

};
#endif
