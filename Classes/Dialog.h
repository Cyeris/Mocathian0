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
	bool shesay(std::string name="", int count = 0);
	void next();

	bool showing;

	bool mocaOn;
	bool moguruOn;
	bool fyeOn;

	int turns;
	int turned;
	std::string nameNow;
	Label* text;
	FadeTo* showDia;
	FadeOut* disDia;

	Sprite* dmoca;
	Sprite* dmoguru;
	Sprite* dfye;

	Sprite* mocaDialog;
	Sprite* moguruDialog;
	Sprite* fyeDialog;

	__Dictionary* kaiwa;
};

#endif
