#include "startLayer.h"
#include "MainScreen.h"
#include "ConfigManager.h"
USING_NS_CC;
StartLayer *StartLayer::createLayer()
{
	auto layer = new StartLayer;
	layer->autorelease();
	float PT_X = Config::init()->getPTM().width;
	float PT_Y = Config::init()->getPTM().height;
	Size size = Director::getInstance()->getVisibleSize();
	MenuItem *background_image = MenuItemImage::create("start_background.png", "start_background.png");
	background_image->setScale(size.width / background_image->getContentSize().width, size.height / background_image->getContentSize().height);
	background_image->setPosition(size.width / 2, size.height / 2);
	MenuItem *label_start = MenuItemImage::create("play_start.png", "play_start.png", CC_CALLBACK_1(StartLayer::play, layer));
	label_start->setScale(2 * PT_X / label_start->getContentSize().width, 1.25*PT_Y / label_start->getContentSize().height);
	label_start->setPosition(7.4 * PT_X, 5.33f*PT_Y);
	MenuItem *label_option = MenuItemImage::create("option_start.png", "option_start.png", CC_CALLBACK_1(StartLayer::option, layer));
	label_option->setScale(2 * PT_X / label_option->getContentSize().width, 1.25*PT_Y / label_option->getContentSize().height);
	label_option->setPosition(7.4 * PT_X, 3.625f*PT_Y);
	MenuItem *label_quit = MenuItemImage::create("quit_start.png", "quit_start.png", CC_CALLBACK_0(StartLayer::quit, layer));
	label_quit->setScale(2 * PT_X / label_quit->getContentSize().width, 1.25*PT_Y / label_quit->getContentSize().height);
	label_quit->setPosition(7.4 * PT_X, 2.0f*PT_Y);
	MenuItem *stick_image = MenuItemImage::create("stick_start1.jpg", "stick_start1.jpg");
	stick_image->setScale(3.5 * PT_X / stick_image->getContentSize().width, 3 * PT_Y / stick_image->getContentSize().height);
	stick_image->setPosition(3 * PT_X, 3.75f*PT_Y);
	//stick_image->setRotation(-3.14f /6);
	Menu *pMenu = Menu::create();
	pMenu->addChild(background_image, 0);
	pMenu->addChild(label_start, 1);
	pMenu->addChild(label_option, 1);
	pMenu->addChild(label_quit, 1);
	pMenu->addChild(stick_image, 1);

	pMenu->setAnchorPoint(Point(0, 0));
	pMenu->setPosition(0, 0);
	layer->addChild(pMenu);

	ParticleSnow *_emitter = ParticleSnow::create();
	_emitter->retain();
	layer->addChild(_emitter, 10);

	auto p = _emitter->getPosition();
	_emitter->setPosition(Point(p.x, p.y));
	_emitter->setLife(3);
	_emitter->setLifeVar(1);
	//Image *image = new Image();
	//image->initWithImageFile("snow.png");
	//Texture2D *texture = new Texture2D();
	//texture->initWithImage(image);
	//_emitter->setTextureWithRect(texture,Rect::Rect(0,0,20,20));
	// gravity
	_emitter->setGravity(Point(0, -10));

	// speed of particles
	_emitter->setSpeed(60);
	_emitter->setSpeedVar(20);


	Color4F startColor = _emitter->getStartColor();
	startColor.r = 0.9f;
	startColor.g = 0.9f;
	startColor.b = 0.9f;
	_emitter->setStartColor(startColor);

	Color4F startColorVar = _emitter->getStartColorVar();
	startColorVar.b = 0.1f;
	_emitter->setStartColorVar(startColorVar);

	_emitter->setEmissionRate(8);

	_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("snow.png"));
  
	return layer;
}

void StartLayer::play(Object* sender)
{
	Director::getInstance()->replaceScene(TransitionSlideInT::create(1.0f, MainScreen::createScene()));
	
}
void StartLayer::option(Object* sender)
{

}
void StartLayer::quit()
{
	Director::getInstance()->end();
}