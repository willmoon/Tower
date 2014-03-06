#include "MarkScene.h"
//#include "HelloWorldScene.h"
#include "StartScene.h"
#include "PictureScene.h"

using namespace cocos2d;


bool MarkScene::init()
{
	addChild(MarkSceneLayer::create());
	return true;
}

bool MarkSceneLayer::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(205, 255, 255, 100)))
	{
		return false;
	}
	int winWidth = CCDirector::sharedDirector()->getWinSize().width;
	int winHeight = CCDirector::sharedDirector()->getWinSize().height;
	

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* panel_1 = CCSprite::create("ui/Market/panel_1.png");
	panel_1->setScale(0.5f);
	panel_1->setPosition(ccp(size.width/2-120, size.height/2));
	this->addChild(panel_1, 0);

	CCSprite* panel_2 = CCSprite::create("ui/Market/panel_2.png");
	panel_2->setScale(0.5f);
	panel_2->setPosition(ccp(size.width/2+120, size.height/2));
	this->addChild(panel_2, 0);

	//Coin
	CoinTotal = CCLabelTTF::create("", "Arial", 20);
	char szStar[256] = {0};
	sprintf(szStar,"%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
	//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
	CoinTotal->setString(szStar);
	CoinTotal->setPosition(ccp(110,265));
	this->addChild(CoinTotal,0);

	CCMenuItemImage *BackItem = CCMenuItemImage::create("ui/Market/BackItem.png","ui/Market/BackItem.png",this,menu_selector(MarkSceneLayer::BackToPic));
	BackItem->setScale(0.66f);
	BackItem->setPosition(ccp(size.width-50, 300));

	Button_1 = CCMenuItemImage::create("ui/Market/Button_1.png", "ui/Market/Button1.png", this, menu_selector(MarkSceneLayer::Button_1Callback));
	Button_2 = CCMenuItemImage::create("ui/Market/Button_2.png", "ui/Market/Button2.png", this, menu_selector(MarkSceneLayer::Button_2Callback));
	Button_3 = CCMenuItemImage::create("ui/Market/Button_3.png", "ui/Market/Button3.png", this, menu_selector(MarkSceneLayer::Button_3Callback));
	Button_1->setScale(0.66f);
	Button_1->setPosition(ccp(size.width/2-120,size.height/2+40));
	Button_2->setScale(0.66f);
	Button_2->setPosition(ccp(size.width/2-120,size.height/2-10));
	Button_3->setScale(0.66f);
	Button_3->setPosition(ccp(size.width/2-120,size.height/2-60));

	CCMenu* pMenu_e = CCMenu::create(BackItem,Button_1,Button_2,Button_3,NULL);
	pMenu_e->setPosition( CCPointZero );
	this->addChild(pMenu_e, 1);	

	layer1 = CCLayer::create();
 
	for(int i=1;i<=3;i++){
		char str[30];
		sprintf(str,"ui/Market/w%d.png",i);
		w[i]=CCSprite::create(str);
		w[i]->setScale(0.5f);
		w[i]->setPosition(ccp(size.width/2+40,size.height/2-10-80*(i-2)));
		layer1->addChild(w[i],0);

		sprintf(str,"ui/Market/coin.png");
		upcoinw[i]=CCSprite::create(str);
		upcoinw[i]->setPosition(ccp(w[i]->getPositionX(),w[i]->getPositionY()-35));
		layer1->addChild(upcoinw[i],0);

		sprintf(str,"%d",i*(i+1)*500);
		pLabelw[i] = CCLabelTTF::create(str, "Arial", 18);
		pLabelw[i]->setPosition(ccp(upcoinw[i]->getPositionX()+30,upcoinw[i]->getPositionY()));
		layer1->addChild(pLabelw[i],0);
	}

	//CCSprite* w1 = CCSprite::create("UI/Market/w1.png");
	//w1->setScale(0.5f);
	//w1->setPosition(ccp(size.width/2+40,size.height/2+70));
	//layer1->addChild(w1,0);

	//CCSprite* upcoinw1 = CCSprite::create("UI/Market/coin.png");
	//upcoinw1->setPosition(ccp(w1->getPositionX(),w1->getPositionY()-35));
	//layer1->addChild(upcoinw1,0);

	//CCLabelTTF* pLabelw1 = CCLabelTTF::create("1000", "Arial", 18);
	//pLabelw1->setPosition(ccp(upcoinw1->getPositionX()+30, upcoinw1->getPositionY()));
	//layer1->addChild(pLabelw1, 0);
	//layer1->setAnchorPoint(CCPointZero);
	//layer1->setPosition(CCPointZero);
	BuyItem1_1 = CCMenuItemImage::create("ui/Market/BuyItem.png", "ui/Market/BuyItem1.png", this, menu_selector(MarkSceneLayer::BuyItem1_1Callback));
	BuyItem1_1->setScale(0.5f);
	BuyItem1_1->setPosition(ccp(upcoinw[1]->getPositionX()+150,upcoinw[1]->getPositionY()));

	BuyItem1_2 = CCMenuItemImage::create("ui/Market/BuyItem.png", "ui/Market/BuyItem1.png", this, menu_selector(MarkSceneLayer::BuyItem1_2Callback));
	BuyItem1_2->setScale(0.5f);
	BuyItem1_2->setPosition(ccp(upcoinw[2]->getPositionX()+150,upcoinw[2]->getPositionY()));

	BuyItem1_3 = CCMenuItemImage::create("ui/Market/BuyItem.png", "ui/Market/BuyItem1.png", this, menu_selector(MarkSceneLayer::BuyItem1_3Callback));
	BuyItem1_3->setScale(0.5f);
	BuyItem1_3->setPosition(ccp(upcoinw[3]->getPositionX()+150,upcoinw[3]->getPositionY()));

	CCMenu* pBuyMenu=CCMenu::create(BuyItem1_1,BuyItem1_2,BuyItem1_3,NULL);
	pBuyMenu->setPosition(CCPointZero);
	layer1->addChild(pBuyMenu,0);

	NoBuy1_1 = CCSprite::create("ui/Market/NoBuy.png");
	NoBuy1_1->setPosition(ccp(BuyItem1_1->getPositionX(),BuyItem1_1->getPositionY()));
	NoBuy1_1->setScale(0.5f);
	layer1->addChild(NoBuy1_1,0);

	NoBuy1_2 = CCSprite::create("ui/Market/NoBuy.png");
	NoBuy1_2->setPosition(ccp(BuyItem1_2->getPositionX(),BuyItem1_2->getPositionY()));
	NoBuy1_2->setScale(0.5f);
	layer1->addChild(NoBuy1_2,0);

	NoBuy1_3 = CCSprite::create("ui/Market/NoBuy.png");
	NoBuy1_3->setPosition(ccp(BuyItem1_3->getPositionX(),BuyItem1_3->getPositionY()));
	NoBuy1_3->setScale(0.5f);
	layer1->addChild(NoBuy1_3,0);

	if((CCUserDefault::sharedUserDefault()->getBoolForKey("BuyW1"))==false)
	{
		BuyItem1_1->setVisible(true);
		NoBuy1_1->setVisible(false);
	}else{
		BuyItem1_1->setVisible(false);
		NoBuy1_1->setVisible(true);
	}

	if((CCUserDefault::sharedUserDefault()->getBoolForKey("BuyW2"))==false)
	{
		BuyItem1_2->setVisible(true);
		NoBuy1_2->setVisible(false);
	}else{
		BuyItem1_2->setVisible(false);
		NoBuy1_2->setVisible(true);
	}

	if((CCUserDefault::sharedUserDefault()->getBoolForKey("BuyW3"))==false)
	{
		BuyItem1_3->setVisible(true);
		NoBuy1_3->setVisible(false);
	}else{
		BuyItem1_3->setVisible(false);
		NoBuy1_3->setVisible(true);
	}
	

	layer1->setContentSize(CCSizeMake(size.width, size.height));
	this->addChild(layer1,2);

	layer2 = CCLayer::create();

	for(int i=1;i<=3;i++){
		char str[30];
		sprintf(str,"ui/Market/f%d.png",i);
		f[i]=CCSprite::create(str);
		f[i]->setScale(0.5f);
		f[i]->setPosition(ccp(size.width/2+40,size.height/2-10-80*(i-2)));
		layer2->addChild(f[i],0);

		sprintf(str,"ui/Market/coin.png");
		upcoinf[i]=CCSprite::create(str);
		upcoinf[i]->setPosition(ccp(w[i]->getPositionX(),w[i]->getPositionY()-35));
		layer2->addChild(upcoinf[i],0);

		sprintf(str,"%d",i*(i+1)*500);
		pLabelf[i] = CCLabelTTF::create(str, "Arial", 18);
		pLabelf[i]->setPosition(ccp(upcoinf[i]->getPositionX()+30,upcoinf[i]->getPositionY()));
		layer2->addChild(pLabelf[i],0);
	}
	//CCSprite* f1 = CCSprite::create("UI/Market/w2.png");
	//f1->setScale(0.5f);
	//f1->setPosition(ccp(size.width/2+40,size.height/2+70));
	//layer2->addChild(f1,0);

	//CCSprite* upcoinf1 = CCSprite::create("UI/Market/coin.png");
	//upcoinf1->setPosition(ccp(f1->getPositionX(),f1->getPositionY()-35));
	//layer2->addChild(upcoinf1,0);

	//CCLabelTTF* pLabelf1 = CCLabelTTF::create("2000", "Arial", 18);
	//pLabelf1->setPosition(ccp(upcoinf1->getPositionX()+30, upcoinf1->getPositionY()));
	//layer2->addChild(pLabelf1, 0);
	BuyItem2_1 = CCMenuItemImage::create("ui/Market/BuyItem.png", "ui/Market/BuyItem1.png", this,menu_selector(MarkSceneLayer::BuyItem2_1Callback));
	BuyItem2_1->setScale(0.5f);
	BuyItem2_1->setPosition(ccp(upcoinf[1]->getPositionX()+150,upcoinf[1]->getPositionY()));

	BuyItem2_2 = CCMenuItemImage::create("ui/Market/BuyItem.png", "ui/Market/BuyItem1.png", this, menu_selector(MarkSceneLayer::BuyItem2_2Callback));
	BuyItem2_2->setScale(0.5f);
	BuyItem2_2->setPosition(ccp(upcoinf[2]->getPositionX()+150,upcoinf[2]->getPositionY()));

	BuyItem2_3 = CCMenuItemImage::create("ui/Market/BuyItem.png", "ui/Market/BuyItem1.png", this, menu_selector(MarkSceneLayer::BuyItem2_3Callback));
	BuyItem2_3->setScale(0.5f);
	BuyItem2_3->setPosition(ccp(upcoinf[3]->getPositionX()+150,upcoinf[3]->getPositionY()));

	CCMenu* pBuyMenuf=CCMenu::create(BuyItem2_1,BuyItem2_2,BuyItem2_3,NULL);
	pBuyMenuf->setPosition(CCPointZero);
	layer2->addChild(pBuyMenuf,0);

	NoBuy2_1 = CCSprite::create("ui/Market/NoBuy.png");
	NoBuy2_1->setPosition(ccp(BuyItem2_1->getPositionX(),BuyItem2_1->getPositionY()));
	NoBuy2_1->setScale(0.5f);
	layer2->addChild(NoBuy2_1,0);

	NoBuy2_2 = CCSprite::create("ui/Market/NoBuy.png");
	NoBuy2_2->setPosition(ccp(BuyItem2_2->getPositionX(),BuyItem2_2->getPositionY()));
	NoBuy2_2->setScale(0.5f);
	layer2->addChild(NoBuy2_2,0);

	NoBuy2_3 = CCSprite::create("ui/Market/NoBuy.png");
	NoBuy2_3->setPosition(ccp(BuyItem1_3->getPositionX(),BuyItem1_3->getPositionY()));
	NoBuy2_3->setScale(0.5f);
	layer2->addChild(NoBuy2_3,0);

	if((CCUserDefault::sharedUserDefault()->getBoolForKey("Buyf1"))==false)
	{
		BuyItem2_1->setVisible(true);
		NoBuy2_1->setVisible(false);
	}else{
		BuyItem2_1->setVisible(false);
		NoBuy2_1->setVisible(true);
	}

	if((CCUserDefault::sharedUserDefault()->getBoolForKey("Buyf2"))==false)
	{
		BuyItem2_2->setVisible(true);
		NoBuy2_2->setVisible(false);
	}else{
		BuyItem2_2->setVisible(false);
		NoBuy2_2->setVisible(true);
	}

	if((CCUserDefault::sharedUserDefault()->getBoolForKey("Buyf3"))==false)
	{
		BuyItem2_3->setVisible(true);
		NoBuy2_3->setVisible(false);
	}else{
		BuyItem2_3->setVisible(false);
		NoBuy2_3->setVisible(true);
	}


	layer2->setContentSize(CCSizeMake(size.width, size.height));
	layer2->setVisible(false);
	this->addChild(layer2,2);


	layer3 = CCLayer::create();
	for(int i=1;i<=3;i++){
		char str[30];
		sprintf(str,"ui/Market/d%d.png",i);
		d[i]=CCSprite::create(str);
		d[i]->setScale(0.5f);
		d[i]->setPosition(ccp(size.width/2+40,size.height/2-10-80*(i-2)));
		layer3->addChild(d[i],0);

		sprintf(str,"ui/Market/coin.png");
		upcoind[i]=CCSprite::create(str);
		upcoind[i]->setPosition(ccp(w[i]->getPositionX(),w[i]->getPositionY()-35));
		layer3->addChild(upcoind[i],0);

		sprintf(str,"%d",i*(i+1)*500);
		pLabeld[i] = CCLabelTTF::create(str, "Arial", 18);
		pLabeld[i]->setPosition(ccp(upcoind[i]->getPositionX()+30,upcoind[i]->getPositionY()));
		layer3->addChild(pLabeld[i],0);
	}
	BuyItem3_1 = CCMenuItemImage::create("ui/Market/BuyItem.png", "ui/Market/BuyItem1.png", this,menu_selector(MarkSceneLayer::BuyItem3_1Callback));
	BuyItem3_1->setScale(0.5f);
	BuyItem3_1->setPosition(ccp(upcoind[1]->getPositionX()+150,upcoind[1]->getPositionY()));

	BuyItem3_2 = CCMenuItemImage::create("ui/Market/BuyItem.png", "ui/Market/BuyItem1.png", this, menu_selector(MarkSceneLayer::BuyItem3_2Callback));
	BuyItem3_2->setScale(0.5f);
	BuyItem3_2->setPosition(ccp(upcoind[2]->getPositionX()+150,upcoind[2]->getPositionY()));

	BuyItem3_3 = CCMenuItemImage::create("ui/Market/BuyItem.png", "ui/Market/BuyItem1.png", this, menu_selector(MarkSceneLayer::BuyItem3_3Callback));
	BuyItem3_3->setScale(0.5f);
	BuyItem3_3->setPosition(ccp(upcoind[3]->getPositionX()+150,upcoind[3]->getPositionY()));

	CCMenu* pBuyMenud=CCMenu::create(BuyItem3_1,BuyItem3_2,BuyItem3_3,NULL);
	pBuyMenud->setPosition(CCPointZero);
	layer3->addChild(pBuyMenud,0);

	NoBuy3_1 = CCSprite::create("ui/Market/NoBuy.png");
	NoBuy3_1->setPosition(ccp(BuyItem3_1->getPositionX(),BuyItem3_1->getPositionY()));
	NoBuy3_1->setScale(0.5f);
	layer3->addChild(NoBuy3_1,0);

	NoBuy3_2 = CCSprite::create("ui/Market/NoBuy.png");
	NoBuy3_2->setPosition(ccp(BuyItem3_2->getPositionX(),BuyItem3_2->getPositionY()));
	NoBuy3_2->setScale(0.5f);
	layer3->addChild(NoBuy3_2,0);

	NoBuy3_3 = CCSprite::create("ui/Market/NoBuy.png");
	NoBuy3_3->setPosition(ccp(BuyItem3_3->getPositionX(),BuyItem3_3->getPositionY()));
	NoBuy3_3->setScale(0.5f);
	layer3->addChild(NoBuy3_3,0);

	if((CCUserDefault::sharedUserDefault()->getBoolForKey("Buyd1"))==false)
	{
		BuyItem3_1->setVisible(true);
		NoBuy3_1->setVisible(false);
	}else{
		BuyItem3_1->setVisible(false);
		NoBuy3_1->setVisible(true);
	}

	if((CCUserDefault::sharedUserDefault()->getBoolForKey("Buyd2"))==false)
	{
		BuyItem3_2->setVisible(true);
		NoBuy3_2->setVisible(false);
	}else{
		BuyItem3_2->setVisible(false);
		NoBuy3_2->setVisible(true);
	}

	if((CCUserDefault::sharedUserDefault()->getBoolForKey("Buyd3"))==false)
	{
		BuyItem3_3->setVisible(true);
		NoBuy3_3->setVisible(false);
	}else{
		BuyItem3_3->setVisible(false);
		NoBuy3_3->setVisible(true);
	}

	layer3->setContentSize(CCSizeMake(size.width, size.height));
	layer3->setVisible(false);
	this->addChild(layer3,2);


	return true;
}

