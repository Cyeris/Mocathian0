#ifndef __KEYB_H__
#define __KEYB_H__
#include "cocos2d.h"
USING_NS_CC;
class Keyboard
{
public:
	
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);

};

#endif
