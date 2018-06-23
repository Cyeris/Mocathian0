#include "GameLayer.h"
#include "cocos2d.h"
#include "option.h"
#include "MenuLayer.h"
//#include <iostream>
enum { right1, left1, right0, left0, jump0, jump1, jump2, f0 };
float tTime = 0;
bool GameLayer::init()
{

	//����һ����ɫ������װ��  
	//LayerColor *blueSky = CCLayerColor::create(Color4B(100, 100, 250, 255));
	//this->addChild(blueSky);

	//���ص�ͼ  
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
	float levelHeightInPixels = map1->getMapSize().height * map1->getTileSize().height; //��ͼ��ʵ�ʸ߶�  
																						//�ѵ�ͼ����tileCoordsת��Ϊʵ����Ϸ�е�����  
	Vec2 origin = Vec2(tilePos.x * map1->getTileSize().width, levelHeightInPixels - ((tilePos.y + 1)*map1->getTileSize().height));
	return CCRectMake(origin.x, origin.y, map1->getTileSize().width, map1->getTileSize().height);
}

//CCArray* GameLayer::getSurroundingTilesAtPosition(Vec2 position, TMXLayer* layer)
//{
//	CCPoint plPos = this->tilePosition(position); //1 ���ش˴���tile����  
//	//log("%f,%f", plPos.x, plPos.y);
//	CCArray* gids = CCArray::create();//2  ��gid������  
//	gids->retain();
//	//3 ���ǵ�Ŀ������ȡ�������ھ������ܵ�8��tile������ʹ�������ÿ������ȡ9��tile���м�һ�����㣩��ϸ����ͼ��֪���������  
//	for (int i = 0; i<9; i++)
//	{
//		int c = i % 3;   //�൱�ڵ�ǰi��������  
//		int r = (int)(i / 3); //�൱�ڵ�ǰi��������  
//		CCPoint tilePos = Vec2(plPos.x + (c - 1), plPos.y + (r - 1));
//		//4 ȡ����Χtile��gid  
//		int tgid = layer->tileGIDAt(tilePos);
//		//5  
//		Rect tileRect = this->tileRect(tilePos);  //��Χ��  
//		float x = tileRect.origin.x;  //λ��  
//		float y = tileRect.origin.y;
//		//ȡ�����tile�ĸ������ԣ��ŵ�CCDictionary��  
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
//	//ȥ���м䣨��������tile��  
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
		//map1->propertiesForGID(gid);//һ���ֵ�
		//						   //��ȡ x ����
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
	//	Rect playerRect = player->getBox();  //2 ��ҵİ�Χ��  
	//	int gid = dic->valueForKey("gid")->intValue();  //3 ��CCDictionary��ȡ����Ҹ���tile��gidֵ  
	//	if (gid)
	//	{
	//		//log("gid");
	//		float rect_x = dic->valueForKey("x")->floatValue();
	//		float rect_y = dic->valueForKey("y")->floatValue();
	//		float width = map1->getTileSize().width;
	//		float height = map1->getTileSize().height;
	//		//4 ȡ�����tile��Rect  
	//		Rect tileRect = CCRectMake(rect_x, rect_y, width, height);
	//		//log("%f %f %f %f", rect_x, rect_y, width, height);
	//		//log("PLA:%f %f %f %f", playerRect.origin.x, playerRect.origin.y, playerRect.size.width, playerRect.size.height);
	//		if (tileRect.intersectsRect(playerRect)) //�����Ұ�Χ����tile��Χ����ײ  
	//		{
	//			log("ok");
	//			//5 ȡ����ײ����  
	//			Rect intersection = intersectsRect(playerRect, tileRect);
	//			int tileIndx = tiles->indexOfObject(dic); //6 ȡ��dic���±�����  
	//			if (tileIndx == 0)
	//			{
	//				//tile��koala���·� �����䵽��tile��  
	//				player->iPos = ccp(player->iPos.x, player->iPos.y + intersection.size.height);
	//				if (player->speed.y<0)
	//				{
	//					player->speed.y = 0;
	//					player->jumpCount = 0;
	//				}
	//			}
	//			else if (tileIndx == 1) //����ͷ����tile  
	//			{
	//				//��koala�����tile��Ҫ��������������  
	//				player->iPos = ccp(player->iPos.x, player->iPos.y - intersection.size.height);
	//			}
	//			else if (tileIndx == 2)
	//			{
	//				//��ߵ�tile  
	//				player->iPos = ccp(player->iPos.x + intersection.size.width, player->iPos.y);
	//			}
	//			else if (tileIndx == 3)
	//			{
	//				//�ұߵ�tile  
	//				player->iPos = ccp(player->iPos.x - intersection.size.width, player->iPos.y);
	//			}
	//			else
	//			{
	//				//7 �����ײ��ˮƽ�������ֱ�棬˵����ɫ��������ײ  
	//				if (intersection.size.width > intersection.size.height)
	//				{
	//					//tile is diagonal, but resolving collision vertically  
	//					float intersectionHeight;
	//					if (tileIndx>5) //˵���ǲȵ�б�µ�ש��,��ɫӦ������ȥ  
	//					{
	//						intersectionHeight = intersection.size.height;
	//					}
	//					else  //˵���Ƕ���б�ϵ�ש�飬��ɫӦ��������  
	//					{
	//						intersectionHeight = -intersection.size.height;
	//					}
	//					player->iPos = ccp(player->iPos.x, player->iPos.y + intersectionHeight);
	//				}
	//				else //�����ײ��ˮƽ��С����ֱ�棬˵����ɫ������ײ��  
	//				{
	//					float resolutionWidth;
	//					if (tileIndx == 6 || tileIndx == 4) //��ɫ����б��ߵ�tile ��ɫӦ������ȥ  
	//					{
	//						resolutionWidth = intersection.size.width;
	//					}
	//					else //��ɫ����б�ұߵ�tile, ��ɫӦ������ȥ  
	//					{
	//						resolutionWidth = -intersection.size.width;
	//					}
	//					player->iPos = ccp(player->iPos.x + resolutionWidth, player->iPos.y);
	//				}
	//			}
	//		}
	//	}
	//}
	player->setPosition(player->iPos); //7 ������λ���趨��������ȥ�ĵط�  
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
	CCPoint ori;    //���½Ƕ���     cocos2dx��CCRect�������½�Ϊԭ�㣬w,hΪ����(��͸�)�����������Ͻ���top,���½�Ϊbottom  
	CCPoint topM;   //���½Ƕ���  
	float width = 0.f, height = 0.f;

	ori.x = max(rectA.getMinX(), rectB.getMinX()); //���½�x����ȡ��������ori����x������  
	ori.y = max(rectA.getMinY(), rectB.getMinY()); //���½�y����ȡ��������ori����y������  

	topM.x = min(rectA.getMaxX(), rectB.getMaxX()); //���Ͻ�x����ȡ�����������ϽǶ���x����С��  
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