void MarkSceneLayer::Button_1Callback(CCObject* pSender){
	layer2->setVisible(false);
	layer3->setVisible(false);
	layer1->setVisible(true);
}

void MarkSceneLayer::Button_2Callback(CCObject* pSender){

	layer1->setVisible(false);
	layer3->setVisible(false);
	layer2->setVisible(true);
}

void MarkSceneLayer::Button_3Callback(CCObject* pSender){

	layer1->setVisible(false);
	layer2->setVisible(false);
	layer3->setVisible(true);
}



void MarkSceneLayer::BuyItem1_1Callback(CCObject* pSender){
	
	if(CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal")>=1000){

		CCLOG("-1000");
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Endless_CoinTotal", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal") -1000);
		CCUserDefault::sharedUserDefault()->setBoolForKey("BuyW1",true);
		CCUserDefault::sharedUserDefault()->flush();
		char szStar[256] = {0};
		sprintf(szStar,"%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
		//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
		CoinTotal->setString(szStar);
		CoinTotal->setPosition(ccp(110,265));

		BuyItem1_1->setVisible(false);
		NoBuy1_1->setVisible(true);
	}
}

void MarkSceneLayer::BuyItem1_2Callback(CCObject* pSender){

	if(CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal")>=3000){

		CCLOG("-3000");
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Endless_CoinTotal", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal") -3000);
		CCUserDefault::sharedUserDefault()->setBoolForKey("BuyW2",true);
		CCUserDefault::sharedUserDefault()->flush();
		char szStar[256] = {0};
		sprintf(szStar,"%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
		//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
		CoinTotal->setString(szStar);
		CoinTotal->setPosition(ccp(110,265));

		BuyItem1_2->setVisible(false);
		NoBuy1_2->setVisible(true);
	}
}

