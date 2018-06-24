#ifndef MOCA_H
#define MOCA_H
#include "cocos2d.h"
#include "GameLayer.h"
#include <queue>
USING_NS_CC;
using namespace std;


class GameLayer;
class Moguru;
class Moca :public Sprite
{
public:
	friend Moguru;
	//enum { right1, left1, right0, left0, jump0, jump1, jump2, f0 };
	CREATE_FUNC(Moca);
	virtual bool init();
	Rect getBox();
	void enableFly();
	void update(float dt);

	//Vec2 TileCoordForPosition(GameLayer* g, Vec2 position);	//把Moca的x坐标/图块的宽，y坐标/图块的高算出现在Moca处于tile的第几行第几列
	//void Jump();	//跳跃方法

public:
	Moguru * moguru;
	int flySpeed;
	int runSpeed;
	int runAcce;
	Vec2 gravity = Vec2(0.f, -800.f);
	int state;
	int jumpCount;
	//Vec2 acce;
	Sprite* aMoca;
	Vec2 speed;
	Vec2 iPos;
	bool flyMode;
	bool isD;
	bool isA;
	bool isW;
	bool isS;
	bool lefting;
	bool righting;
	bool faceLeft;

};
class Moguru :public Sprite {
public:
	Sprite * moguru;

	CREATE_FUNC(Moguru);
	virtual bool init();
	//Rect getBox();
	//void follow();
	std::queue<Vec2> actlog;
	bool isparty;
};




#endif


