#include "GameLayer.h"
#include "cocos2d.h"
#include "option.h"
#include "MenuLayer.h"

//#include <iostream>
//enum { right1, left1, right0, left0, jump0, jump1, jump2, f0 };
float tTime = 0;
bool GameLayer::init()
{
	vector<Sprite*> danmaku1;


	/*auto diabox = Sprite::create("mocaDialog.png");
	diabox->setPosition(origin.x, origin.y);
	this->addChild(diabox, 3);*/

	//加载地图 
	map1 = CCTMXTiledMap::create("map/map1.tmx");
	map1->setPosition(origin.x, origin.y);
	this->addChild(map1);
	_clouds = map1->getLayer("Cloud");
	/*添加Moca*/
	_moca = Moca::create();
	float initx = UserDefault::getInstance()->getFloatForKey("x");
	float inity = UserDefault::getInstance()->getFloatForKey("y");
	_moca->setPosition(initx, inity);

	//_moca->enableFly();
	this->addChild(_moca, 1);

	/*添加Moguru*/
	_moguru = Moguru::create();
	_moguru->setPosition(715, 2544);
	this->addChild(_moguru, 1);

	/*高度条*/
	heightBar = Slider::create();
	heightBar->loadBarTexture("sliderTrack.png"); // what the slider looks like
	heightBar->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "sliderThumb.png");
	heightBar->loadProgressBarTexture("sliderProgress.png");
	heightBar->setRotation(-90);
	heightBar->setPosition(Vec2(100,50));
	this->addChild(heightBar, 1);
	
	/*菜单*/
	menuL = MenuLayer::create();
	this->addChild(menuL, 2);

	/*每帧更新*/
	this->scheduleUpdate();
	this->update(0.00694f);
	//键盘监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameLayer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	return true;
}
void GameLayer::update(float delta)
{
	tTime += delta;
	//log("%f", tTime);
	_moca->update(delta);
	//tilePosition(_moca->getPosition());
	checkForAndResolveCollisions(_moca);
	setViewPoint();
	heightBar->setPosition(Vec2(camera->getPosition().x - 0.48*visibleSize.width, camera->getPosition().y - 0.32*visibleSize.height));
	heightBar->setPercent(100*_moca->getPosition().y / 7680);
	menuL->setPosition(Vec2(camera->getPosition().x, camera->getPosition().y + 1.5*visibleSize.height));
	log("%f %f", _moca->getPosition().x, _moca->getPosition().y);
}
void GameLayer::setViewPoint()
{
	camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
	Vec2 pos = _moca->getPosition();
	Vec2 camPos = camera->getPosition();
	if (pos.x>512&& pos.x<1314) camPos.x = pos.x;
	camPos.y = pos.y+120;
	camera->setPosition(camPos);
}
void GameLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event) {	
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (_moca->flyMode)
		{
			_moca->isD = 1;
		}
		else
		{
			/*if (_moca->state == left0 || _moca->state == left1)
			{
				_moca->setScaleX(1);
			}
			_moca->state = right1;*/
			if (_moca->lefting)
			{
				_moca->lefting = 0;
			}
			_moca->setScaleX(1);
			_moca->righting = 1;
		}
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (_moca->flyMode)
		{
			_moca->isA = 1;
		}
		else
		{
			if (_moca->righting) _moca->righting = 0;
			_moca->setScaleX(-1);
			_moca->lefting=1;
		}
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (_moca->flyMode) _moca->isW = 1;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (_moca->flyMode) _moca->isS = 1;
		break;
	case EventKeyboard::KeyCode::KEY_Z:
		switch (_moca->jumpCount)
		{
		case 0:
			_moca->speed.y += 440;
			_moca->jumpCount = 1;
			break;
		case 1:
			_moca->speed.y += 480;
			_moca->jumpCount = 2;
			break;
		case 2:
			break;
		}
		break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		if (!menuL->escOn)
		{
			menuL->mocaPos = _moca->getPosition();
			menuL->showMenu(1,this,camera->getPosition());
		}
		else
		{
			menuL->showMenu(0,this, camera->getPosition());
		}

		//renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
		//
		////遍历当前类的所有子节点信息，画入renderTexture中。  
		////这里类似截图。  
		//renderTexture->begin();
		//this->getParent()->visit();
		//renderTexture->end();

		//camera->setPosition(Vec2(visibleSize.width *0.5, visibleSize.height *0.5));
		////将游戏界面暂停，压入场景堆栈。并切换到GamePause界面  
		//CCDirector::sharedDirector()->pushScene(MenuLayer::createScene(renderTexture));
		
		break;
	default:
		break;
	}
};
void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event) {
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (_moca->flyMode)
		{
			_moca->isD = 0;
		}
		else
		{
			//_moca->state = right0;
			_moca->righting = 0;
		}
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (_moca->flyMode)
		{
			_moca->isA = 0;
		}
		else
		{
			//_moca->state = left0;
			_moca->lefting = 0;

		}
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (_moca->flyMode)
		{
			_moca->isW = 0;
		}
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (_moca->flyMode)
		{
			_moca->isS = 0;
		}
		break;
	default:
		break;
	}
}
//Point->tile position
Vec2 GameLayer::tilePosition(Vec2 position)
{
	int x = position.x / map1->getTileSize().width;
	//int y = ((map1->getMapSize().height * map1->getTileSize().height) - position.y) / map1->getTileSize().height;
	int y = (map1->getMapSize().height * map1->getTileSize().height - position.y) / map1->getTileSize().height-1 ;
	//log("TP:%d %d", x, y);
	return Vec2(x, y);
}
//tile position->tile Rect
Rect GameLayer::getTileRect(Vec2 tilePos)
{
	float levelHeightInPixels = map1->getMapSize().height * map1->getTileSize().height; //地图的实际高度  
																						//把地图坐标tileCoords转化为实际游戏中的坐标  
	Vec2 origin = Vec2(tilePos.x * map1->getTileSize().width, levelHeightInPixels - ((tilePos.y + 1)*map1->getTileSize().height));
	return Rect(origin.x, origin.y, map1->getTileSize().width, map1->getTileSize().height);
}
//碰撞
void GameLayer::checkForAndResolveCollisions(Moca* player)
{
	Vec2 iPosTile = tilePosition(player->iPos);
	Rect playerRect = player->getBox();
	Rect tileRect = getTileRect(Vec2(iPosTile.x, iPosTile.y+1));
	tileRect.origin.y += 44;
	tileRect.size.height -= 44;
	iPosTile.y++;
	int downgid = _clouds->getTileGIDAt(iPosTile);
	if (downgid != 0) {
		if (tileRect.intersectsRect(playerRect)&& player->speed.y<0)
		{
			player->iPos = Vec2(player->iPos.x, player->iPos.y + 0.1);
			player->speed.y = 0;
			player->jumpCount = 0;
		}
	}
	if (player->iPos.x>1760)
	{
		player->iPos.x = 1760;
		if (player->speed.x>0)
		{
			player->speed.x = 0;
		}
	}
	if (player->iPos.x<68)
	{
		player->iPos.x = 68;
		if (player->speed.x<0)
		{
			player->speed.x = 0;
		}
	}
	player->setPosition(player->iPos); //7 把主角位置设定到它期望去的地方  
	if (_moguru->isparty)
	{
		Vec2 moguPos = player->getPosition();
		moguPos.x -= 40;
		moguPos.y += 50;
		if (_moguru->actlog.size()<16)
		{
			_moguru->actlog.push(moguPos);
		}
		else
		{
			_moguru->setPosition(_moguru->actlog.front());
			_moguru->actlog.pop();
			_moguru->actlog.push(moguPos);
		}
	}
}

