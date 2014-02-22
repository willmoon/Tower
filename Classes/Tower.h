#ifndef __TOWER__
#define __TOWER__

#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "Hero.h"
#include "Monster.h"
#include <map>
#include <list>
#include <vector>
#include "tinyxml.h"
#include "Defines.h"
#include "ContactListener.h"

struct monster_data
{
	int type;
	float x;
	float y;

};

class Tower : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	////////////////////////////////////////////////
	b2World *m_world;
	LevelHelperLoader *loader;

	LevelHelperLoader *next_loader;

	Hero *m_pHero;

	bool lock;

	//关卡设置图
	//map<int,list<monster_data>*> monsters_home;

	//tower里面敌人组织图
	map<int,list<Monster *>> m_pTowerMonsters;

	//float m_fDepth; // 深度
	int m_iLevel;

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
	MyContactListener *contactListener;

	bool left_pressed;
	bool right_pressed;
	bool jump_pressed;
	bool fire_pressed;

	bool run_schedule;
	static void initMonstersList();

	void updateHero();
	void for_run(float dt);
	void setViewpointCenter(CCPoint position);
	void dieCallBack(CCNode* pSender);
	void addMonster(monster_data monster,int num);
	void createMonster(monster_data  monster);
	void setLevel(int iLevel); // 关卡模式，读取关卡
	void update(float dt);
	void monster_set_status();

	void afterHit();

	void loadingProgress(float progressValue);

	void monster_patrol(float dt);

	void gotonx();

	void hurted(CCObject* pSender);
	// implement the "static node()" method manually
	CREATE_FUNC(Tower);
protected:
	~Tower();
};

#endif /* defined(__Deepest__Sea__) */
