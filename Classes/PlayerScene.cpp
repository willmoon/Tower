#include "PlayerScene.h"
//#include "HelloWorldScene.h"

using namespace cocos2d;


bool PlayerScene::init()
{
	addChild(PlayerSceneLayer::create());
	return true;
}

bool PlayerSceneLayer::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(205, 255, 255, 100)))
	{
		return false;
	}
	int winWidth = CCDirector::sharedDirector()->getWinSize().width;
	int winHeight = CCDirector::sharedDirector()->getWinSize().height;

	

	//returnItem
	pReturnWorld = CCMenuItemImage::create("ui/Market/BackItem.png","ui/Market/BackItem.png", this,  menu_selector(PlayerSceneLayer::ReturnCallback));
	pReturnWorld->setScale(0.66f);
	pReturnWorld->setPosition( ccp(winWidth-70+48, 290) );//48

	//int num=2;

	//add_lock
	//for(int i = 1;i<=num;i++)
	//{
	//	char str[30];
	//	sprintf(str,"player%d_lock",i);
	//	PlayerLock[i]= CCUserDefault::sharedUserDefault()->getIntegerForKey(str);

	//	if(PlayerLock[i] == 0) 
	//	{
	//		CCSprite* lock = CCSprite::create("UI/largeLock.png");
	//		lock->setScale(0.3f);
	//		lock->setPosition(ccp(100*i+150,200));
	//		layer->addChild(lock,3);		
	//	}
	//}

	////animate
	//for(int i=1;i<=num;++i){
	//PlayerAnimate = CCSprite::create("UI/none.png");
	//PlayerAnimate->setPosition(ccp(100*i+150,200));
	//PlayerAnimate->setScale(0.5f);
	//layer->addChild(PlayerAnimate,1);
	//if (PlayerLock[i]==1)
	//{
	//	Animate(i);
	//}	
	//}
	//layer->setAnchorPoint(CCPointZero);
	//layer->setPosition(CCPointZero);
	//layer->setContentSize(CCSizeMake(winWidth, winHeight));

	//this->addChild(layer,1);

	CCSprite *coin = CCSprite::create("ui/props/coin.png");
	coin->setPosition(ccp(40,290));
	this->addChild(coin,1);

	CoinTotal = CCLabelTTF::create("", "Arial", 20);
	char szStar[256] = {0};
	sprintf (szStar ,"%d",CCUserDefault ::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
	//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
	CoinTotal->setString(szStar);
	CoinTotal->setPosition(ccp(90,290));
	this->addChild(CoinTotal,0);

	CoinUsed = CCLabelTTF::create("", "Arial", 20);
//	_snprintf(szStar, sizeof(szStar)-1, "need:%d",);
//	CoinUsed->setString(szStar);
//	CoinUsed->setPosition(ccp(200,290));
	this->addChild(CoinUsed,0);


	CCMenu* pMenu_e = CCMenu::create(pReturnWorld ,NULL);
	pMenu_e->setPosition( CCPointZero );
    this->addChild(pMenu_e, 1);	

	

	CCSprite * pro_panel = CCSprite::create("ui/props/pro_panel.png");
	pro_panel->setPosition(ccp(winWidth/2+120,winHeight/2-10));//72
	pro_panel->setScale(0.9f);
	this->addChild(pro_panel);

	int pro_x=winWidth/2+48;//48
	int pro_y=winHeight-72;
	for (int i=1;i<=3;i++)
	{
		for(int j=1;j<=2;j++){
			CCSprite * prop = CCSprite::create("ui/props/no_p.png");
			prop->setScale(0.8f);
			prop->setPosition(ccp(pro_x+72*(i-1),pro_y-108*(j-1)));
			this->addChild(prop);
		}
	}

	CCLayer *layer_f = CCLayer::create();
	initplayer(1);
	//ShowInf_f();

	CCSprite* W=CCSprite::create("ui/props/W.png");
	W->setScale(0.8f);
	W->setPosition(ccp(pro_x,pro_y));
	layer_f->addChild(W,2);

	int upw_px=winWidth/2+48;//48
	int upw_py=winHeight-120;
	upw=CCMenuItemImage::create("ui/props/up.png","ui/props/up.png",this,NULL);
	upw->setScale(0.5f);
	//upw->setVisible(false);
	upw->setPosition(upw_px,upw_py);

	CCSprite * W1=CCSprite::create("ui/Market/w1.png");
	W1->setPosition(ccp(pro_x+72,pro_y));
	W1->setScale(0.8f);
	layer_f->addChild(W1,2);

	upw1=CCMenuItemImage::create("ui/props/up.png","ui/props/up.png",this,NULL);
	upw1->setScale(0.5f);
	upw1->setPosition(upw_px+72,upw_py);
	if((CCUserDefault::sharedUserDefault()->getBoolForKey("BuyW1"))==false)
	{
		W1->setVisible(false);
		upw1->setVisible(false);
	}

	CCSprite * W2=CCSprite::create("ui/Market/w2.png");
	W2->setScale(0.8f);
	W2->setPosition(ccp(pro_x+72*2,pro_y));
	layer_f->addChild(W2,2);

	upw2=CCMenuItemImage::create("ui/props/up.png","ui/props/up.png",this,NULL);
	upw2->setScale(0.5f);
	upw2->setPosition(upw_px+72*2,upw_py);
	if((CCUserDefault::sharedUserDefault()->getBoolForKey("BuyW2"))==false)
	{
		W2->setVisible(false);
		upw2->setVisible(false);
	}

	CCSprite * W3=CCSprite::create("ui/Market/w3.png");
	W3->setScale(0.8f);
	W3->setPosition(ccp(pro_x,pro_y-108));
	layer_f->addChild(W3,2);

	upw3=CCMenuItemImage::create("ui/props/up.png","ui/props/up.png",this,NULL);
	upw3->setScale(0.5f);
	upw3->setPosition(upw_px,upw_py-108);
	if((CCUserDefault::sharedUserDefault()->getBoolForKey("BuyW3"))==false)
	{
		W3->setVisible(false);
		upw3->setVisible(false);
	}


	CCMenuItemImage *use = CCMenuItemImage::create("ui/props/use.png","ui/props/use.png",this,menu_selector(PlayerSceneLayer::UpCallback));
	use->setScale(0.5f);
	use->setPosition(winWidth/4+20,winHeight/6*3);

	CCLabelTTF* LV = CCLabelTTF::create("LV:", "Arial", 20);
	LV->setPosition(ccp(winWidth/4,winHeight/6*3+40));
	this->addChild(LV);

	CCSprite *EquChoice = CCSprite::create("ui/props/EquChoice.png");
	EquChoice->setScale(0.5f);
	EquChoice->setPosition(ccp(winWidth/2+72+48,winHeight-72*4));
	this->addChild(EquChoice);



	CCMenu *pMenu = CCMenu::create(use,upw,upw1,upw2,upw3,NULL);
	pMenu->setPosition(CCPointZero);
	layer_f->addChild(pMenu,2);

	CCSprite* playerInf = CCSprite::create("ui/props/PlayerInf.png");
	playerInf->setScale(0.6f);
	playerInf->setPosition(ccp(winWidth/5,winHeight/5));
	layer_f->addChild(playerInf,2);

    this->addChild(layer_f,1);

	return true;
}

