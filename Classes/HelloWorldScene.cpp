
#include "SimpleAudioEngine.h"
#include "Chapter1.h"
#include "game.h"

using namespace CocosDenshion;
Scene* HelloWorld::createScene()
{
	Scene* scene = Scene::createWithPhysics();
		scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = HelloWorld::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);
	return scene;
}
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	h_Repeat = 1;

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	/// 카메라 ////////////////////
	setCamera();
	/// 잡것 //////////////////////
	//auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

	//auto edgeNode = Node::create();
	//edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100));
	//edgeNode->setPhysicsBody(edgeBody);

	//this->addChild(edgeNode);
	setKeyListener();
	setMath();
	/// 배경  /////////////////////
	setBackGround();
	setItem();
	setAnimation();
	setClear();
	/// 캐릭터 ///////////////////
	setCharacter();
	setUI();

	// 생명
	setHeart();
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	/// 수집 젤리, 점수/////////
	Collecting_Cake = Label::createWithTTF("0 / 800", "fonts/NanumBarun/NanumBarun.ttf", 24);
	Collecting_Cake->setPosition(83, 525);
	this->addChild(Collecting_Cake);

	/// 젤리 ///////////////////
	for (int i = 0; i < 2000; i++)
		isAddChildCake[i] = false;
	chapte1_S1();

	scheduleUpdate();
	this->schedule(schedule_selector(HelloWorld::MoveCake_Stick), 1.0f / 60.0f);

	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	return true;
}
void HelloWorld::update(float dt)
{
	////follow_Camera->setPosition(follow_Camera->getPositionX() + 4.0f, 360);
	//this->runAction(camera);
	/// 케이크, 장애물 //////////
	Collecting_Cake->setString(StringUtils::format("%d / %d", i_Collecting_Cake, Max_Collecting_Cake));
	Collecting_Coin->setString(StringUtils::format("Coin : %d", i_Collecting_Coin));
	//	EatCake();
	//	CrashHurdle();
	/// 배경 반복 /////////
	float x1 = backGround1->getPositionX();
	float x2 = backGround2->getPositionX();

	if (x2 < 0)
	{
		x1 = x2;
		x2 = x1 + backGround1->getContentSize().width;
	}

	backGround1->setPosition(x1 - 10.0f, 0);
	backGround2->setPosition(x2 - 10.0f, 0);

	/// 플레이어 점프, 슬라이딩 /////////

	Condition_Process();
	B_time -= dt;
	opacity_time -= dt;
	if (A_Scale >= 0.8f)
		A_time -= dt;

	JumpProcess();

	if (isSlide && direction == 0)
	{
		C_1->setRotation(270);
		C_1->setPosition(C_1->getPositionX(), y - 70);
	}
	else
	{
		C_1->setRotation(0);
		C_1->setPosition(C_1->getPositionX(), y);
	}

}
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_Z)
	{
		if (n_JumpCount < 2)
		{
			DoJump();
			isJump = true;
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_X)
	{
		isSlide = true;
		C_animation(4);
	}
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_X)
	{
		isSlide = false;
		C_animation(1);
	}
}

