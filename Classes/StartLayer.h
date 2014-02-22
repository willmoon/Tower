#ifndef __START_LAYER_H__
#define __START_LAYER_H__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
//#include "Reachability.h"
//#include "GameScene.h"
//#include "LevelScene.h"
class StartLayer : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// a selector callback
	void StartChallengeBtnCB(CCObject* pSender); //挑战模式游戏
	void StartConquerBtnCB(CCObject* pSender); //关卡模式游戏
	void StartNetBtnCB(CCObject* pSender); //局域网模式游戏
	void MusicBtnCB(CCObject* pSender); //

	// implement the "static node()" method manually
	CREATE_FUNC(StartLayer);
};

#endif
