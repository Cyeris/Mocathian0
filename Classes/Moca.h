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

	//Vec2 TileCoordForPosition(GameLayer* g, Vec2 position);	//��Moca��x����/ͼ��Ŀ�y����/ͼ��ĸ��������Moca����tile�ĵڼ��еڼ���
	//void Jump();	//��Ծ����

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
//	//Vec2 TileCoordForPosition(GameLayer* g, Vec2 position);	//��Moca��x����/ͼ��Ŀ�y����/ͼ��ĸ��������Moca����tile�ĵڼ��еڼ���
//	//void Jump();	//��Ծ����
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
//	void ChangeAnimation();	//�л�����
//	bool Collision(GameLayer* g, CCPoint position);	//��ײ���
//	void Logic(GameLayer* g);	//�ж���ײ���
//
//	CCArray * image_array;
//	Sprite* aMoca;
//	float vx, vy;	//x���y����ٶ�
//	int dir;	//������2�����ң�1������,0����ֹͣ
//	int index_1;	//�л�������
//	int jumpTime;	//��Ծʱ��
//	string state;	//��¼��ǰ״̬
//	string canJump;	//����Ƿ�����Ծ
//	bool onLand;	//����Ƿ����ϰ���֮��
//
//	
//	int mode;
//};
#endif


