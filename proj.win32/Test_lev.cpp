#include "Test_lev.h"
#include "Defines.h"

bool Test_lev::init()
{
	winSize=CCDirector ::sharedDirector ()->getWinSize ();

	i_level=1;	//第一关

	m_world = new b2World(b2Vec2(0,-10));
	m_world->SetContinuousPhysics(true);

	next_loader=new LevelHelperLoader("levels/level2.plhs");
	next_loader ->loadLevelsWithOffset (ccp(0,-640));
	next_loader ->addObjectsToWorld (m_world ,this);
	next_loader ->createPhysicBoundaries (m_world);


	//CCLog ("%f",next_loader ->topPhysicBoundary ()->GetPosition ().y);


	//next_loader ->bottomPhysicBoundary ()->GetWorld ()->DestroyBody (next_loader ->bottomPhysicBoundary ());
	loader = new LevelHelperLoader("levels/level1.plhs");
	loader ->loadLevelsWithOffset (ccp(0,0));
	loader->addObjectsToWorld(m_world ,this);
	loader->createPhysicBoundaries(m_world);




	setOperating ();

	tem_monster =new Monster;

	_bjumped =false;

	run_schedule=false;

	lock=false;

	tem_monster ->monster_cover =10;

	tem_monster ->walk_action =CCAnimate::create (CCAnimationCache ::sharedAnimationCache ()->animationByName
		(CCString ::createWithFormat ("monster_%d_run",1)->getCString ()));

	tem_monster ->monster_sprite =CCSprite::createWithSpriteFrame 
		( CCSpriteFrameCache ::sharedSpriteFrameCache ()->spriteFrameByName 
		(CCString ::createWithFormat ("monster_%d_run-%d",3,1)->getCString ()));

	tem_monster ->monster_sprite->setTag (-1);

	addChild (tem_monster->monster_sprite,999);

	tem_monster->monster_sprite->runAction (CCRepeatForever::create (tem_monster->walk_action));

	tem_monster->monsterBodyDef .type =b2_dynamicBody ;
	tem_monster->monsterBodyDef .position .Set (100/PTM_RATIO ,200/PTM_RATIO);
	tem_monster->monsterBodyDef .userData =tem_monster->monster_sprite ;

	//tem_monster ->monsterBodyDef .

	tem_monster->monster_body = m_world->CreateBody(&tem_monster->monsterBodyDef);

	/*tem_monster->monster_body->SetSleepingAllowed (true);
	tem_monster->monster_body->SetFixedRotation (true);*/

	tem_monster->monster_shape.SetAsBox (tem_monster->monster_sprite->getContentSize().width /PTM_RATIO /3,
		tem_monster->monster_sprite->getContentSize().height /PTM_RATIO /2);

	b2FixtureDef monsterShapeDef;
	monsterShapeDef.shape = &tem_monster->monster_shape;
	monsterShapeDef.density = 2.0f;
	monsterShapeDef.friction = 0.2f;
	monsterShapeDef.restitution = 0.02f;
	monsterShapeDef .filter .groupIndex =-1;

	tem_monster->monster_fixture =tem_monster->monster_body ->CreateFixture (&monsterShapeDef);

	scheduleUpdate();

	setAccelerometerEnabled (true);
	setTouchEnabled (true);
	//setTouchMode(kCCTouchesAllAtOnce);//多点触摸

	return true;
}


Test_lev::~Test_lev(void)
{
}

