#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__
#include "cocos2d.h"
//#include "GameScene.h"
class MainScene : public cocos2d::Scene
{
public:
	//��������
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainScene);
	//�ĸ���ť
	void menuCloseCallback(Ref* pSender);
	void startGame(Ref* pSender);
	void loadSave(Ref* pSender);
	void openOption(Ref* pSender);
};

#endif // __MainScene_SCENE_H__
