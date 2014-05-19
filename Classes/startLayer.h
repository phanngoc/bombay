#ifndef STARTLAYER_H
#define STARTLAYER_H
#include "cocos2d.h"
USING_NS_CC;
class StartLayer :public Layer{
	public:
		static StartLayer *createLayer();
		void play(Object* sender);
		void option(Object* sender);
		void quit();

};

#endif
