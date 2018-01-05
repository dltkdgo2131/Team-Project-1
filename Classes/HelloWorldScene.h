#pragma once
#include "cocos2d.h"
#include "MyBodyParser.h"
#include "stdlib.h"
USING_NS_CC;

enum _item { bigger, teemo, fast, slow };
class HelloWorld : public Layer
{
public:
	static Scene* createScene();

	/// etc /////////////////
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	PhysicsBody* SpiderBody;
	PhysicsBody *T_CBody;
	PhysicsBody *StickBody;
	PhysicsBody *CakeBody;
	PhysicsBody *BatBody;
	PhysicsBody *ItemBody;
	PhysicsBody *ClearBody;
	Node* StickNode[10];
	Node* follow_Camera;
	Follow* camera;

	float jumpTime = 0.0f;
	int n_JumpCount = 0;

	/// Rect ////////////////
	Rect c_Rect;
	Rect h_Rect[200];
	Rect ca_Rect;

	/// Score ///////////////
	Label * Collecting_Cake;
	Label * Collecting_Coin;
	int i_Collecting_Cake = 0;
	int Max_Collecting_Cake = 800;
	int i_Collecting_Coin;

	/// Vector //////////////
	Vec2 C_location;// 플레이어 좌표
	Vec2 LastPosition;

	/// bool ////////////////
	bool bIsjump = false;
	bool bIsDown = false;
	bool isJump = false;
	bool isSlide = false;
	bool isCrush;
	///backGround////////////
	int Chapter;
	int Stage;
	Sprite* backGround1;
	Sprite* backGround2;
	/// Sprite //////////////


	Sprite* cake[2000];
	Sprite *_Stick1[200];
	Sprite *Hurdle[2000];
	Sprite *Heart[4];
	Sprite *Fiver[5];

	/// 엘리스 //////////////////
	Sprite* C_1;
	PhysicsBody *C_1Body;
	int Alice_Condition;
	int sub_Condition;
	float A_time;
	float B_time;
	float A_Scale;
	float opacity_time;

	void A_opacity();
	void Condition_Process();
	/// Animation /////////////
	Animation* C_ani_1;
	Animate* C_anim_1;
	Animation* C_ani_2;
	Animate* C_anim_2;
	/// button ////////////////
	//void menuCloseCallback(cocos2d::Ref* pSender);
	/*void _jump(Ref* pSender);*/
	//void _slide(Ref* pSender);

	Sprite* jump_Button;
	Sprite* slide_Button;

	Sprite* stop_Button;
	Sprite* stop_BackGround;
	Sprite* option;
	Sprite* resume;
	Sprite* stop;
	Sprite* rePlay;

	/// 종료시 팝업 ///////////
	Sprite* _clear;
	Sprite* clear_Background;
	Label* goal;

	/// function ////////////
	virtual bool onTouchBegan(Touch* touch, Event* _event);
	virtual void onTouchMoved(Touch* touch, Event* _event);
	virtual void onTouchEnded(Touch* touch, Event* _event);

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	virtual bool init();
	void C_animation(int Select);
	void set_Action(int index);
	void Action_Vat(int index, int _case);

	bool LocalToWorldPosition(Node* pSender, Point point);
	/// Init //////////////////////
	void setCamera();
	void setBackGround();
	void setKeyListener();
	void setCharacter();
	void setHeart();
	void setUI();
	void setAnimation();
	void setMath();
	void setClear();

	/// 발판 , 케이크, 장애물 /////
	Animation* Spider_ani;
	Animate* Spider_anim;
	Sprite* temps;
	Sprite* tempHurdle[2];
	Animation* Bat_ani;
	Animate* Bat_anim;

	Vec2 CakeLocation[2000];

	int direc[2000];
	int bat_Direc[2000];
	bool isCake[2000];
	bool isAddChildCake[2000];
	bool isHurdle[2000];

	int case_Bat;
	int h_Repeat;
	float Delay_Action[1000];

	int MaxHeart = 4;
	int	NowHeart = 3;
	int CountHurdle = 0;
	int CountCake = 0;
	int CakeSection;

	int lastCakeArr = 0;
	int lastStickArr = 0;

	void basicStick();
	void basicCake(int Repeat);
	void JumpCake();
	void JumpTwoCake();
	void VatCake();
	void SlideCake();
	void biggerCake();
	void TeemoCake();
	void EatCake();
	void FastCake();
	void FiverCake();
	void CrashHurdle();

	void update(float dt);
	void MoveCake_Stick(float dt);

	int CollectCake = 0;
	int MaxCake = 0;
	/// item //////////
	int CountItem;
	Sprite *item[200];
	bool isItem[200];
	void EatItem();
	void setItem();

	Sprite *Teemo;
	bool isTeemo;
	float TeemoTime;
	void Action_Teemo();

	float speed;
	float FastTime;

	float SlowTime;

	bool isFiver[6];
	int i_Fiver;
	float FiverTime;

	/// Jump ////////////
	float y = 0.0f;
	float gravity = 0.0f;
	int direction = 0;

	float jump_Speed = 20.0f;
	float jump_accell = 1.25f;
	float y_base = 220.0f;

	void DoJump();
	void JumpProcess();
	/// Chapter /////////
	void chapte1_S1();

	CREATE_FUNC(HelloWorld);

private:
	PhysicsWorld *sceneWorld;
	void SetPhysicsWorld(PhysicsWorld *world) { sceneWorld = world; };
	bool onContactBegin(PhysicsContact &contact);
};