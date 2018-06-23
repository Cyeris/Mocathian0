#ifndef __GS_H__
#define __GS_H__
#include "cocos2d.h"
#include "Moca.h"
#include "GameLayer.h"
#include "MenuLayer.h"
//#include "Moca.h"
//#include "ui/CocosGUI.h"
USING_NS_CC;
//using namespace ui;
class GameScene : public cocos2d::Scene
{
public:
	
	virtual bool init();
	
	CREATE_FUNC(GameScene);
	GameLayer* gL;
	
};

#endif
