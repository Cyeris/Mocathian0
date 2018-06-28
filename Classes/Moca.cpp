#include "Moca.h"
#include <cmath>
extern float tTime;
float getRandom() {
	random_device rd;
	float rdx = (rd() % 100 + 1);
	//log("%f", rdx/100);
	return rdx/100;
}
bool Moca::init()
{
	aMoca = Sprite::create("Moca.png");
	aMoca->setScale(0.3f);
	aMoca->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(aMoca);
	flySpeed = 400;
	runSpeed = 500;
	runAcce = 1000;
	return true;
}

Rect Moca::getBox()
{
	Rect Box = aMoca->boundingBox();
	//Vec2 nowPos= this->getPosition();
	//Size mSize = aMoca->getContentSize();
	//log("MS:%f %f", mSize.width, mSize.height);
	Box.origin.x = iPos.x - 0.5*Box.size.width;
	Box.origin.y = iPos.y - 0.5*Box.size.height;
	Box.origin.x += 2;
	Box.size.width -= 4;
	Box.origin.y += 2;
	Box.size.height -= 4;

	//Vec2 diff = this->iPos- this->getPosition(); //玩家当前距离与目的地的差距  
	////Rect returnBoundingBox = Tools::CCRectOffset(Box, diff.x, diff.y); //计算调整后的碰撞盒,即包围盒x,y轴方向上移动diff.x, diff.y个单位  
	//Box.origin.x += diff.x;
	//Box.origin.y += diff.y;
	//log("Box:%f %f", Box.origin.x, Box.origin.y);
	return Box;
}
void Moca::enableFly() {
	flyMode = 1;
	gravity.y = 0;
}
void Moca::update(float dt)
{
	if (flyMode)
	{
		speed = Vec2(0, 0);
		if (isA)
		{
			speed.x -= flySpeed;
		}
		if (isD)
		{
			speed.x += flySpeed;
		}
		if (isW)
		{
			speed.y += flySpeed;
		}
		if (isS)
		{
			speed.y -= flySpeed;
		}
	}
	else {
		if (lefting)
		{
			if (speed.x > -runSpeed)
			{
				speed = speed + gravity * dt + Vec2(-runAcce, 0)*dt;
			}
			if (speed.x <= -runSpeed)
			{
				speed = speed + gravity * dt;
			}
		}
		else if (righting) {
			if (speed.x < runSpeed)
			{
				speed = speed + gravity * dt + Vec2(runAcce, 0)*dt;
			}
			if (speed.x >= runSpeed)
			{
				speed = speed + gravity * dt;
			}
		}
		else
		{
				if (speed.x > 10)
				{
					speed = speed + gravity * dt + Vec2(-800, 0)*dt;
				}
				if (speed.x < -10)
				{
					speed = speed + gravity * dt + Vec2(800, 0)*dt;
				}
				if (speed.x >= -10 && speed.x <= 10)
				{
					speed.x = 0;
					speed = speed + gravity * dt;
				}
		}
		
	}
	iPos=this->getPosition() + speed * dt;
	
}

float Moca::getDt(Vec2 pos)
{
	float deltaY = 0.5*aMoca->boundingBox().size.height;
	float x2 = (getPosition().x - pos.x)*(getPosition().x - pos.x);
	float y2 = (getPosition().y + deltaY - pos.y)*(getPosition().y + deltaY - pos.y);
	//log("%f", pow(x2 + y2, 0.5));
	return pow(x2 + y2, 0.5);
}

bool Moguru::init()
{
	isparty = 0;
	moguru = Sprite::create("image/moguru/moguru0.png");
	moguru->setAnchorPoint(Vec2(0.5, 0));
	//this->addChild(moguru);

	return true;
}
bool Ghost::init()
{
	ghost = Sprite::create("Ghost.png");
	ghost->setScale(2.0f);
	ghost->setOpacity(10);
	ghost->runAction(FadeTo::create(1.0f, 240));
	this->addChild(ghost);

	return true;
}

void Ghost::update(Moca * moca,float dt)
{
	if (moca->faceLeft)
	{
		this->setScaleX(-1);
		if (this->getPosition().x>=moca->getPosition().x)
		{
			speed.x = moca->speed.x - 40;
			if (this->getPosition().y<moca->getPosition().y)
			{
				speed.y = 200;
			}
			else
			{
				speed.y = -200;
			}
		}
		else
		{
			speed = Vec2(0, 0);
		}
	}
	else
	{
		this->setScaleX(1);
		if (this->getPosition().x<=moca->getPosition().x)
		{
			speed.x = moca->speed.x + 40;
			if (this->getPosition().y<moca->getPosition().y)
			{
				speed.y = 200;
			}
			else
			{
				speed.y = -200;
			}
		}
		else
		{
			speed = Vec2(0, 0);
		}
	}
	this->setPosition(this->getPosition()+speed*dt);
}
void Fairy1::update(float dt)
{
	deltaT += dt;
	if (deltaT>=5*dt)
	{
		if (tama.size()<1000)
		{
			auto b = Bullet::createWithSpeed(tamaspeed, 6.28*getRandom());
	
			tama.pushBack(b);
			tama.back()->setPosition(fairy1->getPosition());
			fairy1->addChild(tama.back());
			//log("%d", tama.size());
		}
		deltaT = 0;
	}
	for (auto iter = tama.begin(); iter != tama.end();) {
		(*iter)->setPosition((*iter)->getPosition() + (*iter)->speed*dt);
		iter++;
	}
	//for (auto iter = ghosts.begin(); iter != ghosts.end();)
}

bool Fairy1::init()
{
	deltaT = 0;
	fairy1 = Sprite::create("enemy1.png");
	this->addChild(fairy1);


	return true;
}

Bullet::Bullet()
{
}

Bullet::Bullet(float velo, float angle)
{
	speed.x = velo * cos(angle);
	speed.y = velo * sin(angle);
	this->angle = angle;
	blt = Sprite::create("tama1.png");
	this->addChild(blt);
}

Bullet::~Bullet()
{
	this->removeAllChildren();
	//log("~B");
}

Bullet * Bullet::createWithSpeed(float velo, float angle)
{
	//实例化一个新的对象

	Bullet * pRet = new Bullet(velo, angle);

	//初始化OK后自动释放内存

	if (pRet && pRet->init()) {

		pRet->autorelease();

	}
	else {

		//否则就安全删除

		CC_SAFE_DELETE(pRet);

	}

	return pRet;
}

