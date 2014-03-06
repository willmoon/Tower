#ifndef __MarkSCENE_H__
#define __MarkSCENE_H__
#include "cocos2d.h"

USING_NS_CC;


class MarkScene : public cocos2d::CCScene
{
public:
	bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(MarkScene);

};


class MarkSceneLayer : public cocos2d::CCLayerColor
{
public:
	bool init();
	CREATE_FUNC(MarkSceneLayer);
	CCMenu* pMenu;


private:

	CCMenuItemImage* pReturnWorld;
	void ReturnCallback(CCObject* pSender);

	CCMenuItemImage* Button_1;
	CCMenuItemImage* Button_2;
	CCMenuItemImage* Button_3;

	CCMenuItemImage* BuyItem1_1;
	CCMenuItemImage* BuyItem1_2;
	CCMenuItemImage* BuyItem1_3;

	CCMenuItemImage* BuyItem2_1;
	CCMenuItemImage* BuyItem2_2;
	CCMenuItemImage* BuyItem2_3;

	CCMenuItemImage* BuyItem3_1;
	CCMenuItemImage* BuyItem3_2;
	CCMenuItemImage* BuyItem3_3;

	CCSprite* NoBuy1_1;
	CCSprite* NoBuy1_2;
	CCSprite* NoBuy1_3;

	CCSprite* NoBuy2_1;
	CCSprite* NoBuy2_2;
	CCSprite* NoBuy2_3;

	CCSprite* NoBuy3_1;
	CCSprite* NoBuy3_2;
	CCSprite* NoBuy3_3;


	CCLayer *layer1 ;
	CCLayer *layer2;
	CCLayer *layer3;

	void Button_1Callback(CCObject* pSender);
	void Button_2Callback(CCObject* pSender);
	void Button_3Callback(CCObject* pSender);

	void BuyItem1_1Callback(CCObject* pSender);
	void BuyItem1_2Callback(CCObject* pSender);
	void BuyItem1_3Callback(CCObject* pSender);

	void BuyItem2_1Callback(CCObject* pSender);
	void BuyItem2_2Callback(CCObject* pSender);
	void BuyItem2_3Callback(CCObject* pSender);

	void BuyItem3_1Callback(CCObject* pSender);
	void BuyItem3_2Callback(CCObject* pSender);
	void BuyItem3_3Callback(CCObject* pSender);


	void BackToPic(CCObject* pSender);

	CCLabelTTF* CoinTotal;

	CCSprite* w[4];
	CCSprite* upcoinw[4];
	CCLabelTTF* pLabelw[4];

	CCSprite* f[4];
	CCSprite* upcoinf[4];
	CCLabelTTF* pLabelf[4];

	CCSprite* d[4];
	CCSprite* upcoind[4];
	CCLabelTTF* pLabeld[4];



};


#endif
