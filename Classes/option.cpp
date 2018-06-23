#include "option.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace ui;



bool Option::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto bg = Sprite::create("optionBG.png");
	bg->setScale(3.0);/////////////////////////////////////////////////////////////
	this->addChild(bg);
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	Slider* mainsli = Slider::create();
	mainsli->loadBarTexture("sliderTrack.png");
	mainsli->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "sliderThumb.png");
	mainsli->loadProgressBarTexture("sliderProgress.png");

	mainsli->setPosition(Vec2(origin.x+0.66*visibleSize.width, origin.y + 0.5*visibleSize.height+2*mainsli->getContentSize().height));
	float volume = CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
	log("%f", volume);
	mainsli->setPercent(int(100));
	mainsli->addEventListener([=](Ref* sender, Slider::EventType type) {
		if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
			float percent = static_cast<float>(mainsli->getPercent()) / 100;
			
			log("%f", percent);
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(percent);
			log("now%f", CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume());
			//UserDefault::getInstance()->setFloatForKey("musicPercent", percent);
		}
	});
	auto mainL = Label::createWithTTF("Main", "fonts/PingFang Light.ttf", 32);
	mainL->setPosition(Vec2(origin.x + 0.33*visibleSize.width, 0.5*visibleSize.height + 2 * mainsli->getContentSize().height));
	this->addChild(mainL,10);
	/*auto fxL = Label::createWithTTF("Sound", "fonts/PingFang Light.ttf", 32);
	fxL->setPosition(Vec2(origin.x + 0.33*visibleSize.width, 0.5*visibleSize.height - 2 * mainsli->getContentSize().height));
	this->addChild(fxL,10);*/
	// create menu, it's an autorelease object
	//auto menu = Menu::create(mainsli, fxsli, NULL);
	//menu->setPosition(Vec2::ZERO);
	this->addChild(mainsli);
	//this->addChild(fxsli);
	auto goMain = Button::create("back.png");

	goMain->cocos2d::Node::setScale((visibleSize.width * 0.1 / goMain->getContentSize().width));
	goMain->setPosition(Vec2(origin.x + visibleSize.width - goMain->getContentSize().width / 2, origin.y + goMain->getContentSize().height / 2));
	goMain->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionSlideInL::create(0.5, MainScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});

	this->addChild(goMain);

	return true;
}
