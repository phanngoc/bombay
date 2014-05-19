#ifndef GOLD_H
#define GOLD_H
#include "cocos2d.h"
#include "HelloBom.h"
#include "Mario.h"
class HelloBom;
class Mario;
class Gold{
	public:
		Gold(HelloBom *hellobom);
		void update(float dt);
		void start();
		void reset();
	private:
		HelloBom *hellobom;
		Mario *mario;
		std::vector<Sprite*> golds;
};
#endif