void Test_lev::update(float dt)
{
	if(tem_monster ->monster_body ->GetPosition ().x>300/PTM_RATIO &&!lock)
	{
		lock=true;
		CCLOG("goto next");

		//loader->topPhysicBoundaryNode ()->removeSelf ();
		//loader->bottomPhysicBoundaryNode ()->removeSelf ();
		//m_world->DestroyBody (loader->bottomPhysicBoundary ());
		//loader->removeAllPhysics ();

		/*next_loader=new LevelHelperLoader("levels/level2.plhs");
		next_loader ->loadLevelsWithOffset (ccp(0,-640));
		next_loader ->addObjectsToWorld (m_world ,this);																																																																				
		next_loader ->createPhysicBoundaries (m_world);*/

		//loader ->removeAllPhysics ();
		//CCAction *t=CCMoveTo ::create(5,ccp(200,600));
		//CCAction *gotonext=CCSequence ::create ((CCFiniteTimeAction *)t,CCCallFunc ::actionWithTarget (this,callfunc_selector (Tower::gotonx)),NULL);
		//m_pHero ->_pSprite ->runAction (gotonext);
		//tem_monster ->monster_sprite->setUsesOverloadedTransformations (true);
		CCAction *t=CCMoveBy ::create(6,ccp(300,0));
		CCAction *gotonext=CCSequence ::create ((CCFiniteTimeAction *)t,CCCallFunc ::actionWithTarget (this,callfunc_selector (Test_lev::gotonx)),NULL);
		//tem_monster ->monster_sprite->runAction (gotonext);
		tem_monster ->monster_body ->SetType (b2_kinematicBody);
		tem_monster ->monster_body ->SetLinearVelocity (b2Vec2 (0,2.5));

		scheduleOnce(schedule_selector (Test_lev::temp),3);

		if(tem_monster ->monster_sprite ->getPosition().y>=400/PTM_RATIO)
		{
			//loader ->release ();
			//loader=NULL ;

			//m_pHero->_pSprite = next_loader->spriteWithUniqueName("role_right_run1"); 
			/*m_pHero->_pBody = m_pHero->_pSprite->getBody();
			m_pHero->_pSprite ->setTag (1);

			m_pHero ->_pSprite ->transformScale (0.3f);*/
		}

		//m_pHero ->_pSprite ->prepareMovementOnPathWithUniqueName ("");
		//m_pHero ->_pSprite ->startPathMovement ();
		//m_pHero ->_pBody ->ApplyForceToCenter (b2Vec2 (0,7.5));
		//m_pHero->_pBody ->SetGravityScale (0);
		//m_pHero ->_pSprite ->sta
		/*loader->release ();
		loader=new LevelHelperLoader ("levels/level_02.plhs");
		loader->addObjectsToWorld(m_world ,this);
		loader->createPhysicBoundaries(m_world);
		m_pHero->_pSprite = loader->spriteWithUniqueName("role_right_run1"); 
		m_pHero->_pBody = m_pHero->_pSprite->getBody();
		m_pHero->_pSprite ->setTag (1);
		m_pHero ->_pSprite ->transformScale (0.3f);
		contactListener=new MyContactListener();
		m_world->SetContactListener(contactListener);*/
	}

	updateHero ();

	setViewpointCenter(ccp(tem_monster->monster_body->GetPosition ().x *PTM_RATIO,tem_monster->monster_body->GetPosition ().y*PTM_RATIO));

	//调用Box2d的step函数来模拟
	this->m_world->Step(0.03f,10,10);
	//变量所有刚体列表
	b2Body* pTempBody = this->m_world->GetBodyList();
	void*   pUserData = NULL;
	for (;pTempBody;pTempBody = pTempBody->GetNext())
	{
		pUserData = pTempBody->GetUserData();
		if (NULL != pUserData)
		{ //移动该精灵，这里用到了之前存在刚体UserData中的数据
			CCSprite *pSprite = (CCSprite *)pUserData;
			b2Vec2 b2vecPosition = pTempBody->GetPosition();
			pSprite->setPosition(ccp(b2vecPosition.x * PTM_RATIO,b2vecPosition.y * PTM_RATIO));
			pSprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(pTempBody->GetAngle()));
		}
	}
}

void Test_lev::setOperating()
{
	operating_layer =CCLayer::create();
	operating_layer ->setAnchorPoint (ccp(0,0));
	operating_layer ->setPosition (ccp(0,0));

	addChild (operating_layer,20);

	left_control=CCSprite ::create ("tile1_L_67.png");
	left_control ->setPosition (ccp(WINSIZE.width/10,WINSIZE .height /10));
	right_control=CCSprite ::create ("tile1_R_67.png");
	right_control ->setPosition (ccp(WINSIZE.width/3,WINSIZE .height /10));
	jump_control=CCSprite ::create ("tile1_J_67.png");
	jump_control ->setPosition (ccp(WINSIZE.width*7/10,WINSIZE .height /10));
	fire_control=CCSprite ::create ("tile1_F_67.png");
	fire_control ->setPosition (ccp(WINSIZE.width*9/10,WINSIZE .height /10));

	left_control->setScale (0.8f);
	right_control->setScale (0.8f);
	jump_control->setScale (0.8f);
	fire_control ->setScale (0.8f);

	left_control ->setOpacity (150);
	right_control ->setOpacity (150);
	jump_control ->setOpacity (150);
	fire_control ->setOpacity (150);

	operating_layer ->addChild (left_control);
	operating_layer ->addChild (right_control);
	operating_layer ->addChild (jump_control);
	operating_layer ->addChild (fire_control);

	left_pressed =false;
	right_pressed =false;
	jump_pressed =false;
	fire_pressed =false;


}

