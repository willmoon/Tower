#ifndef HANDLE_H
#define HANDLE_H
/*
*创建操作层
*该操作层上，左边用于控制角色运动，
*右边由于攻击或其它动作
*其间也还可扩展游戏菜单选项。
*摇杆可以选择是否跟随用户点击
*/

#include "cocos2d.h"

using namespace cocos2d ;

class Handle :public CCLayer
{
public :

	//初始化 point为摇杆中心 radius为摇杆半径 rocker 为摇杆控制点 
	//rocker_bg为摇杆背景 b_follow 为设置是否跟随点击	
	static Handle* HandleWithCenter(CCPoint point,float radius,CCSprite* rocker,
		CCSprite* rocker_bg,bool b_folloe);


	//启动摇杆
	void Active();

	//解除摇杆
	void Inactive();

	//获得触摸方向
	CCPoint GetDirection();

	//获得触摸移动距离
	float GetVelocity();

private :
	CCPoint center_point;//摇杆中心

	CCPoint current_point;//摇杆当前位置

	CCSprite *rocker;

	bool m_bActive;	//是否激活摇杆

	bool m_bFollow;//是否跟随用户点击

	void UpdatePos(float dt);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	CREATE_FUNC(Handle);

};

#endif