void MarkSceneLayer::BuyItem1_3Callback(CCObject* pSender){

	if(CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal")>=6000){

		CCLOG("-6000");
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Endless_CoinTotal", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal") -6000);
		CCUserDefault::sharedUserDefault()->setBoolForKey("BuyW3",true);
		CCUserDefault::sharedUserDefault()->flush();
		char szStar[256] = {0};
		sprintf(szStar,"%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
		//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
		CoinTotal->setString(szStar);
		CoinTotal->setPosition(ccp(110,265));

		BuyItem1_3->setVisible(false);
		NoBuy1_3->setVisible(true);
	}
}

void MarkSceneLayer::BuyItem2_1Callback(CCObject* pSender){

	if(CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal")>=1000){

		CCLOG("-1000");
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Endless_CoinTotal", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal") -1000);
		CCUserDefault::sharedUserDefault()->setBoolForKey("Buyf1",true);
		CCUserDefault::sharedUserDefault()->flush();
		char szStar[256] = {0};
		sprintf(szStar,"%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
		//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
		CoinTotal->setString(szStar);
		CoinTotal->setPosition(ccp(110,265));

		BuyItem2_1->setVisible(false);
		NoBuy2_1->setVisible(true);
	}
}

void MarkSceneLayer::BuyItem2_2Callback(CCObject* pSender){

	if(CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal")>=3000){

		CCLOG("-3000");
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Endless_CoinTotal", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal") -3000);
		CCUserDefault::sharedUserDefault()->setBoolForKey("Buyf2",true);
		CCUserDefault::sharedUserDefault()->flush();
		char szStar[256] = {0};
		sprintf(szStar,"%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
		//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
		CoinTotal->setString(szStar);
		CoinTotal->setPosition(ccp(110,265));

		BuyItem2_2->setVisible(false);
		NoBuy2_2->setVisible(true);
	}
}


