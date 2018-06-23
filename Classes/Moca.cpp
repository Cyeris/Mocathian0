#include "Moca.h"
extern float tTime;
bool Moca::init()
{
	aMoca = Sprite::create("Moca.png");
	aMoca->setScale(0.3f);
	aMoca->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(aMoca);
	//this->setAnchorPoint(Vec2(0.5, 0));
	flySpeed = 300;
	runSpeed = 500;
	runAcce = 1000;


	return true;
}
//Rect Moca::getBox(Vec2 pos) {
//	return;
//}
Rect Moca::getBox()
{
	//����Ҫ����Χ�п��-2����λ�������ĵ㲻��  
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

	//Vec2 diff = this->iPos- this->getPosition(); //��ҵ�ǰ������Ŀ�ĵصĲ��  
	////Rect returnBoundingBox = Tools::CCRectOffset(Box, diff.x, diff.y); //������������ײ��,����Χ��x,y�᷽�����ƶ�diff.x, diff.y����λ  
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
					//log("r-");
				}
				if (speed.x < -10)
				{
					speed = speed + gravity * dt + Vec2(800, 0)*dt;
					//log("r+");
				}
				if (speed.x >= -10 && speed.x <= 10)
				{
					speed.x = 0;
					speed = speed + gravity * dt;
					//log("%f", speed.x);

				}
		}
		




		//switch (state)
		//{
		//case right0:

		//	if (speed.x > 10)
		//	{
		//		speed = speed + gravity * dt + Vec2(-800, 0)*dt;
		//		//log("r-");
		//	}
		//	if (speed.x < -10)
		//	{
		//		speed = speed + gravity * dt + Vec2(800, 0)*dt;
		//		//log("r+");
		//	}
		//	if (speed.x >= -10 && speed.x <= 10)
		//	{
		//		speed.x = 0;
		//		speed = speed + gravity * dt;
		//		//log("%f", speed.x);

		//	}
		//	break;
		//case right1:
		//	if (speed.x < runSpeed)
		//	{
		//		speed = speed + gravity * dt + Vec2(runAcce, 0)*dt;
		//	}
		//	if (speed.x >= runSpeed)
		//	{
		//		speed = speed + gravity * dt;
		//	}
		//	break;
		//case left0:
		//	if (speed.x > 10)
		//	{
		//		speed = speed + gravity * dt + Vec2(-800, 0)*dt;
		//	}
		//	if (speed.x < -10)
		//	{
		//		speed = speed + gravity * dt + Vec2(800, 0)*dt;
		//	}
		//	if (speed.x >= -10 && speed.x <= 10)
		//	{
		//		speed.x = 0;
		//		speed = speed + gravity * dt;
		//	}
		//	break;
		//case left1:
		//	if (speed.x > -runSpeed)
		//	{
		//		speed = speed + gravity * dt + Vec2(-runAcce, 0)*dt;
		//	}
		//	if (speed.x <= -runSpeed)
		//	{
		//		speed = speed + gravity * dt;
		//	}
		//	break;

		//default:
		//	log("era");
		//	break;
		//}
	}
	iPos=this->getPosition() + speed * dt;
	/*if (true)
	{
		this->setPosition(iPos);
	}*/
	
}