bool HelloWorld::onContactBegin(PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	for (int i = 0; _Stick1[i] != NULL; i++)
	{
		if ((1 == a->getCollisionBitmask() && 200000 + i == b->getCollisionBitmask()) ||
			(200000 + i == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
		{
			isCrush = true;
		}
	}
	for (int i = 0; Hurdle[i] != NULL; i++)
	{
		if (isHurdle[i] == true && Alice_Condition == 1)
		{
			if ((1 == a->getCollisionBitmask() && i + 3 == b->getCollisionBitmask()) ||
				(i + 3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
			{
				Heart[NowHeart]->setTexture(CCTextureCache::sharedTextureCache()->addImage(StringUtils::format("Texture/Object/Heart/None_Heart.png")));
				Hurdle[i]->getPhysicsBody()->removeFromWorld();
				if (Hurdle[i]->getTag() == 2)
					h_Repeat = 2;
				for (int j = 0; j < h_Repeat; j++)
				{
					Hurdle[i + j]->setOpacity(127);
					isHurdle[i + j] = false;
					if (j == h_Repeat)
						i += j;
				}
				h_Repeat = 1;

				Alice_Condition = 3;
				B_time = 0.6f;

				NowHeart--;
				if (NowHeart == -1)
					Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, HelloWorld::createScene()));
			}
		}
	}
	for (int i = 0; cake[i] != NULL; i++)
	{
		if (isCake[i] == true)
		{
			if ((1 == a->getCollisionBitmask() && i + 10000 == b->getCollisionBitmask()) ||
				(i + 10000 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
			{
				if(cake[i]->getTag() == 1)
					i_Collecting_Cake += 1;
				if (cake[i]->getTag() == 2)
					i_Collecting_Coin += 1;

				cake[i]->setVisible(false);
				isCake[i] = false;
				cake[i]->getPhysicsBody()->removeFromWorld();

				if (cake[i]->getTag() >= 3)
				{
					for (int j = 3; j < 8; j++)
					{
						if (cake[i]->getTag() == j)
						{
							isFiver[j - 3] = true;
							Fiver[j - 3]->setVisible(true);
						}
					}
					for (int l = 0; l < 5; l++)
						if (isFiver[l] == true)
							i_Fiver += 1;
					if (i_Fiver >= 5)
					{
						FiverTime = 5.0f;
						isFiver[5] = true;
					}
					i_Fiver = 0;
				}
			}
		}
	}
	for (int i = 0; item[i] != NULL; i++)
	{
		if (isItem[i] == true)
		{
			if ((1 == a->getCollisionBitmask() && i + 20000 == b->getCollisionBitmask()) ||
				(i + 20000 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
			{
				switch (item[i]->getTag())
				{
				case bigger:
					item[i]->setVisible(false);
					isItem[i] = false;
					Alice_Condition = 2;
					A_time = 5.0f;
					break;
				case teemo:
					item[i]->setVisible(false);
					isItem[i] = false;
					TeemoTime = 15.0f;
					Teemo->setVisible(true);
					break;
				case fast:
					item[i]->setVisible(false);
					isItem[i] = false;
					if (SlowTime >= 0.0f)
						SlowTime = 5.0f;
					FastTime = 5.0f;
					speed = -1200;
					if (Alice_Condition != 2)
						Alice_Condition = 4;
					break;
				case slow:
					item[i]->setVisible(false);
					isItem[i] = false;
					if (FastTime >= 0.0f)
						FastTime = 5.0f;
					SlowTime = 5.0f;
					speed = -300;
					break;
				}
				item[i]->getPhysicsBody()->removeFromWorld();
			}
		}
	}
	if (1 == a->getCollisionBitmask() && 100000 == b->getCollisionBitmask() ||
		100000 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask())
	{
		Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5f, HelloWorld::createScene()));
	}
	return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* _event)
{
	/// jump_Slide //////////
	if (slide_Button->getBoundingBox().containsPoint(touch->getLocation()))
	{
		slide_Button->setTexture(Director::getInstance()->getTextureCache()->addImage("Texture/Object/UI/p_SlideButton.png"));
		isSlide = true;
	}
	if (jump_Button->getBoundingBox().containsPoint(touch->getLocation()))
	{
		jump_Button->setTexture(Director::getInstance()->getTextureCache()->addImage("Texture/Object/UI/p_JumpButton.png"));
		if (n_JumpCount < 2)
			DoJump();
	}
	/// 팝업창 /////////
	if (stop_Button->getBoundingBox().containsPoint(touch->getLocation()))
	{
		stop_BackGround->setVisible(true);
		SimpleAudioEngine::getInstance()->playEffect("btClick.wav", false);
		Director::getInstance()->getScheduler()->pauseTarget(this);
		C_1->stopAllActions();
	}
	if (stop_BackGround->isVisible())
	{
		if (option->getBoundingBox().containsPoint(touch->getLocation()))
		{
			option->setTexture(Director::getInstance()->getTextureCache()->addImage("Texture/Object/UI/p_option.png"));
			SimpleAudioEngine::getInstance()->playEffect("btClick.wav", false);
		}
		if (resume->getBoundingBox().containsPoint(touch->getLocation()))
		{
			resume->setTexture(Director::getInstance()->getTextureCache()->addImage("Texture/Object/UI/p_Resume.png"));
			SimpleAudioEngine::getInstance()->playEffect("btClick.wav", false);
		}
		if (rePlay->getBoundingBox().containsPoint(touch->getLocation()))
		{
			rePlay->setTexture(Director::getInstance()->getTextureCache()->addImage("Texture/Object/UI/p_rePlay.png"));
			SimpleAudioEngine::getInstance()->playEffect("btClick.wav", false);
		}
		if (stop->getBoundingBox().containsPoint(touch->getLocation()))
		{
			stop->setTexture(Director::getInstance()->getTextureCache()->addImage("Texture/Object/UI/p_stop.png"));
			SimpleAudioEngine::getInstance()->playEffect("btClick.wav", false);
		}
	}
	CCLOG("%f, %f", touch->getLocation().x, touch->getLocation().y);
	return true;
}
void HelloWorld::onTouchMoved(Touch* touch, Event* _event)
{

}
void HelloWorld::onTouchEnded(Touch* touch, Event* _event)
{
	slide_Button->setTexture(Director::getInstance()->getTextureCache()->addImage("Texture/Object/UI/SlideButton.png"));
	jump_Button->setTexture(Director::getInstance()->getTextureCache()->addImage("Texture/Object/UI/JumpButton.png"));
	isSlide = false;

	if (stop_BackGround->isVisible())
	{
		resume->setTexture(Director::getInstance()->getTextureCache()->addImage("Texture/Object/UI/resume.png"));
		rePlay->setTexture(Director::getInstance()->getTextureCache()->addImage("Texture/Object/UI/rePlay.png"));
		stop->setTexture(Director::getInstance()->getTextureCache()->addImage("Texture/Object/UI/stop.png"));
		option->setTexture(Director::getInstance()->getTextureCache()->addImage("Texture/Object/UI/option.png"));
		if (resume->getBoundingBox().containsPoint(touch->getLocation()))
		{

			stop_BackGround->setVisible(false);
			Director::getInstance()->getScheduler()->resumeTarget(this);

			C_animation(1);
		}
		if (rePlay->getBoundingBox().containsPoint(touch->getLocation()))
		{
			Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5f, HelloWorld::createScene()));
		}
		if (stop->getBoundingBox().containsPoint(touch->getLocation()))
		{
			Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5f, New::NewScene()));
		}
	}
}
