#ifndef _GAMELAYER_
#define _GAMELAYER_
#include "cocos2d.h"
#include "Moca.h"
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"
#include "Dialog.h"

USING_NS_CC;
extern Size visibleSize;
extern Vec2 origin;
//extern std::string savedata;

class Moca;
class Moguru;
class MenuLayer;
class Dialog;

class GameLayer : public cocos2d::Layer
{
public:
	//friend MenuLayer;
	Moca * _moca;
	virtual bool init();
	void update(float delta);
	void setViewPoint();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);
	void checkForAndResolveCollisions(Moca* player);
	CREATE_FUNC(GameLayer);

	bool eventMeetMoguru();






	Vec2 tilePosition(Vec2 position);
	Rect getTileRect(Vec2 tilePos);
	TMXTiledMap * map1;
	Dialog* dia;
	MenuLayer* menuL;
	TMXLayer * _clouds;
	Slider* heightBar;
	Camera* camera;
	Moguru* _moguru;

	//CCPoint TileCoordForPosition(CCPoint position);
	//Rect intersectsRect(Rect rectA, Rect rectB);
	//Rect tileRect(cocos2d::CCPoint tileCoords);
	//CCArray* getSurroundingTilesAtPosition(Vec2 position, TMXLayer* layer);
};


#endif 



//	CCTexture2D* t;	//������ͼ
//	CCPointArray *var_1, *var_2;
//	Mario* mario;

//void AddSprite();
//void FindSpriteAndPlayAnimation(const char* layer, CCPointArray* var, int Animationtype);
//void QuestionMarkAnimation(CCSprite* sprite, float time);	//�ʺ�ש��Ķ���
//void CoinAnimation(CCSprite* sprite, float time);	//��Ҷ���
//void Logic(float fDelta);
//void SetMap();	//����tile��ͼ
//bool ccTouchBegan(CCTouch *touch, CCEvent *pEvent);	 //����
//void ccTouchMoved(CCTouch *touch, CCEvent *pEvent);   //�ƶ�
//void ccTouchEnded(CCTouch *touch, CCEvent *pEvent);   //̧��




















//class GameLevelLayer : public cocos2d::CCLayer
//{
//public:
//	GameLevelLayer(void);
//	~GameLevelLayer(void);
//	CREATE_FUNC(GameLevelLayer);
//
//	bool init();
//
//	static cocos2d::CCScene* scene();
//protected:
//	cocos2d::CCTMXTiledMap *map;
//};