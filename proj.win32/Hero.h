#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "LevelHelper/LevelHelperLoader.h"

class Hero
{
public:
	Hero(void);
	~Hero(void);

	cocos2d ::CCSprite *_pSprite; 

	LHSprite *temp_sprite;

	b2Body *_pBody;
	b2BodyDef hero_bodyDef;
	b2PolygonShape hero_shape;
	b2FixtureDef hero_fixDef;
	b2Fixture *_phero_fixture;

	bool run_schedule;
	cocos2d::CCAnimate *hero_walk;
	cocos2d::CCAnimate *hero_attack;
	cocos2d::CCAnimate *hero_jump;
	cocos2d::CCAnimate *hero_hurt;

	int _iSpeed;
	int _iState;//1Ϊ��ֹ״̬��2Ϊ����״̬��3�������ߣ�4��������
	bool _bAlive;
	bool _bJumped;
};

