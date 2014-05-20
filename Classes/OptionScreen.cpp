#include "OptionScreen.h"
#include "startLayer.h"
Scene *Option::createScene()
{
	auto screen = Option::create();
	StartLayer *layer_start = StartLayer::createLayer();
	screen->addChild(layer_start);
	return screen;
}