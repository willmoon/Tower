#include "StartLayer.h"

using namespace cocos2d;

// on "init" you need to initialize your instance
bool StartLayer::init()
{
    CCLayer::init();
    
    //CCMenuItemFont::setFontSize(30);
    ////背景 
    //CCSprite * pSprite =  CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bg.png"));
    //pSprite->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,568));
    //addChild(pSprite);
    //pSprite =  CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("title.png"));
    //pSprite->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,700));
    //addChild(pSprite);
    //
    //
    //// Create a menu with the "close" menu item, it's an auto release object.
    //CCMenu* pMenu = CCMenu::create();
    //pMenu->setPosition(CCPointZero);
    //
    //pSprite =  CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("cmode.png"));
    //CCMenuItemSprite *pMenuSprite =CCMenuItemSprite::create(pSprite, pSprite);
    ////CCMenuItemFont *pMenuLabel = CCMenuItemFont::create("闯关模式");
    //pMenuSprite->setTarget(this, menu_selector(StartLayer::StartConquerBtnCB));
    //// Place the menu item bottom-right conner.
    //pMenuSprite->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 320, 450));
    //pMenu->addChild(pMenuSprite);
    //
    //// Add the menu to HelloWorld layer as a child layer.
    //this->addChild(pMenu, 1);
    //
    //pSprite =  CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("nmode.png"));
    //pMenuSprite =CCMenuItemSprite::create(pSprite, pSprite);
    ////pMenuLabel = CCMenuItemFont::create("无限模式");
    //pMenuSprite->setTarget(this, menu_selector(StartLayer::StartNetBtnCB));
    //// Place the menu item bottom-right conner.
    //pMenuSprite->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 320, 320));
    //pMenu->addChild(pMenuSprite);
    //
    //if (CCUserDefault::sharedUserDefault()->getBoolForKey(MUSIC_KEY)) {
    //    pSprite = CCSprite::createWithSpriteFrameName("soundOn.png");
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bg.mp3",true);
    //}
    //else{
    //    pSprite = CCSprite::createWithSpriteFrameName("soundOff.png");
    //}
    //pMenuSprite = CCMenuItemSprite::create(pSprite, pSprite);
    //pMenuSprite->setTarget(this, menu_selector(StartLayer::MusicBtnCB));
    //pMenuSprite->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 320, 200));
    //pMenu->addChild(pMenuSprite);
	return true;
}

void StartLayer::MusicBtnCB(CCObject* pSender)
{
   /* CCMenuItemSprite* pMenuSprite = (CCMenuItemSprite*)pSender;
    if (CCUserDefault::sharedUserDefault()->getBoolForKey(MUSIC_KEY)) {
        CCUserDefault::sharedUserDefault()->setBoolForKey(MUSIC_KEY, false);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        pMenuSprite->setSelectedImage(CCSprite::createWithSpriteFrameName("soundOff.png"));
        pMenuSprite->setNormalImage(CCSprite::createWithSpriteFrameName("soundOff.png"));
    }
    else{
        CCUserDefault::sharedUserDefault()->setBoolForKey(MUSIC_KEY, true);
        pMenuSprite->setNormalImage(CCSprite::createWithSpriteFrameName("soundOn.png"));
        pMenuSprite->setSelectedImage(CCSprite::createWithSpriteFrameName("soundOn.png"));
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bg.mp3",true);
    }
    CCUserDefault::sharedUserDefault()->flush();*/
}

void StartLayer::StartConquerBtnCB(CCObject* pSender)
{
   /* LevelScene* pScene = LevelScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1, pScene));*/
}

void StartLayer::StartNetBtnCB(CCObject* pSender)
{
    /*
    int result;
    Reachability *r = [Reachability reachabilityWithHostName:@"www.baidu.com"];
    switch ([r currentReachabilityStatus]) {
        case NotReachable:// 没有网络连接
            result=-1;
            break;
        case ReachableViaWWAN:// 使用3G网络
            result=0;
            break;
        case ReachableViaWiFi:// 使用WiFi网络
            result=1;
        break;
    }
    if (result==1) {
        GameScene* pScene = GameScene::create();
        pScene->SetGameMode(3,0);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1, pScene));
    }
    else{
        CCMessageBox("未检测到wifi", "提示");
    }*/
}

void StartLayer::StartChallengeBtnCB(CCObject* pSender)
{
   /* GameScene* pScene = GameScene::create();
    pScene->SetGameMode(0,0);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1, pScene));*/
}

