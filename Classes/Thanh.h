#ifndef THANH_H
#define THANH_H
#include "HelloBom.h"
#include "Box2D\Box2D.h"
#include "cocos2d.h"
USING_NS_CC;
class HelloBom;
class FetureThanh{
private:
	float x, y, w;
	float h = 0.25f;
public:
	FetureThanh()
	{
	}
	FetureThanh(float x, float y, float w) :x(x), y(y), w(w)
	{

	}
	float get(char a)
	{
		if (a == 'x') return x;
		if (a == 'y') return y;
		if (a == 'w') return w;
		if (a == 'h') return h;
	}
	void set(int chiso, float vari)
	{
		switch (chiso)
		{
		case 0: this->x = vari; break;
		case 1: this->y = vari; break;
		case 2: this->w = vari; break;
		}
	}

};




class Thanh{
	private:
		std::vector<FetureThanh*> mangthanh;
		b2World *_world;
		HelloBom *hellobom;
	public :
		Thanh(b2World *world,HelloBom *bom);
		void setUpThanh();


};

#endif
