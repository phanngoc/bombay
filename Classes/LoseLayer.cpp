#include "LoseLayer.h"
#include "OptionScreen.h"
LoseLayer::LoseLayer(HelloBom *hellobom) :hellobom(hellobom)
{
	float PT_X = HelloBom::PTM_RATIO_X;
	float PT_Y = HelloBom::PTM_RATIO_Y;

	MenuItem *refresh = MenuItemImage::create("refresh.png", "refresh.png", CC_CALLBACK_1(LoseLayer::refresh, this));
	refresh->setScale(1.5f*PT_X / refresh->getContentSize().width, 1.5f*PT_Y / refresh->getContentSize().height);
	refresh->setPosition(3.8f*PT_X, 5.2f*PT_Y);

	MenuItem *menu = MenuItemImage::create("menu.png", "menu.png", CC_CALLBACK_1(LoseLayer::menu, this));
	menu->setScale(1.5f*PT_X / menu->getContentSize().width, 1.5f*PT_Y/ menu->getContentSize().height);
	menu->setPosition(6.2f*PT_X,5.2f*PT_Y);
	

	int point = hellobom->getInfo()->getPoint();
	std::string s = StringUtils::toString(point);
	cocos2d::LabelTTF *note = cocos2d::LabelTTF::create("Point:"+s, "fonts/african.ttf", 17, Size(4*PT_X,1.5f*PT_Y), TextHAlignment::CENTER);
	note->setColor(ccc3(64, 64, 64));
	MenuItem *label = MenuItemLabel::create(note);
	label->setPosition(5*PT_X,3.2*PT_Y);
	
	int point_data = UserDefault::getInstance()->getIntegerForKey("point",-1);
		if (point_data < point)
		{
			point_data = point;
			UserDefault::getInstance()->setIntegerForKey("point", point_data);
		}
	std::string s1 = StringUtils::toString(point_data);
	cocos2d::LabelTTF *point_best = cocos2d::LabelTTF::create("Best point:" + s1, "fonts/african.ttf", 17, Size(5 * PT_X, 1.5f*PT_Y), TextHAlignment::CENTER);
	point_best->setColor(ccc3(64, 64, 64));
	MenuItem *best_label = MenuItemLabel::create(point_best);
	best_label->setPosition(5 * PT_X, 2.4*PT_Y);


	MenuItem *ground_menu = MenuItemImage::create("label_lose.png", "label_lose.png");
	ground_menu->setScale(5.3 * PT_X / ground_menu->getContentSize().width, 3.9 * PT_Y / ground_menu->getContentSize().height);
	ground_menu->setPosition(5 * PT_X, 4.2f*PT_Y);
   
	Menu* pMenu = Menu::create(ground_menu, menu, refresh, label, best_label, NULL);
	pMenu->setAnchorPoint(Point(0, 0));
	pMenu->setPosition(0,-pMenu->getContentSize().height);
	this->addChild(pMenu, 1);

	MoveTo *action = MoveTo::create(0.5f, Point(0, 0));
	pMenu->runAction(action);

	CCLayerColor* opalayer = CCLayerColor::create(ccc4(137, 137, 137, 0.8),HelloBom::width_game*PT_X,HelloBom::height_game*PT_Y);
	this->addChild(opalayer, 0);
	hellobom->pauseGame();
	Director::getInstance()->getRunningScene()->addChild(this,10);
}
LoseLayer *LoseLayer::init(HelloBom *hellobom)
{
	auto layer = new LoseLayer(hellobom);
	layer->autorelease();
	return layer;
}
void LoseLayer::refresh(Object* sender)
{
	hellobom->resetGame();
	Director::getInstance()->getRunningScene()->removeChild(this);
	
}
void LoseLayer::menu(Object *sender)
{
	Director::getInstance()->replaceScene(TransitionMoveInB::create(1,Option::createScene()));
}