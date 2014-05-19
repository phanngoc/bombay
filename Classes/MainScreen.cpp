#include "MainScreen.h"
#include "HelloBom.h"
#include "BackgroundLayer.h"
#include "ControlLayer.h"
#include "info.h"
Scene *MainScreen::createScene()
{
	auto scene = Scene::create();
	/*Tao layer background*/

	auto background = Background::create();
	scene->addChild(background, 0);

	
	/*Tao layer sprite*/
	Info *info = new Info;
	auto layer = HelloBom::create();
	layer->setInfo(info);
	scene->addChild(layer, 2);
	/*Tao layer control*/
	
	auto control = new ControlLayer;
	control->init(layer);
	control->retain();
	scene->addChild(control, 3);
	/*Tao layer info*/

	info->setLabelPoint();
	scene->addChild(info, 10);
	

	return scene;
}