bool GameLayer::eventMeetMoguru()
{
	unscheduleUpdate();





	scheduleUpdate();
	return true;
}

//Rect GameLayer::intersectsRect(Rect rectA, Rect rectB)
//
//{
//	CCPoint ori;    //左下角顶点     cocos2dx的CCRect是以左下角为原点，w,h为参数(宽和高)，并不是左上角是top,右下角为bottom  
//	CCPoint topM;   //右下角顶点  
//	float width = 0.f, height = 0.f;
//
//	ori.x = max(rectA.getMinX(), rectB.getMinX()); //左下角x坐标取两个矩形ori顶点x坐标大的  
//	ori.y = max(rectA.getMinY(), rectB.getMinY()); //左下角y坐标取两个矩形ori顶点y坐标大的  
//
//	topM.x = min(rectA.getMaxX(), rectB.getMaxX()); //右上角x坐标取两个矩形右上角顶点x坐标小的  
//	topM.y = min(rectA.getMaxY(), rectB.getMaxY());
//
//	width = topM.x - ori.x;
//	height = topM.y - ori.y;
//	log("touch:%f %f %f %f", ori.x, ori.y, width, height);
//
//	return CCRectMake(ori.x, ori.y, width, height);
//}

//动画

//auto jumpCache = SpriteFrameCache::getInstance();
//jumpCache->addSpriteFramesWithFile("image/jump/test.plist");
//auto test = Sprite::createWithSpriteFrameName("IMG00000.png");
//test->setPosition(400, 400);
//auto jumpAnime = Animation::create();
//for (int i = 0; i < 13; i++)
//{
//	char name[32] = { 0 };
//	sprintf(name, "image/jump/IMG000%02d.png", i);
//	jumpAnime->addSpriteFrameWithFile(name);
//}
//jumpAnime->setLoops(-1);
//jumpAnime->setDelayPerUnit(0.1f);
//auto action = Animate::create(jumpAnime);
//this->addChild(test, 2);
//test->runAction(action);