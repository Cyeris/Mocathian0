#include "GameLayer.h"
#include "cocos2d.h"
#include "option.h"
#include "MenuLayer.h"
//#include <iostream>
enum { right1, left1, right0, left0, jump0, jump1, jump2, f0 };
float tTime = 0;
bool GameLayer::init()
{

	//加载一个蓝色背景当装饰  
	//LayerColor *blueSky = CCLayerColor::create(Color4B(100, 100, 250, 255));
	//this->addChild(blueSky);

	//加载地图  
	//map1 = CCTMXTiledMap::create("map/level1.tmx");
	map1 = CCTMXTiledMap::create("map/map1.tmx");

	//map1->setScale(3.0f);
	//map1->setAnchorPoint(Vec2(0, 0));
	map1->setPosition(origin.x, origin.y);
	//log("%d %d", origin.x, origin.y);
	this->addChild(map1);
	_clouds = map1->layerNamed("Cloud");
	
	_moca = Moca::create();
	//_moca->setScale(0.5f);
	_moca->setPosition(200, 250);
	//_moca->enableFly();
	//_moca->state = right0;
	this->addChild(_moca, 1);
	this->scheduleUpdate();
	this->update(0.00694);

	auto fadeOut = FadeTo::create(0.5f, 100);


	menuL = MenuLayer::create();
	menuL->setAnchorPoint(Vec2(0.5, 0.5));
	menuL->setPosition(origin.x + 0.5*visibleSize.width, origin.y + 0.5*visibleSize.height);
	menuL->setOpacity(0);
	this->addChild(menuL, 2);


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
	tilePosition(_moca->getPosition());
	//this->getSurroundingTilesAtPosition(_moca->getPosition(), _walls);
	this->checkForAndResolveCollisions(_moca);
	this->setViewPoint(_moca->getPosition());
}
void GameLayer::setViewPoint(const Point& point)
{
	//Size winSize = Director::getInstance()->getWinSize();
	/*int x = max(point.x, winSize.width / 2);
	int y = max(point.y, winSize.height / 2);
	x = min(x, (int)(map1->getMapSize().width * map1->getTileSize().width - winSize.width / 2));
	y = min(y, (int)(map1->getMapSize().height * map1->getTileSize().height - winSize.height / 2));
	Point actualPoint(x, y);
	Point centerOfView(winSize.width / 2, winSize.height / 2);*/

	/*int x = max(point.x, visibleSize.width / 2);
	int y = max(point.y, visibleSize.height / 2);
	x = min(x, (int)(map1->getMapSize().width * map1->getTileSize().width - visibleSize.width / 2));
	y = min(y, (int)(map1->getMapSize().height * map1->getTileSize().height - visibleSize.height / 2));
	log("actualPoint:%d %d", x, y);
	Point actualPoint(x, y);
	Point centerOfView(visibleSize.width / 2, visibleSize.height / 2);

	Point viewPoint = centerOfView - actualPoint;

	log("viewPoint:%f %f", viewPoint.x, viewPoint.y);

	map1->setPosition(viewPoint);*/
	auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
	camera->setPosition(_moca->getPosition());


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
			_moca->speed.y += 480;
			_moca->jumpCount = 1;
			break;
		case 1:
			_moca->speed.y += 360;
			_moca->jumpCount = 2;
			break;
		case 2:
			break;
		}
		break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		if (!menuL->escOn)
		{
			menuL->showMenu(1,this);
		}
		else
		{
			menuL->showMenu(0,this);
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
Vec2 GameLayer::tilePosition(Vec2 position)
{
	int x = position.x / map1->getTileSize().width;
	//int y = ((map1->getMapSize().height * map1->getTileSize().height) - position.y) / map1->getTileSize().height;
	int y = (map1->getMapSize().height * map1->getTileSize().height - position.y) / map1->getTileSize().height-1 ;
	//log("TP:%d %d", x, y);
	return Vec2(x, y);
}
Rect GameLayer::getTileRect(Vec2 tilePos)
{
	float levelHeightInPixels = map1->getMapSize().height * map1->getTileSize().height; //地图的实际高度  
																						//把地图坐标tileCoords转化为实际游戏中的坐标  
	Vec2 origin = Vec2(tilePos.x * map1->getTileSize().width, levelHeightInPixels - ((tilePos.y + 1)*map1->getTileSize().height));
	return CCRectMake(origin.x, origin.y, map1->getTileSize().width, map1->getTileSize().height);
}

//CCArray* GameLayer::getSurroundingTilesAtPosition(Vec2 position, TMXLayer* layer)
//{
//	CCPoint plPos = this->tilePosition(position); //1 返回此处的tile坐标  
//	//log("%f,%f", plPos.x, plPos.y);
//	CCArray* gids = CCArray::create();//2  存gid的数组  
//	gids->retain();
//	//3 我们的目的是想取出环绕在精灵四周的8个tile，这里就从上至下每行三个取9个tile（中间一个不算）仔细画画图就知代码的意义  
//	for (int i = 0; i<9; i++)
//	{
//		int c = i % 3;   //相当于当前i所处的列  
//		int r = (int)(i / 3); //相当于当前i所处的行  
//		CCPoint tilePos = Vec2(plPos.x + (c - 1), plPos.y + (r - 1));
//		//4 取出包围tile的gid  
//		int tgid = layer->tileGIDAt(tilePos);
//		//5  
//		Rect tileRect = this->tileRect(tilePos);  //包围盒  
//		float x = tileRect.origin.x;  //位置  
//		float y = tileRect.origin.y;
//		//取出这个tile的各个属性，放到CCDictionary里  
//		CCDictionary *tileDict = CCDictionary::create();
//		CCString* str_tgid = CCString::createWithFormat("%d", tgid);
//		CCString* str_x = CCString::createWithFormat("%f", x);
//		CCString* str_y = CCString::createWithFormat("%f", y);
//		tileDict->setObject(str_tgid, "gid");
//		tileDict->setObject(str_x, "x");
//		tileDict->setObject(str_y, "y");
//		tileDict->setObject((CCObject *)&tilePos, "tilePos");
//		//6  
//		gids->addObject(tileDict);
//	}
//	//去掉中间（即自身结点tile）  
//	gids->removeObjectAtIndex(4);
//	gids->insertObject(gids->objectAtIndex(2), 6);
//	gids->removeObjectAtIndex(2);
//	gids->exchangeObjectAtIndex(4, 6);
//	gids->exchangeObjectAtIndex(0, 4);//7  
//
//	return gids;
//}
void GameLayer::checkForAndResolveCollisions(Moca* player)
{
	//CCArray* tiles = this->getSurroundingTilesAtPosition(player->iPos, _walls); 
	//CCArray* tiles = this->getSurroundingTilesAtPosition(player->getPosition(), _walls); 
	



	Vec2 iPosTile = tilePosition(player->iPos);
	Rect playerRect = player->getBox();
	Rect tileRect = getTileRect(Vec2(iPosTile.x, iPosTile.y+1));
	iPosTile.y++;
	int downgid = _clouds->tileGIDAt(iPosTile);
	//log("gid:%d", downgid);

	if (downgid != 0) {
		//map1->propertiesForGID(gid);//一个字典
		//						   //获取 x 坐标
		//map1->propertiesForGID(gid)->valueForKey("touch")->intValue();
		if (tileRect.intersectsRect(playerRect))
		{
			//log("rr");
			//player->iPos = player->getPosition();
			Rect intersection = intersectsRect(playerRect, tileRect);
			player->iPos = ccp(player->iPos.x, player->iPos.y + 0.1);
			player->speed.y = 0;
			player->jumpCount = 0;
		}
	}



	//CCObject* obj = NULL;
	//CCDictionary* dic = NULL;
	//CCARRAY_FOREACH(tiles, obj)
	//{
	//	dic = (CCDictionary*)obj;
	//	Rect playerRect = player->getBox();  //2 玩家的包围盒  
	//	int gid = dic->valueForKey("gid")->intValue();  //3 从CCDictionary中取得玩家附近tile的gid值  
	//	if (gid)
	//	{
	//		//log("gid");
	//		float rect_x = dic->valueForKey("x")->floatValue();
	//		float rect_y = dic->valueForKey("y")->floatValue();
	//		float width = map1->getTileSize().width;
	//		float height = map1->getTileSize().height;
	//		//4 取得这个tile的Rect  
	//		Rect tileRect = CCRectMake(rect_x, rect_y, width, height);
	//		//log("%f %f %f %f", rect_x, rect_y, width, height);
	//		//log("PLA:%f %f %f %f", playerRect.origin.x, playerRect.origin.y, playerRect.size.width, playerRect.size.height);
	//		if (tileRect.intersectsRect(playerRect)) //如果玩家包围盒与tile包围盒相撞  
	//		{
	//			log("ok");
	//			//5 取得相撞部分  
	//			Rect intersection = intersectsRect(playerRect, tileRect);
	//			int tileIndx = tiles->indexOfObject(dic); //6 取得dic的下标索引  
	//			if (tileIndx == 0)
	//			{
	//				//tile在koala正下方 考拉落到了tile上  
	//				player->iPos = ccp(player->iPos.x, player->iPos.y + intersection.size.height);
	//				if (player->speed.y<0)
	//				{
	//					player->speed.y = 0;
	//					player->jumpCount = 0;
	//				}
	//			}
	//			else if (tileIndx == 1) //考拉头顶到tile  
	//			{
	//				//在koala上面的tile，要让主角向上移移  
	//				player->iPos = ccp(player->iPos.x, player->iPos.y - intersection.size.height);
	//			}
	//			else if (tileIndx == 2)
	//			{
	//				//左边的tile  
	//				player->iPos = ccp(player->iPos.x + intersection.size.width, player->iPos.y);
	//			}
	//			else if (tileIndx == 3)
	//			{
	//				//右边的tile  
	//				player->iPos = ccp(player->iPos.x - intersection.size.width, player->iPos.y);
	//			}
	//			else
	//			{
	//				//7 如果碰撞的水平面大于竖直面，说明角色是上下碰撞  
	//				if (intersection.size.width > intersection.size.height)
	//				{
	//					//tile is diagonal, but resolving collision vertically  
	//					float intersectionHeight;
	//					if (tileIndx>5) //说明是踩到斜下的砖块,角色应该向上去  
	//					{
	//						intersectionHeight = intersection.size.height;
	//					}
	//					else  //说明是顶到斜上的砖块，角色应该向下托  
	//					{
	//						intersectionHeight = -intersection.size.height;
	//					}
	//					player->iPos = ccp(player->iPos.x, player->iPos.y + intersectionHeight);
	//				}
	//				else //如果碰撞的水平面小于竖直面，说明角色是左右撞到  
	//				{
	//					float resolutionWidth;
	//					if (tileIndx == 6 || tileIndx == 4) //角色碰到斜左边的tile 角色应该向右去  
	//					{
	//						resolutionWidth = intersection.size.width;
	//					}
	//					else //角色碰到斜右边的tile, 角色应该向左去  
	//					{
	//						resolutionWidth = -intersection.size.width;
	//					}
	//					player->iPos = ccp(player->iPos.x + resolutionWidth, player->iPos.y);
	//				}
	//			}
	//		}
	//	}
	//}
	player->setPosition(player->iPos); //7 把主角位置设定到它期望去的地方  
}

Rect GameLayer::intersectsRect(Rect rectA, Rect rectB)

{
	/*float xa1 = rect1.getMinX();
	float ya1 = rect1.getMinY();

	float xa2 = rect1.getMaxX();
	float ya2 = rect1.getMaxY();

	float xb1 = rect2.getMinX();
	float yb1 = rect2.getMinY();

	float xb2 = rect2.getMaxX();
	float yb2 = rect2.getMaxY();

	float xc1, yc1;
	float xc2, yc2;

	xc1 = std::max(xa1, xb1);
	yc1 = std::max(ya1, yb1);
	xc2 = std::min(xa2, xb2);
	yc2 = std::min(ya2, yb2);
	log("touch:%f %f %f %f", xc1, yc1, xc2 - xc1, yc2 - yc1);
	return CCRectMake(xc1, yc1, xc2 - xc1, yc2 - yc1);
*/
	CCPoint ori;    //左下角顶点     cocos2dx的CCRect是以左下角为原点，w,h为参数(宽和高)，并不是左上角是top,右下角为bottom  
	CCPoint topM;   //右下角顶点  
	float width = 0.f, height = 0.f;

	ori.x = max(rectA.getMinX(), rectB.getMinX()); //左下角x坐标取两个矩形ori顶点x坐标大的  
	ori.y = max(rectA.getMinY(), rectB.getMinY()); //左下角y坐标取两个矩形ori顶点y坐标大的  

	topM.x = min(rectA.getMaxX(), rectB.getMaxX()); //右上角x坐标取两个矩形右上角顶点x坐标小的  
	topM.y = min(rectA.getMaxY(), rectB.getMaxY());

	width = topM.x - ori.x;
	height = topM.y - ori.y;
	log("touch:%f %f %f %f", ori.x, ori.y, width, height);

	return CCRectMake(ori.x, ori.y, width, height);
}



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