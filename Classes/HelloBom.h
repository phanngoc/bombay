#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "Box2D\Box2D.h"
#include "cocos2d.h"
#include "Thanh.h"
#include "Mario.h"
#include "Rock.h"
#include "MushRoom.h"
#include "Bullet.h"
#include "LoseLayer.h"
#include "Info.h"
#include "Gold.h"
USING_NS_CC;
class Thanh;
class Mario;
class Rock;
class MushRoom;
class Bullet;
class Info;
class Gold;
class HelloBom : public cocos2d::Layer
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(Object* pSender);

	void update(float dt);

	void updateAll(float dt);

	Mario *getMario();

	Bullet *getBullet();

	b2World *getWorld();

	MushRoom *getMushRoom();

	static void initStatic();

	void callback1(Node *sender);

	void setInfo(Info *info);

	Info *getInfo();
	// implement the "static create()" method manually
	CREATE_FUNC(HelloBom);

	void resetGame();
	void startGame();
	void playGame();
	void pauseGame();

	static float PTM_RATIO_X;
	static float PTM_RATIO_Y;
	static float width_game;
	static float height_game;
private:
	Layer *background;
	b2World *world;
	Point point_start;
	Thanh *thanh;
	Mario *mario;
	Rock *rock;
	MushRoom *mush;
	Bullet *bullet;
	Info *info;
	Gold *gold;
};

#endif // __HELLOWORLD_SCENE_H__
