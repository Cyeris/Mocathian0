#include "Dialog.h"
#include "cocos2d.h"
#include <string>
#include <iostream>
USING_NS_CC;

bool Dialog::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->setCascadeOpacityEnabled(true);
	turned = 1;
	//showDia = FadeIn::create(0.5f);
	showDia = FadeTo::create(2.0f, 255);
	disDia = FadeOut::create(0.5f);


	mocaDialog = Sprite::create("mocaDialog.png");
	moguruDialog= Sprite::create("moguruDialog.png");
	fyeDialog = Sprite::create("fyeDialog.png");

	this->addChild(mocaDialog);
	this->addChild(moguruDialog);
	this->addChild(fyeDialog);
	mocaDialog->setAnchorPoint(Vec2(0.5, 0));
	moguruDialog->setAnchorPoint(Vec2(0.5, 0));
	fyeDialog->setAnchorPoint(Vec2(0.5, 0));
	mocaDialog->setPosition(0, -0.5*visibleSize.height);
	moguruDialog->setPosition(0, -0.5*visibleSize.height);
	fyeDialog->setPosition(0, -0.5*visibleSize.height);

	mocaDialog->setOpacity(128);
	moguruDialog->setOpacity(0);
	fyeDialog->setOpacity(0);

	/*text = Label::createWithTTF("Your Text", "fonts/PingFangLight.ttf", 24);
	this->addChild(text);*/

	kaiwa = Dictionary::createWithContentsOfFile("kaiwa.xml");

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Dialog::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	

	return true;
}

bool Dialog::shesay(int who, std::string name,int count)
{
	//int length = name.size();
	//log("len=%d", length);

	
	if (!count)
	{
		turns = count;
	}
	std::string fullname = name + std::to_string(turned);
	
	
	//std::cout << fullname;

	//const char * str = ((String *)kaiwa->objectForKey(fullname))->getCString();
	std::string str = ((String *)kaiwa->objectForKey(fullname))->getCString();
	char whose = str[str.size() - 1];
	str.pop_back();
	//log("%c", whose);
	text = Label::createWithTTF(str, "fonts/PingFangLight.ttf", 26);
	this->addChild(text, 2);
	switch (whose)
	{
	case '0'://moca
		//mocaDialog->runAction(showDia);
		log("isMoca");
		break;
	case '1'://moguru
		log("isMoguru");
		break;
	case '2'://fye
		break;
	}
	
	return true;
}
//bool Dialog::shesay(int who, const char* name, int count = 0)
//{
//
//	if (!count)
//	{
//		turns = count;
//
//	}
//	const char * str = ((String *)kaiwa->objectForKey(name))->getCString();
//	text = Label::createWithTTF(str, "fonts/PingFangLight.ttf", 26);
//	this->addChild(text, 2);
//	switch (who)
//	{
//	case 0://moca
//		mocaDialog->runAction(showDia);
//		break;
//	case 1://moguru
//		break;
//	case 2://fye
//		break;
//	}
//
//	return true;
//}

void Dialog::next()
{

	turned++;
}
