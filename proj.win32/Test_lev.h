#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "LevelHelper/LevelHelperLoader.h"
#include "Monster.h"
//#include "ContactListener.h"

class Test_lev : public cocos2d ::CCLayer 
{
public:
	bool init();
	~Test_lev(void);

	int i_level;

	CCSize winSize;

	b2World *m_world;

	b2Body *m_pGroundBody;//地面刚体

	LevelHelperLoader *loader;

	LevelHelperLoader *next_loader;

	void setOperating();
	void gotonx();

	CCTouch* m_pTouch;

	CCSprite *left_control;
	CCSprite *right_control;
	CCSprite *jump_control;
	CCSprite *fire_control;

	virtual void registerWithTouchDispatcher();//注册响应触笔事件
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	cocos2d ::CCLayer *operating_layer;
	//MyContactListener *contactListener;

	bool left_pressed;
	bool right_pressed;
	bool jump_pressed;
	bool fire_pressed;

	bool _bjumped;

	bool lock;
	bool run_schedule;

	void updateHero();

	void setViewpointCenter(cocos2d::CCPoint position);

	void update(float dt);
	void for_run (float dt);
	void temp(float dt);

	Monster *tem_monster;
	CREATE_FUNC(Test_lev);
};

