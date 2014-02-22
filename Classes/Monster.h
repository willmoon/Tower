#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"

class Monster
{
public:
	Monster(void);
	~Monster(void);
public:
	cocos2d::CCSprite *monster_sprite;

	bool m_bisalive;

	int type;
	int x;
	int y;

	b2Body *monster_body;
	b2BodyDef monsterBodyDef;
	b2PolygonShape monster_shape;
	b2FixtureDef monster_fixDef;
	b2Fixture *monster_fixture;

	cocos2d::CCSpriteBatchNode *monster_batch;

	float step_pace_no;//¶¯»­ÆµÂÊ
	int monster_stadus;

	cocos2d::CCAnimate *walk_action;
	cocos2d::CCAction *die_action;
	int monster_step_count;
	int monster_cover;//Ñ²Âß·¶Î§
	int monster_speed;

	bool flag;

};

