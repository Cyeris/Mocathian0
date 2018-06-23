#ifndef __OPTION_H__
#define __OPTION_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
class Option : public cocos2d::Scene
{
public:
	//float percent = 1.0f;
	//float fx = 1.0f;
	//void show();
	//virtual ~Option();
	virtual bool init();
	//void sliderCallback(cocos2d::Ref * ref, Slider::EventType type);
	CREATE_FUNC(Option);

};

#endif
