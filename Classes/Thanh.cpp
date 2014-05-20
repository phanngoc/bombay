#include "Thanh.h"



void readFile(const char *fileName, std::vector<std::string> &elems)
{
	std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);

	ssize_t size = 0;
	char* pBuffer = (char*)CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rt", &size);

	std::stringstream ss(pBuffer);
	std::string item;
	while (std::getline(ss, item, '\n')) {
		elems.push_back(item);
	}
}


Thanh::Thanh(b2World *world, HelloBom *bom) 
{
	_world = world;
	hellobom = bom;
	std::vector<std::string> dong;
	readFile("level/data.txt", dong);
	
	while (!dong.empty())
	{

		std::string line = dong.back();
		const char *c = line.c_str();

		char *pch;
		char *c1 = const_cast<char*>(c);
		pch = strtok(c1, ",");
		FetureThanh * thanheve = new FetureThanh();
		int dem = 0;
		while (pch != NULL)
		{
			float so = atof(pch);
			thanheve->set(dem, so);
			dem++;
			pch = strtok(NULL, ",");
		}
		mangthanh.push_back(thanheve);
		dong.pop_back();
	}
	setUpThanh();
}

void Thanh::setUpThanh()
{
	for (int i = 0; i < mangthanh.size(); i++)
	{
		Sprite *spritethanh;
		if (mangthanh[i]->get('w') == 2)
		{
			spritethanh = Sprite::create("thanhmario1.png");
		}
		else if (mangthanh[i]->get('w') == 1)
		{
			spritethanh = Sprite::create("thanhmario1_nua.png");
		}
		spritethanh->setPosition(mangthanh[i]->get('x')*HelloBom::PTM_RATIO_X, mangthanh[i]->get('y')*HelloBom::PTM_RATIO_Y);
		spritethanh->setScale(mangthanh[i]->get('w')*HelloBom::PTM_RATIO_X / spritethanh->getContentSize().width, mangthanh[i]->get('h') *HelloBom::PTM_RATIO_Y / spritethanh->getContentSize().height);
		spritethanh->retain();
		hellobom->addChild(spritethanh,5);
		//Dat body
		b2BodyDef bodydef;
		bodydef.position.Set(mangthanh[i]->get('x'), mangthanh[i]->get('y'));
		b2Body *thanhbody = this->_world->CreateBody(&bodydef);
		b2PolygonShape shape;
		shape.SetAsBox(mangthanh[i]->get('w') / 2, mangthanh[i]->get('h') / 2);
		b2FixtureDef fixture;
		fixture.density = 2.0f;
		fixture.shape = &shape;

		thanhbody->CreateFixture(&fixture);
		thanhbody->SetUserData(spritethanh);
	}
}
