#ifndef __PLAYERSCENE_H__
#define __PLAYERSCENE_H__
#include "cocos2d.h"
//#include "cocos-ext.h"
#include "PictureScene.h"

USING_NS_CC;
//USING_NS_CC_EXT;


class PlayerScene : public cocos2d::CCScene
{
public:
	bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(PlayerScene);

};


class PlayerSceneLayer : public cocos2d::CCLayerColor
{
public:
	bool init();
	CREATE_FUNC(PlayerSceneLayer);
	CCMenu* pMenu;


private:

	CCMenuItemImage* pReturnWorld;
	void ReturnCallback(CCObject* pSender);

	CCLabelTTF* CoinTotal;
	CCLabelTTF* CoinUsed;

	//animate
	 void Animate(int type);
	 CCSprite*  PlayerAnimate; 
	 int     PlayerLock[8]; 

	 void initplayer(int type);

	 CCMenuItemImage *upw ;
	 CCMenuItemImage *upw1 ;
	 CCMenuItemImage *upw2 ;
	 CCMenuItemImage *upw3 ;

	 void UpCallback(CCObject* pSender);

	 void ShowInf_f();
	 CCLabelTTF* F_Lv;
	 CCLabelTTF* F_Life;
	 CCLabelTTF* F_Defense;
	 CCLabelTTF* F_Attack;
	 CCLabelTTF* F_Combo;

	 int power2(int n);

	


};


#endif
