#include "Dialog.h"
#include "cocos2d.h"
USING_NS_CC;

bool Dialog::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto mocaDialog = Sprite::create("mocaDialog.png");
	auto moguruDialog= Sprite::create("moguruDialog.png");
	auto fyeDialog = Sprite::create("fyeDialog.png");


	return true;
}
