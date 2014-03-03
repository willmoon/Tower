#ifndef HANDLE_H
#define HANDLE_H
/*
*����������
*�ò������ϣ�������ڿ��ƽ�ɫ�˶���
*�ұ����ڹ�������������
*���Ҳ������չ��Ϸ�˵�ѡ�
*ҡ�˿���ѡ���Ƿ�����û����
*/

#include "cocos2d.h"

using namespace cocos2d ;

class Handle :public CCLayer
{
public :

	//��ʼ�� pointΪҡ������ radiusΪҡ�˰뾶 rocker Ϊҡ�˿��Ƶ� 
	//rocker_bgΪҡ�˱��� b_follow Ϊ�����Ƿ������	
	static Handle* HandleWithCenter(CCPoint point,float radius,CCSprite* rocker,
		CCSprite* rocker_bg,bool b_folloe);


	//����ҡ��
	void Active();

	//���ҡ��
	void Inactive();

	//��ô�������
	CCPoint GetDirection();

	//��ô����ƶ�����
	float GetVelocity();

private :
	CCPoint center_point;//ҡ������

	CCPoint current_point;//ҡ�˵�ǰλ��

	CCSprite *rocker;

	bool m_bActive;	//�Ƿ񼤻�ҡ��

	bool m_bFollow;//�Ƿ�����û����

	void UpdatePos(float dt);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	CREATE_FUNC(Handle);

};

#endif