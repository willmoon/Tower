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
	int _iState;//1Ϊ��ֹ״̬��2Ϊ����״̬��3�������ߣ�4��������
	bool _bAlive;
	bool _bJumped;
};

