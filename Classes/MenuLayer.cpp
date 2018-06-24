#include "option.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "MenuLayer.h"
#include "MainScene.h"
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

	auto exitGame = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MenuLayer::exitCallback, this));

	exitGame->setPosition(Vec2(0, -exitGame->getContentSize().height));
	resumeGame->setPosition(Vec2(0, exitGame->getContentSize().height));
	auto menu = Menu::create(exitGame, resumeGame, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}
void MenuLayer::menuCloseCallback(Ref* pSender)
{
	showMenu(0, pGameLayer,camPos);
}
void MenuLayer::exitCallback(Ref* pSender)
{
	auto userdefault = UserDefault::getInstance();
	userdefault->setFloatForKey("x", mocaPos.x);
	userdefault->setFloatForKey("y", mocaPos.y);
	//log("x:%f", userdefault->getFloatForKey("x"));
	auto scene = MainScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}
void MenuLayer::showMenu(bool show,GameLayer* gL,Vec2 cam) {
	pGameLayer = gL;
	camPos = cam;
	auto showMenu = MoveTo::create(0.05, Vec2(cam.x, cam.y));
	auto disMenu = MoveTo::create(0.05, Vec2(cam.x, cam.y+visibleSize.height));
	/*auto showMenu = FadeIn::create(0.2f);
	auto disMenu = FadeOut::create(0.2f);*/
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

//Scene * MenuLayer::createScene(RenderTexture* sqr)
//{
//	auto scene = Scene::create();
//	MenuLayer *layer = MenuLayer::create();
//	scene->addChild(layer, 1);
//	auto back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
//	back_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //放置位置,这个相对于中心位置。  
//	back_spr->setFlipY(true);            //翻转，因为UI坐标和OpenGL坐标不同  
//	back_spr->setColor(Color3B::GRAY); //图片颜色变灰色  
//	scene->addChild(back_spr);
//
//	return scene;
//}