void Test_lev::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}


void Test_lev::ccTouchesBegan (CCSet *pTouches, CCEvent *pEvent)
{
	CCLOG("%d",pTouches ->count());

	CCSetIterator iter = pTouches->begin();  
	for (; iter != pTouches->end(); iter++)  
	{  
		m_pTouch =(CCTouch*)(*iter);
		CCPoint tem_point=m_pTouch ->getLocation ();

		if(left_control ->boundingBox ().containsPoint (tem_point))
		{
			left_pressed =true;
			CCLOG("left_pressed");
		}
		if(right_control ->boundingBox ().containsPoint (tem_point))
		{
			right_pressed =true;
			CCLOG("right_pressed");
		}
		if(jump_control  ->boundingBox ().containsPoint (tem_point)
			&&_bjumped ==false)
		{
			jump_pressed =true;
			CCLOG("jump_pressed");
		}

		if(fire_control ->boundingBox ().containsPoint (tem_point))
		{
			fire_pressed =true;
			CCLOG("fire_pressed");
		}

		/*if(0<=tem_point .x&&tem_point .x<=WINSIZE .width /4)
		{
		left_pressed =true;
		CCLOG("left_pressed");
		}

		if(WINSIZE .width /4<=tem_point .x&&tem_point .x<=WINSIZE .width /2)
		{
		right_pressed =true;
		CCLOG("right_pressed");
		}

		if(WINSIZE .width /2<=tem_point .x&&tem_point .x<=WINSIZE .width )
		{
		jump_pressed =true;
		CCLOG("jump_pressed");
		}*/


	}//遍历取出每个触摸点坐标  

}


void Test_lev ::ccTouchesMoved (CCSet *pTouches, CCEvent *pEvent)
{

	CCSetIterator iter = pTouches->begin();  
	for (; iter != pTouches->end(); iter++)  
	{  
		m_pTouch =(CCTouch*)(*iter);
		CCPoint tem_point=m_pTouch ->getLocation ();

		if(left_control ->boundingBox ().containsPoint (tem_point))
		{
			left_pressed =true;
			CCLOG("left_pressed");
		}
		else if(right_control ->boundingBox ().containsPoint (tem_point))
		{
			right_pressed =true;
			CCLOG("right_pressed");
		}
		else if(jump_control  ->boundingBox ().containsPoint (tem_point)
			&&_bjumped ==false)
		{
			jump_pressed =true;
			CCLOG("jump_pressed");
		}else if(fire_control ->boundingBox ().containsPoint (tem_point))
		{
			fire_pressed =true;
			CCLOG("fire_pressed");
		}
		else
		{
			left_pressed =false;
			right_pressed =false;
			jump_pressed =false;
			fire_pressed =false;
			//HelloWorld ::ccTouchesEnded (pTouches, pEvent);
		}


		//if(0<=tem_point .x&&tem_point .x<=WINSIZE .width /4-10)
		//{
		//	left_pressed =true;
		//	CCLOG("left_pressed");
		//}

		//else if(WINSIZE .width /4<=tem_point .x&&tem_point .x<=WINSIZE .width /2-10)
		//{
		//	right_pressed =true;
		//	CCLOG("right_pressed");
		//}

		//else if(WINSIZE .width /2<=tem_point .x&&tem_point .x<=WINSIZE .width )
		//{
		//	jump_pressed =true;
		//	CCLOG("jump_pressed");
		//}else
		//{
		//	left_pressed =false;
		//	right_pressed =false;
		//	jump_pressed =false;
		//	//HelloWorld ::ccTouchesEnded (pTouches, pEvent);
		//}


	}
}


