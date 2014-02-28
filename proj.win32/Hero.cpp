#include "Hero.h"

using namespace cocos2d;

Hero::Hero(void)
{
	_pSprite =CCSprite::createWithSpriteFrame (
		CCSpriteFrameCache ::sharedSpriteFrameCache() 
		->spriteFrameByName (CCString ::createWithFormat ("role_stand1")
		->getCString ())
		);

	_pSprite ->setScale (0.4f);

	_pSprite ->setPosition (ccp(100,190));

	_pBody =NULL;
	
	_iSpeed =0;
	_iState =0;
	_bAlive =true;
	_bJumped =false;
	run_schedule =false;
	_phero_fixture =NULL ;
}


Hero::~Hero(void)
{
}
