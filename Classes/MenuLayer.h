#ifndef __MENU_H__
#define __MENU_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameLayer.h"
USING_NS_CC;
using namespace ui;
extern Size visibleSize;
extern Vec2 origin;
class GameLayer;
class MenuLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	void menuCloseCallback(Ref * pSender);
	void exitCallback(Ref * pSender);
	void showMenu(bool show, GameLayer* gL);
	CREATE_FUNC(MenuLayer);
	bool escOn;
	GameLayer* pGameLayer;
};

#endif
