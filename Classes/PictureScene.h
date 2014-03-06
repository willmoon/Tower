#ifndef __PICTURESELECT_H__
#define __PICTURESELECT_H__


#include "cocos2d.h"
//#include "cocos-ext.h"
//#include "HelloWorldScene.h"
#include "StartScene.h"
USING_NS_CC;
//USING_NS_CC_EXT;


class PictureSelectScene : public cocos2d::CCScene
{
public:
	bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(PictureSelectScene);

};


class PictureSelectSceneLayer : public cocos2d::CCLayerColor
{
public:
	bool init();
	CREATE_FUNC(PictureSelectSceneLayer);
	CCMenu* pMenu;


private:
	CCMenuItemImage* PlayerWorld;
	CCMenuItemImage*  BossWorld;
	CCMenuItemImage* MarkWorld;
	CCMenuItemImage* pReturnWorld;

	void ReturnCallback(CCObject* pSender);

	void PlayerCallback(CCObject* pSender);
	void BossCallback(CCObject* pSender);
	void MarkCallback(CCObject* pSender);

};


#endif