#include "Loading.h"
using namespace cocos2d;

bool Loading::init()
{
	CCSprite *loading=CCSprite::create("ui/loading.png");
	loading ->setPosition(ccp(WINSIZE.width/2,WINSIZE.height/2));
	addChild(loading,102,1020);

	scheduleOnce (schedule_selector(Loading::load),1.0f);
	return true;
}

void Loading::load(float dt)
{
	getChildByTag(1020)->removeFromParentAndCleanup(true);

	CCScene* pScene = TowerScene::create();

	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.1f, pScene));

}