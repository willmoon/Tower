#pragma once
#include "LevelHelper/LevelHelperLoader.h"
class Hero
{
public:
	Hero(void);
	~Hero(void);

	LHSprite *_pSprite; 
	b2Body *_pBody;
	int _iSpeed;
	int _iState;//1为静止状态，2为受伤状态，3向左行走，4向右行走
	bool _bAlive;
	bool _bJumped;
};

