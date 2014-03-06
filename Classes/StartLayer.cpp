#include "StartLayer.h"

using namespace cocos2d;

bool StartLayer::init()
{
	CCSprite *bg=CCSprite::create("ui/start.png");
	bg->setAnchorPoint (ccp(0,0));
	addChild (bg);
	bg->setScale (0.5f);

	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"ui/CloseNormal.png",
		"ui/CloseSelected.png",
		this,
		menu_selector(StartLayer::quit));

	pCloseItem->setPosition(ccp(WINSIZE.width - 40, 30));
	CCMenu *tem=CCMenu ::create(pCloseItem ,NULL);
	addChild (tem);
	tem->setPosition (CCPointZero);


	CCMenuItemImage *startImage=CCMenuItemImage::create
		("ui/start_btn.png", "ui/start_btn_down.png",this,menu_selector(StartLayer::start));  

	CCMenuItemImage *shopImage=CCMenuItemImage::create
		("ui/shop_btn.png", "ui/shop_btn_down.png",this,menu_selector(StartLayer::shop));  

	CCMenuItemImage *setImage=CCMenuItemImage::create
		("ui/set_btn.png", "ui/set_btn_down.png",this,menu_selector(StartLayer::set));  

	CCMenu *menu=CCMenu::create(startImage,shopImage,setImage,NULL);  
	menu->setScale (0.6f);  

	menu->setPosition (ccp(WINSIZE.width /4,WINSIZE .height /10));
	menu->alignItemsHorizontallyWithPadding (10);

	addChild(menu);  
	return true;
}

void StartLayer::quit(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}

void StartLayer::start(CCObject* pSender)
{
	CCScene *pScene=Loading::create();

	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.1f, pScene));
}

void StartLayer::shop(CCObject* pSender)
{
	CCScene* pScene = PictureSelectScene::create();

	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, pScene));
}

void StartLayer::set(CCObject* pSender)
{

}

