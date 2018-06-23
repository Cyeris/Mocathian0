#ifndef MOCA_H
#define MOCA_H
#include "cocos2d.h"
#include "GameLayer.h"
USING_NS_CC;
using namespace std;


class GameLayer;

class Moca :public Sprite
{
public:
	enum { right1, left1, right0, left0, jump0, jump1, jump2, f0 };
	CREATE_FUNC(Moca);
	virtual bool init();
	//Rect getBox(Vec2 pos);
	Rect getBox();
	void enableFly();
	void update(float dt);

	//Vec2 TileCoordForPosition(GameLayer* g, Vec2 position);	//把Moca的x坐标/图块的宽，y坐标/图块的高算出现在Moca处于tile的第几行第几列
	//void Jump();	//跳跃方法

public:
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
};
//class Moca :public Sprite
//{
//public:
//	enum { right1, left1, right0, left0, jump0, jump1, jump2, fly, swim };
//	CREATE_FUNC(Moca);
//	virtual bool init();
//	Rect getBox();
//	void update(float dt);
//
//	//Vec2 TileCoordForPosition(GameLayer* g, Vec2 position);	//把Moca的x坐标/图块的宽，y坐标/图块的高算出现在Moca处于tile的第几行第几列
//	//void Jump();	//跳跃方法
//
//public:
//	const Vec2 gravity = Vec2(0.f, -100.f);
//	int state;
//	int jumpCount;
//	//Vec2 acce;
//	Sprite* aMoca;
//	Vec2 speed;
//	Vec2 iPos;
//
//};



//class Moca : public Layer
//{
//public:
//	Moca(void);
//	virtual ~Moca(void);
//	virtual void onEnter();
//	void AddSprite();
//	void ChangeAnimation();	//切换动画
//	bool Collision(GameLayer* g, CCPoint position);	//碰撞检测
//	void Logic(GameLayer* g);	//判断碰撞检测
//
//	CCArray * image_array;
//	Sprite* aMoca;
//	float vx, vy;	//x轴和y轴的速度
//	int dir;	//代表方向。2代表右，1代表左,0代表停止
//	int index_1;	//切换动画用
//	int jumpTime;	//跳跃时间
//	string state;	//记录当前状态
//	string canJump;	//标记是否能跳跃
//	bool onLand;	//标记是否处于障碍物之上
//
//	
//	int mode;
//};
#endif


