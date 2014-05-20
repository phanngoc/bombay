#include "Gold.h"
#include "lib/KompexSQLiteDatabase.h"
#include "lib/KompexSQLiteException.h"
#include "lib/KompexSQLiteStatement.h"
#include <iostream>   
#include <fstream>  
#include "ConfigManager.h"



Gold::Gold(HelloBom *hellobom) :hellobom(hellobom)
{
	FileUtils* fileUtils = FileUtils::getInstance();
	ssize_t size = 5;
	unsigned char* smth;
	smth = fileUtils->getFileData("posgold.db", "r", &size);
	fflush(stdout);
	std::string path = fileUtils->getWritablePath();
	path += "gold.db";
	log("path ne:%s", path);
	std::fstream ofs;
	ofs.open(path, std::fstream::out);
	ofs.write((const char*)smth, size - 1);
	ofs.close();
	start();
	mario = hellobom->getMario();
}
void Gold::start()
{
	FileUtils* fileUtils = FileUtils::getInstance();
	std::string path = fileUtils->getWritablePath();
	path += "gold.db";
	Kompex::SQLiteDatabase *pDatabase = new Kompex::SQLiteDatabase(path, SQLITE_OPEN_READWRITE, 0);
	// create statement instance for sql queries/statements
	Kompex::SQLiteStatement *pStmt = new Kompex::SQLiteStatement(pDatabase);
	pStmt->Sql("select * from gold");
	// process all results
	float PT_X = Config::init()->getPTM().width;
	float PT_Y = Config::init()->getPTM().height;
	while (pStmt->FetchRow())
	{
		Sprite *gold = Sprite::create("gold.png");
		gold->setScale(0.5*PT_X / gold->getContentSize().width, 0.5*PT_Y / gold->getContentSize().height);
		gold->setPosition(pStmt->GetColumnInt(1)*PT_X, pStmt->GetColumnInt(2)*PT_Y);
		golds.push_back(gold);
		hellobom->addChild(gold, 1);
	}
	// do not forget to clean-up
	pStmt->FreeQuery();
}
void Gold::update(float dt)
{
	float PT_X = Config::init()->getPTM().width;
	float PT_Y = Config::init()->getPTM().height;
	//Rect rect =  Rect::Rect(mario->getSprite()->getPosition().x, mario->getSprite()->getPosition().y, 0.5*PT_X, 0.5*PT_Y);
	for (int i = 0; i < golds.size(); i++)
	{
		float distance_x = abs(golds[i]->getPosition().x - mario->getSprite()->getPosition().x);
		float distance_y = abs(golds[i]->getPosition().y - mario->getSprite()->getPosition().y);
		float radi_x = 0.5*PT_X;
		float radi_y = 0.5*PT_Y;
		if (distance_x <= radi_x&&distance_y <= radi_y)
		{
			hellobom->removeChild(golds[i]);
			hellobom->getInfo()->setGold();
			golds.erase(golds.begin() + i);
			break;
		}
	}

}
void Gold::reset()
{
	for (int i = 0; i < golds.size(); i++)
	{
		hellobom->removeChild(golds[i]);
	}
	golds.clear();
	start();
}