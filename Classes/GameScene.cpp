#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include "GameScene.h"
#include "GameLayer.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace ui;
Size visibleSize;
Vec2 origin;

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	bool flag = false;
	do
	{
		visibleSize = Director::getInstance()->getVisibleSize();
		origin = Director::getInstance()->getVisibleOrigin();
		//////////////////////////////
		//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/starting.wav", true);
		gL = GameLayer::create();
		this->addChild(gL);

		/*Camera *camera = Camera::create();
		camera->setCameraFlag(CameraFlag::DEFAULT);
		this->addChild(camera);*/


		/*menuL = MenuLayer::create();
		menuL->setAnchorPoint(Vec2(0.5, 0.5));
		menuL->setPosition(origin.x+0.5*visibleSize.width,origin.y+ 1.5*visibleSize.height);
		this->addChild(menuL, 2);*/
		
				
		flag = true;
	} while (0);
	return flag;

}
