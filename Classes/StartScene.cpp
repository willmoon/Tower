#include "StartScene.h"
#include "Tower.h"
#include "Test_lev.h"
using namespace cocos2d;

// on "init" you need to initialize your instance
bool StartScene::init()
{
	Tower::initMonstersList();
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("frames/monster_1.plist","frames/monster_1.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("frames/monster_3.plist","frames/monster_3.png");
	
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/monster_run_1.plist");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/monster_die_1.plist");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/monster_run_3.plist");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/monster_die_3.plist");
	//addChild(Tower::create());
	addChild (Test_lev ::create ());
	return true;
}


