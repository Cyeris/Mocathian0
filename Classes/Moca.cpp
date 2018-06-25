#include "Moca.h"
extern float tTime;
bool Moca::init()
{
	aMoca = Sprite::create("Moca.png");
	aMoca->setScale(0.3f);
	aMoca->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(aMoca);
	flySpeed = 300;
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

bool Moguru::init()
{
	isparty = 0;
	moguru = Sprite::create("image/moguru/32IMG00000.png");
	moguru->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(moguru);



	return true;
}

//void Moguru::follow()
//{
//
//
//}