void PlayerSceneLayer::ReturnCallback(CCObject* pSender)
{   
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(2.0f, PictureSelectScene::create()));
}

void PlayerSceneLayer::Animate(int type)
{
	switch(type)
	{
	case 1:{
		PlayerAnimate->stopAllActions();
		CCArray *aniframe=CCArray::createWithCapacity(2);   //创建长度为4的集合
		char str[30];
		for(int i=1;i<=2;i++){
			sprintf(str,"ui/player/player%d.png",i);  //通过下标动态创建精灵
			CCSpriteFrame *frame;
			frame =CCSpriteFrame::create(str,CCRectMake(0,0,284,320));
			aniframe->addObject(frame);//将每一帧精灵动画添加到集合里面
		}
		CCAnimation *animation=CCAnimation::createWithSpriteFrames(aniframe,0.2f);//通过集合创建动画
		CCAnimate *animate=CCAnimate::create(animation);
		PlayerAnimate->runAction(CCRepeatForever::create(animate));
		   }
		   break;
	case 2:{
		PlayerAnimate->stopAllActions();
		CCArray *aniframe=CCArray::createWithCapacity(2);   //创建长度为4的集合
		char str[30];
		for(int i=3;i<=4;i++){
			sprintf(str,"ui/player/player%d.png",i);  //通过下标动态创建精灵
			CCSpriteFrame *frame;
			frame =CCSpriteFrame::create(str,CCRectMake(0,0,284,320));
			aniframe->addObject(frame);//将每一帧精灵动画添加到集合里面
		}
		CCAnimation *animation=CCAnimation::createWithSpriteFrames(aniframe,0.2f);//通过集合创建动画
		CCAnimate *animate=CCAnimate::create(animation);
		PlayerAnimate->runAction(CCRepeatForever::create(animate));
		   }
		   break;
}
}

