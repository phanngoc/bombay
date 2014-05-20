#ifndef CONTROLLAYER_H
#define CONTROLLAYER_H
#include "cocos2d.h"
#include "Mario.h"
#include "Bullet.h"
#include "HelloBom.h"
class HelloBom;
USING_NS_CC;
class Mario;
class Bullet;
class ControlLayer :public Layer{
	public:
		void init(HelloBom *hellobom);
		bool onTouchBegan(Touch *touch, Event *unused_event);
		void onTouchEnded(Touch *touch, Event *unused_event);
		void longpress(float dt);
		int jumpContact = 0;
	private:
		Mario *mario;
		Bullet *bullet;
		Sprite *button;
		Point point_start;
		HelloBom *hellobom;
		int check;
};
#endif
