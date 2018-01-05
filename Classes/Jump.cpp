#include"HelloWorldScene.h"
#include "cocos2d.h"

USING_NS_CC;
#define FPS 1 / 60
void HelloWorld::DoJump()
{
	C_animation(2);
	direction = 1;
	isCrush = false;
	gravity = jump_Speed;
	n_JumpCount++;
}
void HelloWorld::JumpProcess()
{
	switch (direction)
	{
	case 0:
		if (y > y_base)
			y = y_base;
		if (isJump == true)
		{
			isJump = false;
			if (isSlide == false)
				C_animation(1);
		}
		else if (y == y_base)//&& C_1->getBoundingBox().intersectsCircle(Stick)
			n_JumpCount = 0;
		break;
	case 1:
		y += gravity;
		if (gravity <= 0.0f)
		{
			direction = 2;
		}
		else
		{
			gravity -= jump_accell;
		}
		break;
	case 2:
		y -= gravity;
		//if (y > y_base)
		//	gravity += jump_accell;
		if (isCrush == false)
			gravity += jump_accell;
		else
		{
			direction = 0;
		}
		break;
	} 
}
void HelloWorld::Condition_Process()
{

	switch (Alice_Condition)
	{
	case 1:
		C_1->setScale(A_Scale);
		A_time = 0;
		break;
	case 2:
		if (y < y_base)
			y = y_base;
		if (A_time <= 0.0f)
		{
			C_1->setScale(A_Scale);
			C_1->setTag(2);
			B_time -= 0.1f;
			A_Scale -= 0.01f;
			y_base -= 1.5f;
		}
		if (A_Scale <= 0.8f && C_1->getTag() == 1)
		{
			C_1->setScale(A_Scale + 0.01f);
			B_time -= 0.1f;
			A_Scale += 0.01f;
			y_base += 1.5f;
		}
		else if (A_Scale >= 0.8f)
		{
			C_1->setScale(A_Scale + 0.01f);
		}
		else if (A_Scale <= 0.5f)
		{
			if (FastTime >= 0.0f)
				Alice_Condition = 4;
			else
				Alice_Condition = 1;

			y_base = 220.0f;
		}


		//else if (A_time <= 0 && C_1->getScale() > 0.4f)
		//	C_1->setScale(C_1->getScale() - 0.1f);
		//else
		//	Alice_Condition = 1;
		break;
	case 3:
		if (sub_Condition == 1)
		{
			C_animation(3);
			sub_Condition = 2;
		}
		else if (B_time > 0.0f)
			A_opacity();
		else if (B_time <= 0.0f)
		{
			C_1->setOpacity(255);
			Alice_Condition = 1;
			sub_Condition = 1;
			if (isSlide)
				C_animation(4);
			else if (direction == 0)
				C_animation(1);
			else if (direction == 1 || direction == 2)
				C_animation(2);

		}
	case 4:
		break;
	default:
		break;
	}
}
void HelloWorld::C_animation(int Select)
{
	if (sub_Condition != 2)
	{
		C_1->stopAllActions();
		switch (Select)
		{
		case 1:
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Texture/Character/Character_1.plist");
			C_ani_1 = Animation::create();
			C_ani_1->setDelayPerUnit(0.05f);

			for (int i = 1; i <= 6; i++)
				C_ani_1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("run-%d.png", i)));

			C_anim_1 = Animate::create(C_ani_1);
			C_1->runAction(RepeatForever::create(C_anim_1));
			break;
		case 2:
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Texture/Character/Character_Jump_1.plist");
			C_ani_1 = Animation::create();
			C_ani_1->setDelayPerUnit(0.08f);

			for (int i = 1; i <= 10; i++)
				C_ani_1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("jump_%d.png", i)));

			C_anim_1 = Animate::create(C_ani_1);
			C_1->runAction(RepeatForever::create(C_anim_1));
			break;
		case 3:
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Texture/Character/Character_Damage_1.plist");
			C_ani_2 = Animation::create();
			C_ani_2->setDelayPerUnit(0.2f);

			for (int i = 1; i <= 3; i++)
				C_ani_2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("Damage_%d.png", i)));

			C_anim_2 = Animate::create(C_ani_2);
			C_1->runAction(C_anim_2);
			break;
			//	C_animation(1);
		case 4:
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Texture/Character/Character_Slide_1.plist");
			C_ani_1 = Animation::create();
			C_ani_1->setDelayPerUnit(0.05f);

			for (int i = 1; i <= 3; i++)
				C_ani_1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("Slide_%d.png", i)));

			C_anim_1 = Animate::create(C_ani_1);
			C_1->runAction(RepeatForever::create(C_anim_1));
			break;
		}
	}
}
void HelloWorld::A_opacity()
{
	if (opacity_time <= 0.0f)
	{
		opacity_time = 0.08f;
		if (C_1->getOpacity() == 127)
			C_1->setOpacity(255);
		else
			C_1->setOpacity(127);
	}
}
//void HelloWorld::_jump(Ref* pSender)
//{
//	if (n_JumpCount < 2)
//		DoJump();
//}
//void HelloWorld::_slide(Ref* pSender) 
//{ 
//	isSlide = true;
//}