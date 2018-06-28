#include "GameLayer.h"
#include "cocos2d.h"
#include "option.h"
#include "MenuLayer.h"
#include <iostream>
#define VB visibleSize
float tTime = 0;
extern float getRandom();
bool GameLayer::init()
{
	tTime = 0;
	vector<Sprite*> danmaku1;
	lastGhost = 0;
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
	_moca->enableFly();
	this->addChild(_moca, 1);
	/////////test
	//auto circle = Sprite::create("tama1.png");
	//circle->setPosition(400, 700);
	//this->addChild(circle, 1);

	auto fer = Fairy1::create();
	fer->setPosition(500, 700);
	this->addChild(fer, 1);
	fairy1.pushBack(fer);

	/*添加Moguru*/
	_moguru = Moguru::create();
	_moguru->setPosition(715, 2544);
	this->addChild(_moguru, 1);
	if (inity > 2544)_moguru->isparty = 1;
	/*follow层*/
	followCamera = Layer::create();
	followCamera->setCascadeOpacityEnabled(true);
	this->addChild(followCamera, 1);

	///////////////////////////
	hintL = Layer::create();
	hintL->setCascadeOpacityEnabled(true);
	hintL->setOpacity(0);
	followCamera->addChild(hintL, 2);

	/*高度条*/
	heightBar = Slider::create();
	heightBar->loadBarTexture("sliderTrack.png"); // what the slider looks like
	heightBar->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "sliderThumb.png");
	heightBar->loadProgressBarTexture("sliderProgress.png");
	heightBar->setRotation(-90);
	heightBar->setPosition(Vec2(32-0.5*visibleSize.width,160 - 0.5*visibleSize.height));
	followCamera->addChild(heightBar, 1);
	
	/*对话框*/
	dia = Dialog::create();
	followCamera->addChild(dia, 2);
	//eventMeetMoguru();
	/*菜单*/
	menuL = MenuLayer::create();
	this->addChild(menuL, 3);

	/*每帧更新*/
	this->scheduleUpdate();
	this->update(0.00694f);
	//键盘监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameLayer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	//showHint();
	return true;
}
void GameLayer::update(float delta)
{
	tTime += delta;
	//log("%f", tTime);
	log("%f", getRandom());

	

	_moca->update(delta);
	//tilePosition(_moca->getPosition());
	checkForAndResolveCollisions(_moca);
	mocapos0.x = _moca->getPosition().x;
	mocapos0.y = _moca->getPosition().y+0.5*_moca->getBox().size.height;
	setViewPoint();
	heightBar->setPercent(100*_moca->getPosition().y / 7680);
	menuL->setPosition(Vec2(camera->getPosition().x, camera->getPosition().y + 1.5*visibleSize.height));
	followCamera->setPosition(camera->getPosition());

	Vec2 cp = camera->getPosition();
	

	//if (ifHurt(Vec2(400, 700),8))
	//{
	//	log("c");
	//}
	if (tTime>1)
	{
		for (auto iter = fairy1.begin(); iter != fairy1.end();) {
			(*iter)->update(delta);
			iter++;
		}
	}
	
	


	//log("%f %f", _moca->getPosition().x, _moca->getPosition().y);
	if (!_moguru->isparty&&_moca->jumpCount==0&&_moca->getPosition().y>=2544)
	{
		eventMeetMoguru();
	}
	if (_moca->getPosition().y>3000)
	{
		randomGhost();
		for (auto iter = ghosts.begin(); iter != ghosts.end();)
		{
			(*iter)->update(_moca, delta);
			Vec2 gp = (*iter)->getPosition();
			if (gp.x > (cp.x + 0.5*VB.width) || gp.x < (cp.x - 0.5*VB.width) || gp.y<(cp.y - 0.5*VB.height) || gp.y>(cp.y + 0.5*VB.height))
			{
				this->removeChild((*iter), true);
				iter = ghosts.erase(iter);
				log("%d", ghosts.size());
			}
			else {
				if (ifHurt(gp,25))
				{
					log("g");
					this->removeChild((*iter), true);
					iter = ghosts.erase(iter);
					log("%d", ghosts.size());
				}
				else
				{
					++iter;
				}
			}
		}
		
	}
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
			_moca->faceLeft = 0;
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
			//if (_moca->righting) _moca->righting = 0;
			_moca->faceLeft = 1;
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
		if (hintOn)
		{
			disHint();
		}
		if (dia->showing)
		{
			if (dia->turned==dia->turns)
			{
				scheduleUpdate();
			}
			dia->next();
		}
		else
		{
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
	player->setPosition(player->iPos); 
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

void GameLayer::showHint(int i)
{
	hintOn = 1;
	auto background = Sprite::create("HintBG.png");
	//background->setOpacity(0);
	hintL->runAction(FadeTo::create(2.0f, 255));
	hintL->addChild(background);
	this->unscheduleUpdate();
}

void GameLayer::disHint()
{
	hintOn = 0;
	hintL->runAction(FadeTo::create(0.4f, 0));
	hintL->removeAllChildren();
	this->scheduleUpdate();
	log("run DIS HINT");
}

bool GameLayer::ifHurt(Vec2 pos, float r)
{
	if (_moca->getDt(pos) < (r + 0.5*_moca->getBox().size.width-4)) {
		//log("hurt");
		return true;
	}
	else
	{
		return false;
	}
}

bool GameLayer::eventMeetMoguru()
{
	unscheduleUpdate();
	dia->shesay("meet", 3);
	_moguru->isparty = 1;
	return true;
}

void GameLayer::randomGhost() {
	if (ghosts.size()<5&&(tTime-lastGhost)>3)
	{
		lastGhost = tTime;
		srand((unsigned)time(NULL));
		if ((rand() % 100 + 1)>60)
		{
			ghosts.pushBack(Ghost::create());
			srand((unsigned)time(NULL));
			ghosts.back()->setPosition(_moca->getPosition().x+(rand() % 100 - 49)*visibleSize.width / 200, _moca->getPosition().y + (rand() % 100 + 1)*visibleSize.height / 200);
			this->addChild(ghosts.back());
			log("%d", ghosts.size());
		}
	}
}
void GameLayer::randomFairy() {
	if (fairy1.size()<5 && (tTime - lastFairy1)>2)
	{
		lastFairy1 = tTime;
		srand((unsigned)time(NULL));
		if ((rand() % 100 + 1)>60)
		{
			ghosts.pushBack(Ghost::create());
			srand((unsigned)time(NULL));
			ghosts.back()->setPosition(_moca->getPosition().x + (rand() % 100 - 49)*visibleSize.width / 200, _moca->getPosition().y + (rand() % 100 + 1)*visibleSize.height / 200);
			this->addChild(ghosts.back());
			log("%d", ghosts.size());
		}
	}
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