void  PlayerSceneLayer::initplayer(int type)
{
	int winWidth = CCDirector::sharedDirector()->getWinSize().width;
	int winHeight = CCDirector::sharedDirector()->getWinSize().height;
	switch(type){
	case 1:
		{
		CCSprite *player1 = CCSprite::create("ui/player/player1.png");
		player1->setPosition(ccp(winWidth/8,winHeight/5*3));
		player1->setScale(0.5f);
		this->addChild(player1,1);

		//ShowInf_f();
		F_Lv = CCLabelTTF::create("", "Arial", 20);
		char szStar[256] = {0};
		sprintf (szStar ,"%d",CCUserDefault ::sharedUserDefault()->getIntegerForKey("F_LVv"));
		//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Lv"));
		F_Lv->setString(szStar);
		F_Lv->setPosition(ccp(winWidth/4+20,winHeight/6*3+40));
		this->addChild(F_Lv,3);

		F_Life = CCLabelTTF::create("", "Arial", 20);
		sprintf (szStar ,"%d",CCUserDefault ::sharedUserDefault()->getIntegerForKey("F_Life"));
		//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Life"));
		F_Life->setString(szStar);
		F_Life->setPosition(ccp(winWidth/5-25,winHeight/5+15));
		this->addChild(F_Life,3);

		F_Defense = CCLabelTTF::create("", "Arial", 20);
		sprintf (szStar ,"%d",CCUserDefault ::sharedUserDefault()->getIntegerForKey("F_Defense"));
		//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Defense"));
		F_Defense->setString(szStar);
		F_Defense->setPosition(ccp(F_Life->getPositionX()+90,F_Life->getPositionY()));
		this->addChild(F_Defense,3);

		F_Attack = CCLabelTTF::create("", "Arial", 20);
		sprintf (szStar ,"%d",CCUserDefault ::sharedUserDefault()->getIntegerForKey("F_Attack"));
		//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Attack"));
		F_Attack->setString(szStar);
		F_Attack->setPosition(ccp(F_Life->getPositionX(),F_Life->getPositionY()-30));
		this->addChild(F_Attack,3);

		F_Combo = CCLabelTTF::create("", "Arial", 20);
		sprintf (szStar ,"%d",CCUserDefault ::sharedUserDefault()->getIntegerForKey("F_Combo"));
		//_snprintf(szStar, sizeof(szStar)-1, "%d%%", CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Combo"));
		F_Combo->setString(szStar);
		F_Combo->setPosition(ccp(F_Life->getPositionX()+90,F_Life->getPositionY()-30));
		this->addChild(F_Combo,3);



		}
		break;
	case  2:
		break;
	default:
		break;
	}

}

void PlayerSceneLayer::UpCallback(CCObject* pSender){
	int LvInf = CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Lv");
	int CoinTol = CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal");

	if (LvInf<10&&CoinTol>=50+50*2*power2(LvInf-1))
	{	
		//CoinUsed->setVisible(false);
		char szStar[256] = {0};
		sprintf(szStar,"need:%d",50+50*2*power2(LvInf));
		//_snprintf(szStar, sizeof(szStar)-1, "need:%d",50+50*2*power2(LvInf));
		CoinUsed->setString(szStar);
		CoinUsed->setPosition(ccp(200,290));
		CoinUsed->setVisible(true);

		CCUserDefault::sharedUserDefault()->setIntegerForKey("Endless_CoinTotal", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal")-(50+50*2*power2(LvInf-1) ));
		CCUserDefault::sharedUserDefault()->setIntegerForKey("F_Lv", CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Lv")+1 );
		CCUserDefault::sharedUserDefault()->setIntegerForKey("F_Life", CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Life") +1);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("F_Defense", CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Defense")+1 );
		CCUserDefault::sharedUserDefault()->setIntegerForKey("F_Attack", CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Attack") +1);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("F_Combo", CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Combo")+1 );
		CCUserDefault::sharedUserDefault()->flush();
	

		ShowInf_f();
	}
}

void PlayerSceneLayer::ShowInf_f(){
	int winWidth = CCDirector::sharedDirector()->getWinSize().width;
	int winHeight = CCDirector::sharedDirector()->getWinSize().height;

	char szStar[256] = {0};
	sprintf(szStar,"%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Lv"));
	//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Lv"));
	F_Lv->setString(szStar);
	F_Lv->setPosition(ccp(winWidth/4+20,winHeight/6*3+40));

	sprintf(szStar,"%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Life"));
	//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Life"));
	F_Life->setString(szStar);
	F_Life->setPosition(ccp(winWidth/5-25,winHeight/5+15));

	sprintf(szStar,"%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Defense"));
	//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Defense"));
	F_Defense->setString(szStar);
	F_Defense->setPosition(ccp(F_Life->getPositionX()+90,F_Life->getPositionY()));
	
	sprintf(szStar,"%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Attack"));
	//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Attack"));
	F_Attack->setString(szStar);
	F_Attack->setPosition(ccp(F_Life->getPositionX(),F_Life->getPositionY()-30));

	sprintf(szStar,"%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Combo"));
	//_snprintf(szStar, sizeof(szStar)-1, "%d%%", CCUserDefault::sharedUserDefault()->getIntegerForKey("F_Combo"));
	F_Combo->setString(szStar);
	F_Combo->setPosition(ccp(F_Life->getPositionX()+90,F_Life->getPositionY()-30));

	sprintf(szStar,"%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
	//_snprintf(szStar, sizeof(szStar)-1, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("Endless_CoinTotal"));
	CoinTotal->setString(szStar);
	CoinTotal->setPosition(ccp(90,290));


}

int PlayerSceneLayer::power2(int n){   
	int r = 1;  
	for(int i=1;i<=n;i++)      
		r *= 2;  
	return r;
}