void Test_lev::ccTouchesEnded (CCSet *pTouches, CCEvent *pEvent)
{
	//CCLOG("%d",LHCuttingEngineMgr ::sharedInstance ()->getSprites ()->count ());	

	CCSetIterator iter = pTouches->begin();  
	for (; iter != pTouches->end(); iter++)  
	{  
		CCTouch* tem_touch =(CCTouch*)(*iter);
		CCPoint tem_point=m_pTouch ->getLocation ();

		if(jump_control ->boundingBox ().containsPoint (tem_touch->getLocation ()))
		{
			CCLOG("jump cancelled");
			jump_pressed=false;

		}
		if(left_control ->boundingBox ().containsPoint (tem_touch->getLocation ()))
		{
			CCLOG("left_control cancelled");
			left_pressed=false;
			unschedule (schedule_selector (Test_lev ::for_run ));

			run_schedule =false;
		}

		if(right_control ->boundingBox ().containsPoint (tem_touch->getLocation ()))
		{
			CCLOG("right_control cancelled");
			right_pressed=false;
			unschedule (schedule_selector (Test_lev ::for_run ));

			run_schedule =false;
		}

		if(fire_control ->boundingBox ().containsPoint (tem_touch ->getLocation ()))
		{
			CCLOG("fire_control cancelled");
			fire_pressed =false;
		}
		/*if(0<=tem_point .x&&tem_point .x<=WINSIZE .width /4)
		{
		CCLOG("left_control cancelled");
		left_pressed=false;
		unschedule (schedule_selector (Tower ::for_run ));

		run_schedule =false;
		}

		if(WINSIZE .width /4<=tem_point .x&&tem_point .x<=WINSIZE .width /2)
		{
		CCLOG("right_control cancelled");
		right_pressed=false;
		unschedule (schedule_selector (Tower ::for_run ));

		run_schedule =false;
		}

		if(WINSIZE .width /2<=tem_point .x&&tem_point .x<=WINSIZE .width )
		{
		CCLOG("jump cancelled");
		jump_pressed=false;
		}*/

	}

	CCLOG("%d",pTouches ->count());

}

void Test_lev::for_run(float dt)
{
	if(tem_monster ->m_bisalive)
	{
		if(left_pressed)
		{
			tem_monster->monster_sprite ->setFlipX (false);
			if(!_bjumped){
				tem_monster->monster_body ->SetLinearVelocity (b2Vec2 (-100/PTM_RATIO ,0));
			}else
			{
				tem_monster->monster_body ->SetLinearVelocity (b2Vec2 (-10/PTM_RATIO ,0));
			}
		}

		if(right_pressed)
		{
			tem_monster->monster_sprite ->setFlipX (true);
			if(!_bjumped){
				tem_monster->monster_body ->SetLinearVelocity (b2Vec2 (100/PTM_RATIO ,0));
			}else
			{
				tem_monster->monster_body ->SetLinearVelocity (b2Vec2 (10/PTM_RATIO ,0));
			}
		}
	}

}

//更新herobody的动作
void Test_lev::updateHero ()
{
	if(tem_monster->m_bisalive)
	{

		if(tem_monster->monster_body->GetLinearVelocity ().y>=-3&&
			tem_monster->monster_body->GetLinearVelocity ().y <3
			//&&
			//m_pHero->_pBody ->GetPosition ().y<(WINSIZE .height *8/5)/PTM_RATIO
			)
		{
			_bjumped =false;
		}else 
		{
			_bjumped =true;
		}

		if((left_pressed||right_pressed)&&!run_schedule)
		{
			schedule (schedule_selector(Test_lev::for_run),0.1f);
			run_schedule=true;
		}

		if(jump_pressed&&_bjumped==false)
		{
			tem_monster->monster_body->SetLinearVelocity (b2Vec2(0/PTM_RATIO,300/PTM_RATIO));

		}

		if(left_pressed&&jump_pressed&&_bjumped==false)
		{
			tem_monster->monster_body->SetLinearVelocity (b2Vec2(-100/PTM_RATIO,300/PTM_RATIO));

		}

		if(right_pressed&&jump_pressed&&_bjumped==false)
		{
			tem_monster->monster_body->SetLinearVelocity (b2Vec2(100/PTM_RATIO,300/PTM_RATIO));

		}


		//if(fire_pressed)
		//{
		//	m_pHero ->_pSprite ->prepareAnimationNamed ("role1Climb","roleAndObjects.pshs");

		//	m_pHero ->_pSprite ->playAnimation ();
		//	m_pHero->_pSprite ->setAnimationHasEndedObserver (this,SEL_CallFuncO (callfuncO_selector (Tower ::hurted)));

		//	//m_pHero ->_pSprite ->transformPosition (ccp(200,200));
		//	//m_pHero->_pSprite ->prepareMovementOnPathWithUniqueName ("");
		//}



		//if(m_pHero ->_pBody ->GetLinearVelocity ()==b2Vec2 (0,0))
		//{
		//	//m_pHero ->_pSprite ->pauseAnimation ();
		//	//m_pHero ->_pSprite ->prepareAnimationNamed ("role1Stand","roleAndObjects.pshs");
		//	//m_pHero ->_pSprite ->playAnimation ();
		//	//m_pHero->_pSprite ->setAnimationHasEndedObserver (this,SEL_CallFuncO (callfuncO_selector (Tower ::hurted)));

		//}else
		//{
		//	//m_pHero ->_pSprite ->playAnimation();
		//}


		//if(m_pHero ->_pBody ->GetLinearVelocity ().y >5/PTM_RATIO 
		//	&&m_pHero ->_pBody ->GetLinearVelocity ().x<-2/PTM_RATIO)
		//{
		//	//跳跃的动作
		//	/*	m_pHero_sprite->prepareAnimationNamed("role1RightJump","roleAndObjects.pshs");
		//	m_pHero_sprite->playAnimation();*/

		//}


		//if(m_pHero ->_pBody ->GetLinearVelocity ().y >10/PTM_RATIO
		//	&&m_pHero ->_pBody ->GetLinearVelocity ().x>10)
		//{
		//	//跳跃的动作
		//	/*m_pHero_sprite->prepareAnimationNamed("role1RightJump","roleAndObjects.pshs");
		//	m_pHero_sprite->playAnimation();*/

		//}

	}
}

