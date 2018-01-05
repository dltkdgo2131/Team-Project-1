#include"HelloWorldScene.h"
#define WIDTH 60
#define FPS 1.0f / 60.0f

void HelloWorld::MoveCake_Stick(float dt)
{
	static float c_MoveTime = 0.0f;
	static float s_MoveTime = 0.0f;

	//	CCLOG("%f", cake[i]->getPositionX());

	//StickNode[i]->setPosition(Point(_Stick1[i]->getPosition()));
	_clear->runAction(MoveBy::create(FPS, Vec2(speed / 60, 0)));
	for (int i = 0; _Stick1[i] != nullptr; i++)
	{
		_Stick1[i]->runAction(MoveBy::create(FPS, Vec2(speed / 60, 0)));
		if (_Stick1[i]->getPositionX() <= 1300 && _Stick1[i]->getPositionX() > 0)
		{
			if (!(_Stick1[i]->isVisible() == true))
			{
				StickBody = PhysicsBody::createBox(_Stick1[i]->getContentSize(), PhysicsMaterial(0, 0, 0));
				StickBody->setGravityEnable(false);
				StickBody->setCollisionBitmask(200000 + i);
				StickBody->setContactTestBitmask(true);
				_Stick1[i]->setPhysicsBody(StickBody);
				_Stick1[i]->setVisible(true);
			}
		}
		else if(_Stick1[i]->getPositionX() <= -1300)
			if (_Stick1[i]->isVisible())
			{
				_Stick1[i]->getPhysicsBody()->removeFromWorld();
				_Stick1[i]->setVisible(false);
			}
	}
	for (int i = 0; cake[i] != nullptr; i++)
	{
		cake[i]->runAction(MoveBy::create(FPS, Vec2(speed / 60, 0)));
		if (cake[i]->getPositionX() <= 1300 && cake[i]->getPositionX() > 0)
		{
			if (isCake[i] == true && !(cake[i]->isVisible()))
			{
				CakeBody = PhysicsBody::createCircle(cake[i]->getContentSize().width / 3, PhysicsMaterial(0, 0, 0));
				CakeBody->setDynamic(false);
				CakeBody->setCollisionBitmask(10000 + i);
				CakeBody->setContactTestBitmask(true);
				cake[i]->setPhysicsBody(CakeBody);
				cake[i]->setVisible(true);
			}
		}
		else if (cake[i]->getPositionX() <= 0)
			if (isCake[i] == true && cake[i]->isVisible())
			{
				cake[i]->getPhysicsBody()->removeFromWorld();
				cake[i]->setVisible(false);
			}
	}
	for (int i = 0; Hurdle[i] != nullptr; i++)
	{
		Hurdle[i]->runAction(MoveBy::create(FPS, Vec2(speed / 60, 0)));
		if (Hurdle[i]->getPositionX() <= 1400
			&& Hurdle[i]->getPositionX() > 0)
		{
			if (isHurdle[i] == true && !(Hurdle[i]->isVisible()))
			{
				switch (Hurdle[i]->getTag())
				{
				case 1:
					MyBodyParser::getInstance()->parseJsonFile("Collider/Table_Chair.json");
					T_CBody = MyBodyParser::getInstance()->bodyFormJson(Hurdle[i], "Table_Chair", PhysicsMaterial(0, 0, 0));

					T_CBody->setDynamic(false);
					T_CBody->setCollisionBitmask(i + 3);
					T_CBody->setContactTestBitmask(true);

					Hurdle[i]->setPhysicsBody(T_CBody);
					break;
				case 2:
					MyBodyParser::getInstance()->parseJsonFile("Collider/Spider.json");
					SpiderBody = MyBodyParser::getInstance()->bodyFormJson(Hurdle[i], "Spider", PhysicsMaterial(0, 0, 0));

					SpiderBody->setDynamic(false);
					SpiderBody->setCollisionBitmask(i + 3);
					SpiderBody->setContactTestBitmask(true);
					Hurdle[i]->setPhysicsBody(SpiderBody);
					break;
				case 3:
				case 4:
					MyBodyParser::getInstance()->parseJsonFile("Collider/bat.json");
					BatBody = MyBodyParser::getInstance()->bodyFormJson(Hurdle[i], "bat", PhysicsMaterial(0, 0, 0));

					BatBody->setDynamic(false);
					BatBody->setCollisionBitmask(i + 3);
					BatBody->setContactTestBitmask(true);
					Hurdle[i]->setPhysicsBody(BatBody);
					break;
				}
				Hurdle[i]->setVisible(true);
			}
		}
		else if (Hurdle[i]->getPositionX() <= -50)
			if (isHurdle[i] == true && Hurdle[i]->isVisible())
			{
				Hurdle[i]->getPhysicsBody()->removeFromWorld();
				Hurdle[i]->setVisible(false);
			}

		if (Hurdle[i]->getTag() == 2)
		{
			if (Hurdle[i]->getPositionX() <= 1500
				&& Hurdle[i]->getPositionX() >= 0)
				set_Action(i);
			i++;
		}
		if (Hurdle[i]->getTag() == 3)
		{
			if (Hurdle[i]->getPositionX() <= 1500
				&& Hurdle[i]->getPositionX() >= 0)
				Action_Vat(i, case_Bat);
		}
		if (Hurdle[i]->getTag() == 4)
		{
			if (Hurdle[i]->getPositionX() <= 1900
				&& Hurdle[i]->getPositionX() >= 0)
				Action_Vat(i, 3);
		}
	}
	for (int i = 0; item[i] != nullptr; i++)
	{
		item[i]->runAction(MoveBy::create(FPS, Vec2(speed / 60, 0)));
		if (item[i]->getPositionX() <= 1300 && item[i]->getPositionX() > 0)
		{
			if (isItem[i] == true && !(item[i]->isVisible()))
			{
				MyBodyParser::getInstance()->parseJsonFile("Collider/bigger.json");
				ItemBody = MyBodyParser::getInstance()->bodyFormJson(item[i], "bigger", PhysicsMaterial(0, 0, 0));
				ItemBody->setDynamic(false);
				ItemBody->setCollisionBitmask(20000 + i);
				ItemBody->setContactTestBitmask(true);
				item[i]->setPhysicsBody(ItemBody);
				item[i]->setVisible(true);
			}
		}
		else if (item[i]->getPositionX() <= 0)
			if (isItem[i] == true && item[i]->isVisible())
			{
				item[i]->getPhysicsBody()->removeFromWorld();
				item[i]->setVisible(false);
			}
	}
	s_MoveTime += dt;

	//	EatItem();
	if (TeemoTime <= 0.0f)
	{
		if (TeemoTime >= -0.1f)
			Teemo->runAction(FadeOut::create(0.5f));
	}
	else
		Action_Teemo();
	if (FastTime <= 0.0f && FastTime >= -0.015f)
	{
		speed = -600.0f;
	}
	else if (FastTime <= -3.0f && FastTime >= -3.015f)
		if (Alice_Condition == 4)
			Alice_Condition = 1;

	if (SlowTime <= 0.0f && SlowTime >= -0.015f)
		speed = -600;
	else if (FastTime <= -3.0f && FastTime >= -3.015f)
		Alice_Condition = 1;
	if (isFiver[5] == true)
	{
		FiverTime -= dt;
		speed = -1200;
	}

	FastTime -= dt;
	SlowTime -= dt;
	TeemoTime -= dt;
	//	_Stick1[i]->setPosition(_Stick1[i]->getPositionX() - 20.0f, 0);
}
void HelloWorld::basicCake(int Repeat)
{
	for (int j = 0; j < Repeat; j++)
	{
		for (int i = lastCakeArr; i < 5 + lastCakeArr; i++)
		{
			cake[i] = Sprite::create("Texture/Object/Cake/Cake.png");
			cake[i]->setTag(1);
			cake[i]->setScale(0.6f);
			cake[i]->setPosition(1400 + (WIDTH * i), 250);
			cake[i]->setVisible(false);
			isCake[i] = true;

			this->addChild(cake[i], 5);
		}
		lastCakeArr += 5;
	}
}
void HelloWorld::JumpCake()
{
	int Height = 0;
	for (int i = lastCakeArr; i < 6 + lastCakeArr; i++)
	{
		cake[i] = Sprite::create("Texture/Object/Cake/Cake.png");
		cake[i]->setTag(1);
		cake[i]->setScale(0.6f);
		cake[i]->setPosition(1400 + (WIDTH * i), 250 + (70 * Height));
		cake[i]->setVisible(false);
		isCake[i] = true;
		if (i < 2 + lastCakeArr) Height++;
		else if (i > 2 + lastCakeArr) Height--;
		this->addChild(cake[i], 5);
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Texture/Object/Hurdle/Chapter1/bat.plist");
	Hurdle[CountHurdle] = Sprite::createWithSpriteFrameName("bat_1.png");
	Bat_ani = Animation::create();
	Bat_ani->setDelayPerUnit(0.1f);

	for (int j = 1; j <= 4; j++)
		Bat_ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("bat_%d.png", j)));
	Bat_anim = Animate::create(Bat_ani);
	Hurdle[CountHurdle]->runAction(RepeatForever::create(Bat_anim));
	//		Hurdle[i] = Sprite::create("Texture/Object/Hurdle/Chapter1/bat_1.png");
	Hurdle[CountHurdle]->setScale(1.0f, 1.0f);
	Hurdle[CountHurdle]->setTag(4);
	Hurdle[CountHurdle]->setAnchorPoint(Point(0.5f, 0.5f));
	Hurdle[CountHurdle]->setRotation(-45);
	Hurdle[CountHurdle]->setPosition(1400 + (WIDTH * (lastCakeArr + 2.2f)), 1200);
	Hurdle[CountHurdle]->setVisible(false);
	isHurdle[CountHurdle] = true;

	this->addChild(Hurdle[CountHurdle], 5);
	//item[CountItem] = Sprite::create("Texture/Object/Item/Slow_Item.png");
	//item[CountItem]->setScale(0.5f);
	//item[CountItem]->setPosition(1400 + (WIDTH * (lastCakeArr + 3)), 250);
	//item[CountItem]->setTag(3);
	//item[CountItem]->setVisible(false);
	//isItem[CountItem] = true;

	//this->addChild(item[CountItem]);
	CountHurdle += 1;
	lastCakeArr += 6;
}
void HelloWorld::JumpTwoCake() {
	int Height = 0;
	for (int i = lastCakeArr; i < 10 + lastCakeArr; i++)
	{
		if (4 + lastCakeArr > i && i < 5 + lastCakeArr)
		{
			cake[i] = Sprite::create("Texture/Object/Item/Gold_Coin.png");
			cake[i]->setTag(2);
		}
		else 
		{
			cake[i] = Sprite::create("Texture/Object/Cake/Cake.png");
			cake[i]->setTag(1);
		} 
		cake[i]->setScale(0.6f);
		cake[i]->setPosition(1400 + (WIDTH * i), 300 + (70 * Height));
		cake[i]->setVisible(false);
		isCake[i] = true;
	

		if (i < 4 + lastCakeArr) Height++;
		else if (i > 4 + lastCakeArr)Height--;

		this->addChild(cake[i], 5);
	}
	Hurdle[CountHurdle] = Sprite::create("Texture/Object/Hurdle/Chapter1/Table_Chair.png");
	Hurdle[CountHurdle]->setPosition(1450 + WIDTH * (lastCakeArr + 4) - 30, 300);
	Hurdle[CountHurdle]->setScale(1.0f, 1.0f);
	Hurdle[CountHurdle]->setTag(1);
	Hurdle[CountHurdle]->setVisible(false);
	Hurdle[CountHurdle]->setAnchorPoint(Point(0.5, 0.5));
	//Hurdle[CountHurdle]->getBoundingBox().setRect(0, 0, Hurdle[CountHurdle]->getContentSize().width / 2, Hurdle[CountHurdle]->getContentSize().height / 2);

	//MyBodyParser::getInstance()->parseJsonFile("Collider/Table_Chair.json");
	//T_CBody = MyBodyParser::getInstance()->bodyFormJson(Hurdle[CountHurdle], "Table_Chair", PhysicsMaterial(0, 0, 0));

	//T_CBody->setDynamic(false);
	//T_CBody->setCollisionBitmask(CountHurdle);
	//T_CBody->setContactTestBitmask(true);
	//Hurdle[CountHurdle]->setPhysicsBody(T_CBody);

	isHurdle[CountHurdle] = true;
	this->addChild(Hurdle[CountHurdle]);
	CountHurdle++;
	lastCakeArr += 10;
}
void HelloWorld::basicStick()
{

	for (int i = 0 + lastStickArr; i < 10 + lastStickArr; i++)
	{
		_Stick1[i] = Sprite::create("Texture/Object/Stick/1_Stick.png");
		_Stick1[i]->setAnchorPoint(Point(0, 0));
		_Stick1[i]->setScale(1.0f, 1.2f);
		_Stick1[i]->setVisible(false);
		_Stick1[i]->setPosition((_Stick1[i]->getContentSize().width * i), 0);


		this->addChild(_Stick1[i], 2);
		CCLOG("%f", _Stick1[i]->getContentSize().height);
	}
	lastStickArr += 10;

}
void HelloWorld::SlideCake()
{
	for (int i = 0 + lastCakeArr; i < 8 + lastCakeArr; i++)
	{
		cake[i] = Sprite::create("Texture/Object/Cake/Cake.png");
		cake[i]->setTag(1);
		cake[i]->setScale(0.6f);
		cake[i]->setPosition(1400 + (WIDTH * i), 200);
		cake[i]->setVisible(false);
		isCake[i] = true;

		this->addChild(cake[i], 5);
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Texture/Object/Hurdle/Chapter1/Spider_1.plist");
	Hurdle[CountHurdle] = Sprite::createWithSpriteFrameName("Spider_1.png");
	Spider_ani = Animation::create();
	Spider_ani->setDelayPerUnit(0.4f);
	for (int i = 1; i <= 2; i++)
		Spider_ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("Spider_%d.png", i)));
	Spider_anim = Animate::create(Spider_ani);
	Hurdle[CountHurdle]->runAction(RepeatForever::create(Spider_anim));
	Hurdle[CountHurdle]->setScale(1.0f, 0.85f);
	Hurdle[CountHurdle]->setTag(2);
	Hurdle[CountHurdle]->setAnchorPoint(Point(0.5, 0.5));
	Hurdle[CountHurdle]->setPosition(1420 + (WIDTH * (lastCakeArr + 2.0f)), 332.5);
	Hurdle[CountHurdle]->setVisible(false);
	Hurdle[CountHurdle + 1] = Sprite::create("Texture/Object/Hurdle/Chapter1/Spider_Rain.png");

	Hurdle[CountHurdle + 1]->setPosition(0, 600);
	Hurdle[CountHurdle + 1]->setScaleY(0.85f);
	Hurdle[CountHurdle + 1]->setAnchorPoint(Point(0.0f, 1.0f));
	Hurdle[CountHurdle]->addChild(Hurdle[CountHurdle + 1], -1);
	h_Rect[CountHurdle] = Hurdle[CountHurdle]->getBoundingBox();
	//MyBodyParser::getInstance()->parseJsonFile("Collider/Spider.json");
	//SpiderBody = MyBodyParser::getInstance()->bodyFormJson(Hurdle[CountHurdle],"Spider", PhysicsMaterial(0,0,0));
	//
	//SpiderBody->setDynamic(false);
	//SpiderBody->setCollisionBitmask(CountHurdle);
	//SpiderBody->setContactTestBitmask(true);
	//Hurdle[CountHurdle]->setPhysicsBody(SpiderBody);
	isHurdle[CountHurdle] = true;
	this->addChild(Hurdle[CountHurdle], 5);
	CountHurdle += 2;
	lastCakeArr += 8;
}
void HelloWorld::VatCake()
{
	for (int i = 0 + lastCakeArr; i < 20 + lastCakeArr; i++)
	{
		cake[i] = Sprite::create("Texture/Object/Cake/Cake.png");
		cake[i]->setTag(1);
		cake[i]->setScale(0.6f);
		cake[i]->setPosition(1400 + (WIDTH * i), 200);
		cake[i]->setVisible(false);
		isCake[i] = true;

		this->addChild(cake[i], 5);
	}


	for (int i = 0 + CountHurdle; i <= 6 + CountHurdle; i++)
	{

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Texture/Object/Hurdle/Chapter1/bat.plist");
		Hurdle[i] = Sprite::createWithSpriteFrameName("bat_1.png");
		Bat_ani = Animation::create();
		Bat_ani->setDelayPerUnit(0.1f);

		for (int j = 1; j <= 4; j++)
			Bat_ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("bat_%d.png", j)));
		Bat_anim = Animate::create(Bat_ani);
		Hurdle[i]->runAction(RepeatForever::create(Bat_anim));
		//		Hurdle[i] = Sprite::create("Texture/Object/Hurdle/Chapter1/bat_1.png");
		Hurdle[i]->setScale(1.0f, 1.0f);
		Hurdle[i]->setTag(3);
		Hurdle[i]->setAnchorPoint(Point(0.5f, 0.5f));
		Hurdle[i]->setRotation(-45);
		Hurdle[i]->setPosition(1400 + (WIDTH * (lastCakeArr + 1.0f) + (150 * (i - CountHurdle))), 900);
		Hurdle[i]->setVisible(false);
		isHurdle[i] = true;
		case_Bat = 2;
		for (int l = 0; l < 2; l++)
		{
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Texture/Object/Hurdle/Chapter1/bat.plist");
			tempHurdle[l] = Sprite::createWithSpriteFrameName("bat_1.png");
			Bat_ani = Animation::create();
			Bat_ani->setDelayPerUnit(0.1f);

			for (int j = 1; j <= 4; j++)
				Bat_ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("bat_%d.png", j)));
			Bat_anim = Animate::create(Bat_ani);
			tempHurdle[l]->runAction(RepeatForever::create(Bat_anim));
			tempHurdle[l]->setPosition(50, 200 + (100 * l));
			Hurdle[i]->addChild(tempHurdle[l]);
		}
		this->addChild(Hurdle[i], 5);
	}
	//Hurdle[CountHurdle] = Sprite::create("Texture/Object/Hurdle/Chapter1/bat_1.png");
	//Hurdle[CountHurdle]->setPosition(1450 + WIDTH * (lastCakeArr + 4) - 30, 300);
	//Hurdle[CountHurdle]->setScale(1.0f, 1.0f);
	//Hurdle[CountHurdle]->setTag(3);
	//Hurdle[CountHurdle]->setVisible(false);
	//Hurdle[CountHurdle]->setAnchorPoint(Point(0.5, 0.5));
	//isHurdle[CountHurdle] = true;
	//this->addChild(Hurdle[CountHurdle]);
	CountHurdle += 7;
	lastCakeArr += 20;

}
void HelloWorld::biggerCake()
{

	for (int i = 0 + lastCakeArr; i < 30 + lastCakeArr; i++)
	{
		cake[i] = Sprite::create("Texture/Object/Cake/Cake.png");
		cake[i]->setTag(1);
		cake[i]->setScale(0.6f);
		cake[i]->setPosition(1400 + (WIDTH * i), 200);
		cake[i]->setVisible(false);
		isCake[i] = true;

		this->addChild(cake[i], 5);
	}
	for (int i = 0 + CountHurdle; i < 10 + CountHurdle; i += 2)
	{
		int i_origin = (i - CountHurdle) / 2 + CountHurdle;
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Texture/Object/Hurdle/Chapter1/Spider_1.plist");
		Hurdle[i] = Sprite::createWithSpriteFrameName("Spider_1.png");
		Spider_ani = Animation::create();
		Spider_ani->setDelayPerUnit(0.4f);
		for (int j = 1; j <= 2; j++)
			Spider_ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("Spider_%d.png", j)));
		Spider_anim = Animate::create(Spider_ani);
		Hurdle[i]->runAction(RepeatForever::create(Spider_anim));
		Hurdle[i]->setScale(1.0f, 0.85f);
		Hurdle[i]->setTag(2);
		Hurdle[i]->setAnchorPoint(Point(0.5, 0.5));
		Hurdle[i]->setPosition(1550 + (WIDTH * (lastCakeArr + 2.0f) + (250 * (i_origin - CountHurdle))), 332.5);
		Hurdle[i]->setVisible(false);
		Hurdle[i + 1] = Sprite::create("Texture/Object/Hurdle/Chapter1/Spider_Rain.png");

		Hurdle[i + 1]->setPosition(0, 600);
		Hurdle[i + 1]->setScaleY(0.85f);
		Hurdle[i + 1]->setAnchorPoint(Point(0.0f, 1.0f));
		Hurdle[i]->addChild(Hurdle[i + 1], -1);
		isHurdle[i] = true;
		this->addChild(Hurdle[i], 5);
	}
	item[CountItem] = Sprite::create("Texture/Object/Item/Bigger.png");
	item[CountItem]->setPosition(1400 + (WIDTH * lastCakeArr), 482.5);
	item[CountItem]->setScale(0.5f, 0.5f);
	item[CountItem]->setTag(0);
	item[CountItem]->setVisible(false);
	isItem[CountItem] = true;
	this->addChild(item[CountItem], 5);
	CountItem += 1;
	CountHurdle += 10;
	lastCakeArr += 30;
}
void HelloWorld::TeemoCake()
{
	for (int i = 0 + lastCakeArr; i < 20 + lastCakeArr; i++)
	{
		cake[i] = Sprite::create("Texture/Object/Cake/Cake.png");
		cake[i]->setTag(1);
		cake[i]->setScale(0.6f);
		cake[i]->setPosition(1400 + (WIDTH * i), 200);
		cake[i]->setVisible(false);
		isCake[i] = true;

		this->addChild(cake[i], 5);
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0 + CountItem; j < 7 + CountItem; j++)
		{
			int j_origin = j - CountItem;
			item[(i * 7) + j] = Sprite::create("Texture/Object/Item/Teemo_Item.png");
			item[(i * 7) + j]->setPosition(1400 + (WIDTH * (lastCakeArr + 1)) + (150 * j_origin), 382.5 - (100 * i));
			item[(i * 7) + j]->setScale(0.5f, 0.5f);
			item[(i * 7) + j]->setTag(1);
			item[(i * 7) + j]->setRotation(90);
			item[(i * 7) + j]->setVisible(false);
			isItem[(i * 7) + j] = true;
			this->addChild(item[(i * 7) + j], 5);
		}
	}
	CountItem += 14;
	lastCakeArr += 20;
}
void HelloWorld::FastCake()
{
	int Height = 0;
	//int C_random = (rand() % 2) + 1;
	item[CountItem] = Sprite::create("Texture/Object/Item/Teemo_Item.png");
	item[CountItem]->setPosition(1300 + (WIDTH * (lastCakeArr + 1)), 200);
	item[CountItem]->setScale(0.5f, 0.5f);
	item[CountItem]->setTag(2);
	item[CountItem]->setVisible(false);
	isItem[CountItem] = true;
	//switch (C_random)
	//{
	//case 1:
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0 + lastCakeArr; i < 20 + lastCakeArr; i++)
		{
			cake[(j * 20) + i] = Sprite::create("Texture/Object/Cake/Cake.png");
			cake[(j * 20) + i]->setTag(1);
			cake[(j * 20) + i]->setScale(0.6f);
			cake[(j * 20) + i]->setPosition(1400 + (WIDTH * (i + j * 20)), 250 + 35 * Height);
			cake[(j * 20) + i]->setVisible(false);
			isCake[(j * 20) + i] = true;

			if (i < 8 + lastCakeArr) Height++;
			if (i > 11 + lastCakeArr) Height--;
			this->addChild(cake[(j * 20) + i]);
		}
	}

	/*	break;*/
	//case 2:
	//for (int i = 0 + CountHurdle; i < 18 + CountHurdle; i += 2)
	//{
	//	int i_origin = (i - CountHurdle) / 2 + CountHurdle;
	//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Texture/Object/Hurdle/Chapter1/Spider_1.plist");
	//	Hurdle[i] = Sprite::createWithSpriteFrameName("Spider_1.png");
	//	Spider_ani = Animation::create();
	//	Spider_ani->setDelayPerUnit(0.4f);
	//	for (int j = 1; j <= 2; j++)
	//		Spider_ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("Spider_%d.png", j)));
	//	Spider_anim = Animate::create(Spider_ani);
	//	Hurdle[i]->runAction(RepeatForever::create(Spider_anim));
	//	Hurdle[i]->setScale(1.0f, 0.85f);
	//	Hurdle[i]->setTag(2);
	//	Hurdle[i]->setAnchorPoint(Point(0.5, 0.5));
	//	Hurdle[i]->setPosition(1550 + (WIDTH * (lastCakeArr + 2.0f) + (250 * (i_origin - CountHurdle))), 332.5);
	//	Hurdle[i]->setVisible(false);
	//	Hurdle[i + 1] = Sprite::create("Texture/Object/Hurdle/Chapter1/Spider_Rain.png");

	//	Hurdle[i + 1]->setPosition(0, 600);
	//	Hurdle[i + 1]->setScaleY(0.85f);
	//	Hurdle[i + 1]->setAnchorPoint(Point(0.0f, 1.0f));
	//	Hurdle[i]->addChild(Hurdle[i + 1], -1);
	//	isHurdle[i] = true;
	//	this->addChild(Hurdle[i], 5);
	//}

	//break;
	//}


	this->addChild(item[CountItem]);
	//	CountHurdle += 20;
	lastCakeArr += 40;
	CountItem += 1;
}
void HelloWorld::FiverCake()
{
	
	int Fiver = 0;
	for (int j = 0; j < 5; j++)
	{
		int Height = 0;
		for (int i = lastCakeArr; i < 6 + lastCakeArr; i++)
		{
			if (i >= 2 + lastCakeArr && i <= 3 + lastCakeArr)
			{
				cake[i] = Sprite::create(StringUtils::format("Texture/Object/UI/Fiver_%d.png", j + 1));
				cake[i]->setTag(j + 3);
			}
			else
			{
				cake[i] = Sprite::create("Texture/Object/Cake/Cake.png");
				cake[i]->setTag(1);
			}
			cake[i]->setScale(0.6f);
			cake[i]->setPosition(1400 + (WIDTH * i), 250 + (70 * Height));
			cake[i]->setVisible(false);
			isCake[i] = true;
			if (i < 2 + lastCakeArr) Height++;
			else if (i > 2 + lastCakeArr) Height--;
			this->addChild(cake[i], 5);
		}
		lastCakeArr += 6;
	}
}
void HelloWorld::EatItem()
{
	for (int i = 0; item[i] != NULL; i++)
	{

	}
	C_1->setTag(1);
}
void HelloWorld::EatCake()
{
	for (int i = 0; cake[i] != NULL; i++)
	{
		if (C_1->getBoundingBox().intersectsRect(cake[i]->getBoundingBox()) && isCake[i])
		{
			cake[i]->setVisible(false);
			i_Collecting_Cake += 1;
			isCake[i] = false;
		}
	}

}
void HelloWorld::CrashHurdle()
{
	for (int i = 0; Hurdle[i] != NULL; i++)
	{
		if (h_Rect[i].intersectsRect(C_1->getBoundingBox()) && isHurdle[i])
		{
			Heart[NowHeart]->setTexture(CCTextureCache::sharedTextureCache()->addImage(StringUtils::format("Texture/Object/Heart/None_Heart.png")));
			Hurdle[i]->setOpacity(127);
			isHurdle[i] = false;
			i_Collecting_Cake += 1;
			if (NowHeart != 0)
				NowHeart--;
		}
	}
}
bool HelloWorld::LocalToWorldPosition(Node* pSender, Point point)
{
	Point o = pSender->getParent()->convertToWorldSpace(pSender->boundingBox().origin);
	Rect rect = CCRectMake(o.x, o.y, pSender->boundingBox().size.width, pSender->boundingBox().size.height);
	return rect.containsPoint(point);
}
void HelloWorld::set_Action(int index)
{
	MoveBy *move1 = MoveBy::create(FPS, Vec2(0, 71.85f / 60));
	MoveBy *move2 = MoveBy::create(FPS, Vec2(0, -(71.85f / 60)));
	if (direc[index] == 1)
	{
		Hurdle[index]->runAction(move1);
		Hurdle[index + 1]->runAction(move2);
	}
	else if (direc[index] == 2)
	{
		Hurdle[index]->runAction(move2);
		Hurdle[index + 1]->runAction(move1);
	}
	if (direc[index] == 1)
	{
		if (Hurdle[index + 1]->getScaleY() <= 0.85f)
			direc[index] = 2;
		else
			Hurdle[index + 1]->setScaleY(Hurdle[index + 1]->getScaleY() - 0.15f / 60);

	}
	else if (direc[index] == 2)
	{
		if (Hurdle[index + 1]->getScaleY() >= 1.0f)
			direc[index] = 1;
		else
			Hurdle[index + 1]->setScaleY(Hurdle[index + 1]->getScaleY() + 0.15f / 60);

	}
	CCLOG("%f %d", Hurdle[index + 1]->getScaleY(), direc[index]);
	//Sequence* seq1 = Sequence::create(scale1, scale2, NULL);
	//Hurdle[index + 1]->runAction(seq1);
	//MoveBy *move = MoveBy::create(0.5f, Vec2(0, 100));
	//Sequence* seq2 = Sequence::create(move, move->reverse(), NULL);
	//Hurdle[index]->runAction(seq2);
}
void HelloWorld::Action_Teemo()
{
	static int condition = 0;
	static int m_condition = 0;
	if (condition == 0)
	{
		Teemo->setOpacity(Teemo->getOpacity() + 1.0f);
		if (Teemo->getOpacity() >= 254.0f)
			condition = 1;
	}
	else if (condition == 1)
	{
		Teemo->setOpacity(Teemo->getOpacity() - 1.0f);
		if (Teemo->getOpacity() <= 177.0f)
			condition = 0;
	}
	if (m_condition == 0)
	{
		Teemo->setPosition(Teemo->getPosition().x + 1.0f, Teemo->getPosition().y + 2.0f);
		if (Teemo->getPosition().y >= 0)
			m_condition = 1;
	}
	if (m_condition == 1)
	{
		Teemo->setPosition(Teemo->getPosition().x + 1.0f, Teemo->getPosition().y - 2.0f);
		if (Teemo->getPosition().y <= -200)
			m_condition = 2;
	}
	if (m_condition == 2)
	{
		Teemo->setPosition(Teemo->getPosition().x - 2.0f, Teemo->getPosition().y);
		if (Teemo->getPosition().x <= -200.0)
			m_condition = 0;
	}
	CCLOG("%f", Teemo->getPosition().y);
}
void HelloWorld::Action_Vat(int index, int _case)
{
	switch (_case)
	{
	case 1:
		if (Hurdle[index]->getPosition().y <= 720)
			Hurdle[index]->setRotation(Hurdle[index]->getRotation() + 0.6f);
		if (bat_Direc[index] == 1)
		{

			Hurdle[index]->setPosition(Hurdle[index]->getPosition().x, Hurdle[index]->getPosition().y - 5.0f);
			if (Hurdle[index]->getPosition().y <= 275)
				bat_Direc[index] = 2;
		}
		if (bat_Direc[index] == 2)
		{
			Hurdle[index]->setPosition(Hurdle[index]->getPosition().x, Hurdle[index]->getPosition().y + 6.0f);
		}
		break;
	case 2:

		if (bat_Direc[index] == 1)
		{
			Hurdle[index]->setPosition(Hurdle[index]->getPosition().x, -500);
			Hurdle[index]->setRotation(-20);
			bat_Direc[index] = 2;
		}
		if (bat_Direc[index] == 2)
		{
			Hurdle[index]->setRotation(Hurdle[index]->getRotation() + 0.5f);
			Hurdle[index]->setPosition(Hurdle[index]->getPosition().x, Hurdle[index]->getPosition().y + 7.0f);
			if (Hurdle[index]->getPosition().y >= 300)
				bat_Direc[index] = 3;
		}
		if (bat_Direc[index] == 3)
		{
			Hurdle[index]->setRotation(Hurdle[index]->getRotation() - 1.0f);
		}
		break;
	case 3:
		if (Hurdle[index]->getPosition().y <= 720)
			Hurdle[index]->setRotation(Hurdle[index]->getRotation() + 0.5f);
		if (bat_Direc[index] == 1)
		{
			Hurdle[index]->setPosition(Hurdle[index]->getPosition().x, Hurdle[index]->getPosition().y - 8.0f);
			if (Hurdle[index]->getPosition().y <= 270)
				bat_Direc[index] = 2;
		}
		if (bat_Direc[index] == 2)
		{
			Hurdle[index]->setPosition(Hurdle[index]->getPosition().x, Hurdle[index]->getPosition().y - 1.0f);
			if (Hurdle[index]->getPosition().y <= 200)
				bat_Direc[index] = 3;
		}
		if (bat_Direc[index] == 3)
		{
			Hurdle[index]->setPosition(Hurdle[index]->getPosition().x, Hurdle[index]->getPosition().y + 6.0f);
		}
	}
}