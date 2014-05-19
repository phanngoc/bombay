#include "Info.h"

USING_NS_CC;
Info::Info()
{

}
void Info::setLabelPoint()
{
	pointlabel  = cocos2d::LabelTTF::create("Point:0", "fonts/FINALOLD.ttf", 16,Size(75, 32), TextHAlignment::LEFT);
	pointlabel->setPosition(5.0f * HelloBom::PTM_RATIO_X,7* HelloBom::PTM_RATIO_Y);
	pointlabel->setColor(ccc3(64,64,64));
	this->addChild(pointlabel);
}
int Info::getPoint()
{
	point = distance + gold * 100;
	return point;
}
void Info::setGold()
{
	gold++;
}
void Info::setHero()
{
	hero--;
}
void Info::update(float real_distance)
{
	if (distance < (int)real_distance)
	{
			distance = (int)real_distance;
	}
	std::string s = StringUtils::toString(getPoint());
	pointlabel->setString("Point:" + s);
}
void Info::reset()
{
	distance = 0;
	gold=0;
	point = 0;
}
