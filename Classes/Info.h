#ifndef INFO_H
#define INFO_H
#include "cocos2d.h"
#include "HelloBom.h"

USING_NS_CC;


class Info :public Layer{
	public:
		Info();
		int getPoint();

		void setLabelPoint();
		void setGold();
		void setHero();
		void setDistance();
		void update(float distance);
		void reset();
	private:
		int point = 0;
		int gold = 0;
		int hero = 3;
		int distance = 0;
		cocos2d::LabelTTF  *pointlabel;

};
#endif
