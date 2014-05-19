#ifndef _BACKGROUNDLAYER_H
#define _BACKGROUNDLAYER_H
#include "cocos2d.h"
USING_NS_CC;
class Background : public Layer{
	public :
		virtual bool init();
		CREATE_FUNC(Background);
};
#endif
