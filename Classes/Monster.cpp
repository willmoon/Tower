#include "Monster.h"

Monster::Monster(void)
{
	monster_sprite =NULL;
	m_bisalive=true;
	monster_body =NULL;

	monster_fixture =NULL;

	monster_stadus =1;//初始化为1，1代表巡逻
	step_pace_no=0.2f;

	walk_action =NULL;
	die_action =NULL;
	monster_cover =10;

	monster_step_count=0;
	monster_speed =-40;
	flag=true;
}

//Monster 的构造函数中并没有动态分配内存，在析构函数中该做什么？
Monster::~Monster(void)
{
	CCLOG("---------Monster的析构函数");

	monster_sprite =NULL;
	
	monster_body =NULL;

	monster_fixture =NULL;

	walk_action =NULL;

	die_action =NULL;
}