void Test_lev::setViewpointCenter(CCPoint position)
{
	int x = MAX(position.x, WINSIZE.width / 2);
	int y = MAX(position.y, WINSIZE.height / 2);
	x = MIN(x, (568*6) - WINSIZE.width / 2);
	y = MIN(y, (320*2) - WINSIZE.height / 2);
	CCPoint actualPosition = ccp(x, y);

	CCPoint centerOfView = ccp(WINSIZE.width / 2, WINSIZE.height/2-(i_level -1)*65);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	CCPoint operating_layer_point = ccpSub(actualPosition,centerOfView );

	this->setPosition(viewPoint);
	operating_layer ->setPosition (operating_layer_point);
}

void Test_lev::gotonx()
{
	//m_pHero ->_pSprite ->removeFromParentAndCleanup (true);

	loader->release ();
	loader =NULL;


	////清理上一关遗留的怪物
	//for(map<int ,list<Monster*>>::iterator i=m_pTowerMonsters  .begin ();i!=m_pTowerMonsters .end ();)
	//{
	//	if(!(i->second.empty()))
	//	{
	//		for(list<Monster *>::iterator j=i->second .begin ();j!=i->second .end ();)
	//		{
	//			Monster* tem=*j;

	//			if(tem->m_bisalive)
	//			{
	//				tem->monster_sprite ->removeFromParentAndCleanup (true);

	//				m_world ->DestroyBody (tem->monster_body);

	//				delete tem;
	//				tem =NULL ;

	//				i->second .erase( j++);
	//			}else{

	//				j++;
	//			}
	//		}

	//	}

	//	i++;
	//}




	/*m_pHero->_pSprite = next_loader->spriteWithUniqueName("role_right_run1"); 
	m_pHero->_pBody = m_pHero->_pSprite->getBody();
	m_pHero->_pSprite ->setTag (1);

	m_pHero ->_pSprite ->transformScale (0.3f);*/
}

void Test_lev::temp(float dt)
{
	
	i_level +=1;

	//建造底边和左右两边
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0,0);//?????????????????????????????????????????????????????????????????
	m_pGroundBody = m_world->CreateBody(&groundBodyDef);
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	//刚体m_pGroundBody通过固定装置boxShapeDef与groundEdge相关联
	boxShapeDef.shape = &groundEdge;
	//底边
	groundEdge.Set(b2Vec2(0,(320+70)/PTM_RATIO),b2Vec2(4*winSize.width/PTM_RATIO,(320+70)/PTM_RATIO ));
	m_pGroundBody->CreateFixture(&boxShapeDef);
	////左边
	//groundEdge.Set(b2Vec2(0,0),b2Vec2(0,winSize.height/PTM_RATIO));
	//m_pGroundBody->CreateFixture(&boxShapeDef);
	////上边
	//groundEdge.Set(b2Vec2(0, winSize.height/PTM_RATIO), 
	//	b2Vec2(winSize.width/PTM_RATIO, winSize.height/PTM_RATIO));
	//m_pGroundBody->CreateFixture(&boxShapeDef);
	////右边
	//groundEdge.Set(b2Vec2(winSize.width/PTM_RATIO, 
	//	winSize.height/PTM_RATIO), b2Vec2(winSize.width/PTM_RATIO, 0));
	//m_pGroundBody->CreateFixture(&boxShapeDef);



	tem_monster->monster_body ->SetType (b2_dynamicBody);
	//next_loader ->loadLevelsWithOffset (ccp(0,0));
	//loader->release ();
	//loader =NULL;
}