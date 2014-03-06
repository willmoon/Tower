#ifndef __START_LAYER_H__
#define __START_LAYER_H__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Defines.h"
#include "MarkScene.h"
#include "PictureScene.h"
#include "Loading.h"


class StartLayer : public cocos2d::CCLayer
{
public:
	
	virtual bool init();  

    void quit(CCObject* pSender);

	void start(CCObject* pSender);

	void shop(CCObject* pSender);

	void set(CCObject* pSender);

	
	CREATE_FUNC(StartLayer);
};

#endif
