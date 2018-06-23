#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "reader/CreatorReader.h"
#include "option.h"
#include "GameScene.h"
USING_NS_CC;

Scene* MainScene::createScene()
{
	return MainScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin(); 
	if (!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/mainmenu.wav", true);
	}

	//MENUITEM
	auto startGame = MenuItemImage::create(
		"start.png",
		"start.png",
		CC_CALLBACK_1(MainScene::startGame, this));
	auto loadGame = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainScene::loadSave, this));


	std::string savePath = FileUtils::getInstance()->getWritablePath() + "save.txt";
	std::string saveData = FileUtils::getInstance()->getStringFromFile(savePath);








	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));
	/*{
	float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
	float y = origin.y + closeItem->getContentSize().height / 2;
	}*/
	closeItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 200));
	loadGame->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 200 + closeItem->getContentSize().height));
	startGame->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 200 + closeItem->getContentSize().height + loadGame->getContentSize().height));
	auto menu = Menu::create(closeItem, loadGame, startGame, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto goOption = Button::create("back.png");

	goOption->cocos2d::Node::setScale((visibleSize.width * 0.1 / goOption->getContentSize().width));
	goOption->setPosition(Vec2(origin.x + visibleSize.width - goOption->getContentSize().width / 2, origin.y + goOption->getContentSize().height / 2));
	goOption->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionSlideInL::create(0.5, Option::create());
			Director::getInstance()->replaceScene(transition);
		}
	});

	this->addChild(goOption);
	// III
	auto mainBG = Sprite::create("mainBG.jpg");
	mainBG->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(mainBG, -1);




	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	// add "MainScene" splash screen"
	/*auto sprite = Sprite::create("MainScene.png");
	if (sprite == nullptr)
	{
	problemLoading("'MainScene.png'");
	}
	else
	{
	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	}*/
	return true;
}
void MainScene::startGame(Ref* pSender) {
	//SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->pushScene(transition);
	
}
void MainScene::loadSave(Ref * pSender)
{
	/*std::string savePath = FileUtils::getInstance()->getWritablePath() + "save.txt";
	std::string saveData = FileUtils::getInstance()->getStringFromFile(savePath);*/
	CCLOG("============================================================");
	CCLOG("reading begin!");
	auto userdefault = UserDefault::getInstance();
	//根据isExisted的值来判断，是否数据被写入
	if (userdefault->getBoolForKey("isExisted"))
	{
		//读取键值为Int的内容并输出
		int intVar = userdefault->getIntegerForKey("int");
		CCLOG("the int is:%d", intVar);
		//读取键值为float的内容并输出　　　　　　
		float floatVar = userdefault->getFloatForKey("float");
		CCLOG("the float is:%f", floatVar);
		//读取键值为string的内容并输出
		std::string str = userdefault->getStringForKey("string");
		CCLOG("the string is:%s", str);
	}
	//如果isExisted的键值为false的话，说明信息没有被保存，不可用
	else
	{
		CCLOG("not exist!");
	}
	CCLOG("============================================================");
}


void MainScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
void MainScene::openOption(Ref* pSender)
{
	auto scene = Option::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}
