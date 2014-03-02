#ifndef __TOWER__
#define __TOWER__

#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "Hero.h"
#include "LevelHelper/LevelHelperLoader.h"
#include "Monster.h"
#include <map>
#include <list>
#include <vector>
#include "tinyxml.h"
#include "Defines.h"
#include "ContactListener.h"
#include "HRocker.h"

struct monster_data
{
	int type;
	float x;
	float y;

};

class Tower : public cocos2d::CCLayer
{
public:
	virtual bool init();

	b2World *m_world;
	LevelHelperLoader *loader;
	LevelHelperLoader *next_loader;

	b2Body *m_pGroudBody;

	Hero *m_pHero;

	bool lock;

	//tower里面敌人图
	map<int,list<Monster *>> m_pTowerMonsters;

	int m_iLevel;

	void set_operating();

	void set_hero();

	HRocker *rocker;	//控制摇杆

	cocos2d ::CCLayer *operating_layer;
	MyContactListener *contactListener;

	static void initMonstersList();

	void updateHero();
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

	void gotonx(float dt);

	void normalstate(CCNode* pSender);
	CREATE_FUNC(Tower);
protected:
	~Tower();
};

#endif 