//Moca::Moca(void)
//{
//	this->vx = 4.0f;
//	this->vy = 0;
//	this->dir = right0;
//	this->index_1 = 0;
//	this->jumpTime = 0;
//	this->state = "rightstop";
//	this->canJump = "--";
//}
//
//
//Moca::~Moca(void)
//{
//}
//
//
//void Moca::onEnter()
//{
//	/*CCLayer::onEnter();
//
//	image_array = CCArray::create();
//	image_array->retain();
//
//	image_array->addObject(CCSpriteFrame::create("Moca1.png", CCRectMake(0, 0, 16, 31)));
//	image_array->addObject(CCSpriteFrame::create("Moca2.png", CCRectMake(0, 0, 16, 31)));
//	image_array->addObject(CCSpriteFrame::create("Moca3.png", CCRectMake(0, 0, 16, 31)));
//
//	this->AddSprite();*/
//}
//
//
//
//void Moca::AddSprite()
//{
//	aMoca = Sprite::create("Moca.png");
//	this->addChild(s);
//}
//
//
//void Moca::ChangeAnimation()
//{
//	//���state�����ַ�r
//	if (state.find("r") == 0)
//	{
//		this->s->setScaleX(1);
//	}
//	else
//	{
//		this->s->setScaleX(-1);
//	}
//
//	//��ֹ״̬
//	if (strcmp(state.c_str(), "rightstop") == 0 && strcmp(canJump.c_str(), "jumping") != 0 ||
//		strcmp(state.c_str(), "leftstop") == 0 && strcmp(canJump.c_str(), "jumping") != 0)
//	{
//		this->s->setDisplayFrame((CCSpriteFrame*)this->image_array->objectAtIndex(0));
//	}
//
//	//��Ծ״̬
//	else if (strcmp(canJump.c_str(), "jumping") == 0)
//	{
//		this->s->setDisplayFrame((CCSpriteFrame*)this->image_array->objectAtIndex(2));
//	}
//
//	//�ƶ�״̬
//	else
//	{
//		this->s->setDisplayFrame((CCSpriteFrame*)this->image_array->objectAtIndex(index_1));
//		index_1++;
//		if (index_1 > 1)
//		{
//			index_1 = 0;
//		}
//	}
//
//}
//
//
//void Moca::Move(GameLayer* g, float angle)
//{
//	if (angle == 0)
//	{
//		//�������ƶ���ʱ���ж���һ��״̬���ұ߻������
//		if (strcmp(state.c_str(), "right") == 0)
//		{
//			this->state = "rightstop";
//		}
//		else if (strcmp(state.c_str(), "left") == 0)
//		{
//			this->state = "leftstop";
//		}
//		this->dir = 0;
//		return;
//	}
//	else
//	{
//		angle = (float)angle / 3.1415926535898f * 180;
//
//		//�ұ�
//		if (angle > -90 && angle < 90)
//		{
//			this->dir = 2;
//			this->state = "right";
//		}
//		//���
//		else
//		{
//			this->dir = 1;
//			this->state = "left";
//		}
//	}
//}
//
//
//bool Moca::Collision(GameLayer* g, CCPoint position)
//{
//	//1�����Moca����tile��ͼ�ļ��м���
//	CCPoint point = this->TileCoordForPosition(g, position);
//
//	//����60�С�����60�еĲ���
//	if (point.x > 59) return false;
//
//	//2����ȡgidֵ
//	int tileGid = g->meta->tileGIDAt(point);
//
//	if (tileGid)
//	{
//		//3������gidֵ����CCDictionary����
//		CCDictionary *properties = g->map->propertiesForGID(tileGid);
//		if (properties)
//		{
//			//4����ȡCCDictionary����ļ�
//			const CCString *collision = properties->valueForKey("red");
//
//			//5����ȡ����ֵ�����Ϊ�棬������ײ
//			if (collision && collision->compare("true") == 0)
//			{
//				return true;
//			}
//		}
//	}
//	return false;
//}
//
//
//CCPoint Moca::TileCoordForPosition(GameLayer* g, CCPoint position)
//{
//	int x = position.x / g->map->getTileSize().width;
//
//	// ��tile������ * tile��һ��ͼ��ĸ߶ȣ�Ҳ����16�� - Moca��y���� ��/ 16
//	int y = ((g->map->getMapSize().height * g->map->getTileSize().height) - position.y) / g->map->getTileSize().height;
//	return ccp(x, y);
//}
//
//
//void Moca::Jump()
//{
//	if (strcmp(canJump.c_str(), "jumping") != 0)
//	{
//		this->canJump = "jumping";
//		this->jumpTime = 11;
//		this->yspeed = 11.0f;
//	}
//}
//
//
//void Moca::Logic(GameLayer* g)
//{
//	this->onLand = false;
//
//	switch (dir)
//	{
//		//���
//	case 1:
//		if (this->Collision(g, ccp(this->getPosition().x - 12, this->getPosition().y)) == false)//������������
//		{
//			this->setPositionX(this->getPositionX() - this->xspeed);
//		}
//		break;
//
//		//�ұ�
//	case 2:
//		if (this->Collision(g, ccp(this->getPosition().x + 8, this->getPosition().y)) == false)
//		{
//			this->setPositionX(this->getPositionX() + this->xspeed);
//		}
//		break;
//
//		//ֹͣ
//	case 0:
//		break;
//	}
//
//	//Խ������
//	if (this->getPositionX() + 8 >= 960)
//	{
//		this->setPositionX(960 - 8);
//	}
//
//	//�ϱ�
//	if (this->Collision(g, ccp(this->getPosition().x - 7, this->getPosition().y + 15.5f)) == true ||
//		this->Collision(g, ccp(this->getPosition().x + 7, this->getPosition().y + 15.5f)) == true)
//	{
//		this->jumpTime = 0;
//	}
//
//	//�±�
//	if (this->Collision(g, ccp(this->getPosition().x - 4, this->getPosition().y - 15.5f)) == true ||
//		this->Collision(g, ccp(this->getPosition().x + 4, this->getPosition().y - 15.5f)) == true)
//	{
//		onLand = true;
//		this->canJump = "--";
//		if (this->jumpTime <= 0)
//		{
//			this->yspeed = 0;
//			CCPoint point = this->TileCoordForPosition(g, this->getPosition());
//
//			//�������� - ��ǰ��������*16 - 1 ��-1����ΪMocaͼƬ�ĸ߶���31��
//			this->setPositionY((20 - point.y) * 16 - 1);
//		}
//	}
//
//	//�ж���Ծ��������
//	if (this->jumpTime > 0)
//	{
//		this->canJump = "jumping";
//		this->setPositionY(this->getPositionY() + this->yspeed);
//		if (this->yspeed > 0)
//		{
//			this->yspeed--;
//		}
//		this->jumpTime--;
//	}
//	else if (!onLand && jumpTime <= 0)
//	{
//		this->canJump = "jumping";
//		this->setPositionY(this->getPositionY() - this->yspeed);
//		if (this->yspeed < 11)
//		{
//			this->yspeed++;
//		}
//	}
//}


