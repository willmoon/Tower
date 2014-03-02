#include "StartScene.h"
#include "Tower.h"
#include "Test_lev.h"
using namespace cocos2d;

bool StartScene::init()
{
	Tower::initMonstersList();


	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile
		("my_monster_1.plist","my_monster_1.png");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/monster_1_run.plist");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/monster_1_die.plist");

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile
		("my_monster_3.plist","my_monster_3.png");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/monster_3_run.plist");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/monster_3_die.plist");


	/*CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile
		("monster_MonsterSheet.plist","monster_MonsterSheet.png");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/m1_die.plist");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/m1_poison.plist");

	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/m2_die.plist");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/m2_jump.plist");

	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/m3_die.plist");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/m3_lb.plist");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/m3_rb.plist");

	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/b1_lr.plist");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/b1_rr.plist");*/


	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile
		("role1_Role1Sheet.plist","role1_Role1Sheet.png");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/1climb.plist");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/1die.plist");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/1hurt.plist");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/1rjump.plist");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/1rrun.plist");
	CCAnimationCache ::sharedAnimationCache ()->addAnimationsWithFile ("animations/1stand.plist");

	
	addChild(Tower::create());
	//addChild (Test_lev ::create ());
	return true;
}


