#include "PictureScene.h"
#include "PlayerScene.h"
#include "MarkScene.h"

using namespace cocos2d;
 
 
bool PictureSelectScene::init()
{
	addChild(PictureSelectSceneLayer::create());
	return true;
}


bool PictureSelectSceneLayer::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(255, 255, 255, 100)))
	{
		return false;
	}
	int winWidth = CCDirector::sharedDirector()->getWinSize().width;
	int winHeight = CCDirector::sharedDirector()->getWinSize().height;

	CCSprite* PicIde= CCSprite::create("ui/PicIde.png");
	PicIde->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,300));
	this->addChild(PicIde, 0);

	//returnItem
	pReturnWorld = CCMenuItemImage::create("ui/back1.png", "ui/back2.png", this,  menu_selector(PictureSelectSceneLayer::ReturnCallback));
	pReturnWorld->setPosition( ccp(80, 80) );

	//playerItem
	PlayerWorld= CCMenuItemImage::create("ui/player.png", "ui/player.png", this,  menu_selector(PictureSelectSceneLayer::PlayerCallback));
	PlayerWorld->setScale(0.5f);
	PlayerWorld->setPosition( ccp(winWidth/2-50,winHeight/2) );

	//BossItem
	//BossWorld= CCMenuItemImage::create("UI/Boss.png", "UI/Boss.png", this,  menu_selector(PictureSelectSceneLayer::BossCallback));
	//BossWorld->setScale(0.5f);
	//BossWorld->setPosition( ccp(winWidth/2+50,winHeight/2) );

	//MarkItem
	MarkWorld=CCMenuItemImage::create("ui/marketIcon.png","ui/marketIcon.png",this,menu_selector(PictureSelectSceneLayer::MarkCallback));
	MarkWorld->setPosition(ccp(winWidth/2+50,winHeight/2));



	CCMenu* pMenu_e = CCMenu::create(pReturnWorld,PlayerWorld,MarkWorld ,NULL);
	pMenu_e->setPosition( CCPointZero );
	this->addChild(pMenu_e, 1);	 

	//init player
	 CCUserDefault::sharedUserDefault()->setIntegerForKey("player1_lock", 1);
	 CCUserDefault::sharedUserDefault()->setIntegerForKey("player2_lock", 0);


	if (CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Lv")==0)
	{
	 //init coin
	 CCUserDefault::sharedUserDefault()->setIntegerForKey("Endless_CoinTotal",250000);
	 // init p_info
	 CCUserDefault::sharedUserDefault()->setIntegerForKey("F_Lv",1);
	 CCUserDefault::sharedUserDefault()->setIntegerForKey("F_Life",10);
	 CCUserDefault::sharedUserDefault()->setIntegerForKey("F_Defense",6);
	 CCUserDefault::sharedUserDefault()->setIntegerForKey("F_Attack",8);
	 CCUserDefault::sharedUserDefault()->setIntegerForKey("F_Combo",6);
	}
	 
}

void PictureSelectSceneLayer::ReturnCallback(CCObject* pSender)
{   
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(1.0f, StartScene::create()));
}

void PictureSelectSceneLayer::PlayerCallback(CCObject* pSender)
{   
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(2.0f, PlayerScene::create()));
}
void PictureSelectSceneLayer::BossCallback(CCObject* pSender)
{   
	//CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(2.0f, ZomSelectScene::scene(0)));
}

void PictureSelectSceneLayer::MarkCallback(CCObject* pSender)
{   
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(2.0f, MarkScene::create()));
}
