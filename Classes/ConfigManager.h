#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
#include "cocos2d.h"
USING_NS_CC;
class Config :public Object{
	public :
		static Config *init();
		void setPTM(float x, float y);
		Size getPTM();
	private:
		float PT_X;
		float PT_Y;

};

#endif
