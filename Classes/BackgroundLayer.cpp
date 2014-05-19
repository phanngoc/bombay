#include "BackgroundLayer.h"


bool Background::init()
{

	if (!Layer::init())
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("backgroundJungle.jpg");
	background->setAnchorPoint(Point(0, 0));
	background->setScaleX(visibleSize.width / background->getContentSize().width);
	background->setScaleY(visibleSize.height / background->getContentSize().height);
	this->addChild(background, 0);
	return true;
}
