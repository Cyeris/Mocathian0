#include "option.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "MenuLayer.h"
#include "GameLayer.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace ui;

bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	escOn = 0;


	auto menuBG = Sprite::create("optionBG.png");
	this->addChild(menuBG);

	auto resumeGame = MenuItemImage::create(
		"start.png",
		"start.png",
		CC_CALLBACK_1(MenuLayer::menuCloseCallback, this));
	/*auto loadGame = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainScene::loadSave, this));*/


	auto exitGame = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MenuLayer::exitCallback, this));

	exitGame->setPosition(Vec2(0, 0));
	resumeGame->setPosition(Vec2(0, exitGame->getContentSize().height+20));
	/*loadGame->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 200 + closeItem->getContentSize().height));
	startGame->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 200 + closeItem->getContentSize().height + loadGame->getContentSize().height));*/
	auto menu = Menu::create(exitGame, resumeGame, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}
void MenuLayer::menuCloseCallback(Ref* pSender)
{
	showMenu(0, pGameLayer);
}
void MenuLayer::exitCallback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/mainmenu.wav", true);
	Director::getInstance()->popScene();
	
}
void MenuLayer::showMenu(bool show,GameLayer* gL) {
	pGameLayer = gL;

	/*auto showMenu = MoveTo::create(0.05, Vec2(origin.x + 0.5*visibleSize.width, origin.y + 0.5*visibleSize.height));
	auto disMenu = MoveTo::create(0.05, Vec2(origin.x + 0.5*visibleSize.width, origin.y + 1.5*visibleSize.height)); */
	auto showMenu = FadeIn::create(0.2f);
	auto disMenu = FadeOut::create(0.2f);
	if (show) {

		this->runAction(showMenu);
		gL->unscheduleUpdate();
		escOn = 1;
	}
	else
	{
		this->runAction(disMenu);
		gL->scheduleUpdate();
		escOn = 0;
	}
}
