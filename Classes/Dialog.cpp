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

	mocaDialog->setOpacity(0);
	moguruDialog->setOpacity(0);
	fyeDialog->setOpacity(0);

	kaiwa = Dictionary::createWithContentsOfFile("kaiwa.xml");

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Dialog::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	

	return true;
}

bool Dialog::shesay(std::string name,int count)
{
	if (count!=0)
	{
		turns = count;
		showing = 1;
		nameNow = name;
	}
	std::string fullname = nameNow + std::to_string(turned);
	
	log("%s", fullname.c_str());
	//std::cout << fullname;
	//std::string str = ((__String *)kaiwa->objectForKey(fullname))->getCString();
	std::string str = ((__String *)Dictionary::createWithContentsOfFile("kaiwa.xml")->objectForKey(fullname))->getCString();

	char whose = str[str.size() - 1];
	str.pop_back();
	text = Label::createWithTTF(str, "fonts/PingFangLight.ttf", 26);
	this->addChild(text, 2);
	text->setPosition(0, -0.3*visibleSize.height);
	switch (whose)
	{
	case '0'://moca
		if (count != 0) { mocaDialog->runAction(FadeTo::create(1.0f, 255)); }
		else
		{
			mocaDialog->setOpacity(255);
			moguruDialog->setOpacity(0);
			fyeDialog->setOpacity(0);
		}
		log("isMoca");
		break;
	case '1'://moguru
		if (count != 0) {moguruDialog->runAction(FadeTo::create(1.0f, 255));}
		else
		{
			mocaDialog->setOpacity(0);
			moguruDialog->setOpacity(255);
			fyeDialog->setOpacity(0);
		}
		log("isMoguru");
		break;
	case '2'://fye
		if (count != 0) { fyeDialog->runAction(FadeTo::create(1.0f, 255)); }
		else
		{
			mocaDialog->setOpacity(0);
			moguruDialog->setOpacity(0);
			fyeDialog->setOpacity(255);
		}
		break;
	}
	
	return true;
}

void Dialog::next()
{
	if (turned<turns)
	{
		turned++;
		text->removeFromParentAndCleanup(1);
		shesay();
	}
	else
	{
		turned = 1;
		turns = 0;
		mocaDialog->setOpacity(0);
		moguruDialog->setOpacity(0);
		fyeDialog->setOpacity(0);
		text->removeFromParentAndCleanup(1);
		showing = 0;
	}
}
