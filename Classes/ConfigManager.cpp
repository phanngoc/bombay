#include "ConfigManager.h"
USING_NS_CC;
Config *Config::init()
{
	Config *config = new Config();
	config->autorelease();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float PT_X = visibleSize.width / 10;
	float PT_Y = visibleSize.height / 7.5;
	config->setPTM(PT_X, PT_Y);
	return config;
}
void Config::setPTM(float x, float y)
{
	this->PT_X = x;
	this->PT_Y = y;
}
Size Config::getPTM()
{
	return Size(PT_X,PT_Y);
}