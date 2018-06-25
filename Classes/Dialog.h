#ifndef __DIALOG_H__
#define __DIALOG_H__
#include "cocos2d.h"
USING_NS_CC;
extern Size visibleSize;
extern Vec2 origin;
class Dialog : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(Dialog);
	bool shesay(int who, std::string name, int count = 0);
	void next();

	bool showing;

	int turns;
	int turned;
	Label* text;
	FadeTo* showDia;
	FadeOut* disDia;


	Sprite* mocaDialog;
	Sprite* moguruDialog;
	Sprite* fyeDialog;

	Dictionary* kaiwa;
};

#endif
