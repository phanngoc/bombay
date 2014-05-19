#ifndef LOSELAYER_H
#define LOSELAYER_H
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "HelloBom.h"
class LabelTTF;
class HelloBom;
class LoseLayer :public Layer{
	public:	
		LoseLayer(HelloBom *hellobom);
		static LoseLayer *init(HelloBom *hellobom);
		void refresh(Object* sender);
		void menu(Object *sender);
	private:
		HelloBom  *hellobom;
};
#endif