void MarkSceneLayer::BuyItem2_3Callback(CCObject* pSender){

	if(CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal")>=6000){

	CCLOG("-6000");
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Endless_CoinTotal", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal") -6000);
	CCUserDefault::sharedUserDefault()->setBoolForKey("Buyf3",true);
	CCUserDefault::sharedUserDefault()->flush();
	char szStar[256] = {0};

	//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
	CoinTotal->setString(szStar);
	CoinTotal->setPosition(ccp(110,265));

	BuyItem2_3->setVisible(false);
	NoBuy2_3->setVisible(true);
	}
}

void MarkSceneLayer::BuyItem3_1Callback(CCObject* pSender){

	if(CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal")>=1000){

		CCLOG("-1000");
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Endless_CoinTotal", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal") -1000);
		CCUserDefault::sharedUserDefault()->setBoolForKey("Buyd1",true);
		CCUserDefault::sharedUserDefault()->flush();
		char szStar[256] = {0};
		sprintf(szStar,"%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
		//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
		CoinTotal->setString(szStar);
		CoinTotal->setPosition(ccp(110,265));

		BuyItem3_1->setVisible(false);
		NoBuy3_1->setVisible(true);
	}
}

void MarkSceneLayer::BuyItem3_2Callback(CCObject* pSender){

	if(CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal")>=3000){

		CCLOG("-3000");
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Endless_CoinTotal", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal") -3000);
		CCUserDefault::sharedUserDefault()->setBoolForKey("Buyd2",true);
		CCUserDefault::sharedUserDefault()->flush();
		char szStar[256] = {0};
		sprintf(szStar,"%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
		//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
		CoinTotal->setString(szStar);
		CoinTotal->setPosition(ccp(110,265));

		BuyItem3_2->setVisible(false);
		NoBuy3_2->setVisible(true);
	}
}


void MarkSceneLayer::BuyItem3_3Callback(CCObject* pSender){

	if(CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal")>=6000){

		CCLOG("-6000");
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Endless_CoinTotal", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal") -6000);
		CCUserDefault::sharedUserDefault()->setBoolForKey("Buyd3",true);
		CCUserDefault::sharedUserDefault()->flush();
		char szStar[256] = {0};
		sprintf(szStar,"%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
		//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
		CoinTotal->setString(szStar);
		CoinTotal->setPosition(ccp(110,265));

		BuyItem3_3->setVisible(false);
		NoBuy3_3->setVisible(true);

	}
}




void MarkSceneLayer::BackToPic(CCObject* pSender)
{   
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(2.0f, PictureSelectScene::create()));
}

