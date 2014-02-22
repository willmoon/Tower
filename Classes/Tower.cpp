#include "Tower.h"
using namespace cocos2d;

// on "init" you need to initialize your instance
bool Tower::init()
{
	m_iLevel=1;  //第几关
	m_pHero =new Hero ();

	lock=false;	//进入下一关的时候的锁

	////////////////////////////////////////////////
	m_world = new b2World(b2Vec2(0,-10));
	m_world->SetContinuousPhysics(true);
	loader = new LevelHelperLoader("levels/level1.plhs");

	//loader->registerLoadingProgressObserver(this, callfuncFloat_selector(loadingProgress));
	//loader->loadLevelsWithOffset(ccp(300,100));
	//loader->layerWithUniqueName ("MAIN_LAYER");

	loader->addObjectsToWorld(m_world ,this);
	loader->createPhysicBoundaries(m_world);


	CCRect gwRect = loader->gameWorldSize();

	float x = gwRect.origin.x;
	float y = gwRect.origin.y;
	float width = gwRect.size.width;
	float height= gwRect.size.height;
	CCLog("x %f, y %f, width %f, height %f", x, y, width, height);


	//CCPoint pointA,pointB;
	//pointA .setPoint (500,350);
	//pointB .setPoint (100,350);
	//LHCuttingEngineMgr::sharedInstance()->cutAllSpritesIntersectedByLine(pointA, pointB, m_world);
	//CCLOG("%d",LHCuttingEngineMgr ::sharedInstance ()->getSprites ()->count ());	

	m_pHero->_pSprite = loader->spriteWithUniqueName("role_right_run1");
	//m_pHero ->_pSprite =LHSprite ::spriteWithName ("role_right_run1","role1","roleAndObjects.pshs");
	//m_pHero ->_pSprite ->setPosition (ccp(150,200));
	//addChild(m_pHero ->_pSprite,20);
	//m_pHero->_pBody = loader->spriteWithUniqueName("role_right_run1")->getBody();

	m_pHero ->_pBody =m_pHero ->_pSprite ->getBody ();
	m_pHero->_pSprite ->setTag (1);

	m_pHero ->_pSprite ->transformScale (0.3f);


	contactListener=new MyContactListener();
	m_world->SetContactListener(contactListener);
	////////////////////////////////////////////////////////
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

	run_schedule=false;
	/////////////////////////////////////////////////////////////////
	setLevel (m_iLevel);

	schedule(schedule_selector(Tower ::monster_patrol),0.2f);

	setAccelerometerEnabled (true);
	setTouchEnabled (true);

	scheduleUpdate();
	return true;
}
//更新herobody的动作
void Tower::updateHero ()
{
	if(m_pHero->_bAlive )
	{
		//更新hero的动画
		if(m_pHero ->_iState ==1)
		{
			//m_pHero ->_pSprite ->prepareAnimationNamed ("role1LeftRun","roleAndObjects.pshs");
			//m_pHero ->_pSprite->playAnimation ();
		}else if(m_pHero ->_iState ==2)
		{
			//m_pHero ->_pSprite ->prepareAnimationNamed ("role1Hurt","roleAndObjects.pshs");
			//m_pHero ->_pSprite->playAnimation ();
		}

		if(m_pHero->_pBody->GetLinearVelocity ().y>=-3&&
			m_pHero->_pBody->GetLinearVelocity ().y <3
			//&&
			//m_pHero->_pBody ->GetPosition ().y<(WINSIZE .height *8/5)/PTM_RATIO
			)
		{
			m_pHero->_bJumped =false;
		}else 
		{
			m_pHero->_bJumped =true;
		}

		if((left_pressed||right_pressed)&&!run_schedule)
		{
			schedule (schedule_selector(Tower::for_run),0.1f);
			run_schedule=true;
		}

		if(jump_pressed&&m_pHero->_bJumped==false)
		{
			m_pHero ->_pBody->SetLinearVelocity (b2Vec2(0/PTM_RATIO,300/PTM_RATIO));

		}

		if(left_pressed&&jump_pressed&&m_pHero->_bJumped==false)
		{
			m_pHero ->_pBody->SetLinearVelocity (b2Vec2(-100/PTM_RATIO,300/PTM_RATIO));

		}

		if(right_pressed&&jump_pressed&&m_pHero->_bJumped==false)
		{
			m_pHero ->_pBody->SetLinearVelocity (b2Vec2(100/PTM_RATIO,300/PTM_RATIO));

		}


		if(fire_pressed)
		{
			m_pHero ->_pSprite ->prepareAnimationNamed ("role1Climb","roleAndObjects.pshs");

			m_pHero ->_pSprite ->playAnimation ();
			m_pHero->_pSprite ->setAnimationHasEndedObserver (this,SEL_CallFuncO (callfuncO_selector (Tower ::hurted)));

			//m_pHero ->_pSprite ->transformPosition (ccp(200,200));
			//m_pHero->_pSprite ->prepareMovementOnPathWithUniqueName ("");
		}



		if(m_pHero ->_pBody ->GetLinearVelocity ()==b2Vec2 (0,0))
		{
			//m_pHero ->_pSprite ->pauseAnimation ();
			//m_pHero ->_pSprite ->prepareAnimationNamed ("role1Stand","roleAndObjects.pshs");
			//m_pHero ->_pSprite ->playAnimation ();
			//m_pHero->_pSprite ->setAnimationHasEndedObserver (this,SEL_CallFuncO (callfuncO_selector (Tower ::hurted)));

		}else
		{
			//m_pHero ->_pSprite ->playAnimation();
		}


		if(m_pHero ->_pBody ->GetLinearVelocity ().y >5/PTM_RATIO 
			&&m_pHero ->_pBody ->GetLinearVelocity ().x<-2/PTM_RATIO)
		{
			//跳跃的动作
			/*	m_pHero_sprite->prepareAnimationNamed("role1RightJump","roleAndObjects.pshs");
			m_pHero_sprite->playAnimation();*/

		}


		if(m_pHero ->_pBody ->GetLinearVelocity ().y >10/PTM_RATIO
			&&m_pHero ->_pBody ->GetLinearVelocity ().x>10)
		{
			//跳跃的动作
			/*m_pHero_sprite->prepareAnimationNamed("role1RightJump","roleAndObjects.pshs");
			m_pHero_sprite->playAnimation();*/

		}

	}
}

void Tower::loadingProgress(float progressValue){
	CCLog("LOAD PROGRESS IS %f", progressValue);    
}

void Tower::for_run(float dt)
{
	if(m_pHero ->_bAlive)
	{
		if(left_pressed)
		{
			m_pHero->_pSprite ->setFlipX (true);
			if(!m_pHero->_bJumped){
				m_pHero->_pBody ->SetLinearVelocity (b2Vec2 (-100/PTM_RATIO ,0));
			}else
			{
				m_pHero->_pBody ->SetLinearVelocity (b2Vec2 (-10/PTM_RATIO ,0));
			}
		}

		if(right_pressed)
		{
			m_pHero->_pSprite ->setFlipX (false);
			if(!m_pHero->_bJumped){
				m_pHero->_pBody ->SetLinearVelocity (b2Vec2 (100/PTM_RATIO ,0));
			}else
			{
				m_pHero->_pBody ->SetLinearVelocity (b2Vec2 (10/PTM_RATIO ,0));
			}
		}
	}

}

//巡逻算法
void Tower::monster_patrol(float dt)
{
	//不同type的monster执行不同的patrol，还是设置不同的status?
	/////////////////////////////////////////////////////////////
	for(map<int ,list<Monster*>>::iterator i=m_pTowerMonsters .begin ();i!=m_pTowerMonsters .end ();)
	{
		if(!(i->second.empty()))
		{
			for(list<Monster *>::iterator j=i->second .begin ();j!=i->second .end ();)
			{
				Monster* tem=*j;

				if(tem->monster_stadus==1&&tem->monster_sprite !=NULL)
				{
					tem->monster_body ->SetLinearVelocity (b2Vec2 (tem->monster_speed/PTM_RATIO,0));
					tem->monster_step_count  ++;
					if(tem->monster_step_count >=tem->monster_cover)
					{
						tem->monster_sprite->setFlipX (tem->flag);
						tem->monster_step_count =0;
						tem->flag=!tem->flag;
					}
				}


				if(tem->monster_stadus ==2&&m_pHero->_bAlive)//在巡逻范围内找到hero
				{
					tem->monster_body ->SetLinearVelocity (b2Vec2 (tem->monster_speed/PTM_RATIO,0));
				}

				if(tem->monster_stadus ==3)
				{
					tem->monster_body ->SetLinearVelocity (b2Vec2 (0,0));
				}

				j++;

			}
		}
		i++;

	}

}

void Tower::setViewpointCenter(CCPoint position)
{
	int x = MAX(position.x, WINSIZE.width / 2);
	int y = MAX(position.y, WINSIZE.height / 2);
	x = MIN(x, (568*5) - WINSIZE.width / 2);
	y = MIN(y, (320*3) - WINSIZE.height / 2);
	CCPoint actualPosition = ccp(x, y);

	CCPoint centerOfView = ccp(WINSIZE.width / 2, WINSIZE.height/2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	CCPoint operating_layer_point = ccpSub(actualPosition,centerOfView );

	this->setPosition(viewPoint);
	operating_layer ->setPosition (operating_layer_point);
}


//
void Tower::hurted(CCObject *pSender)
{
	CCLOG("hurted");
	m_pHero ->_pSprite ->prepareAnimationNamed("role1RightRun","roleAndObjects.pshs");
	m_pHero ->_pSprite ->playAnimation ();
}

void Tower::afterHit ()
{
	std::list<MyContact>::iterator pos;
	std::list<b2Body *> toDestroy;
	for(pos=contactListener->contactList.begin();pos!=contactListener->contactList.end();++pos)
	{

		MyContact &contact=*pos;

		b2Body *bodyA = contact.fixtureA->GetBody();
		b2Body *bodyB = contact.fixtureB->GetBody();
		if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL) {
			CCSprite *spriteA = (CCSprite *) bodyA->GetUserData();
			CCSprite *spriteB = (CCSprite *) bodyB->GetUserData();

			LHSprite *tema=(LHSprite *)bodyA ->GetUserData ();
			LHSprite *temb=(LHSprite *)bodyB ->GetUserData ();
			// Sprite A = hero, Sprite B = monster
			if (spriteA->getTag () ==1&& spriteB->getTag () ==-1) {
				if (std::find(toDestroy.begin(), toDestroy.end(), bodyB) 
					== toDestroy.end()) {
						if(fire_pressed)
							toDestroy.push_back(bodyB);

				}
			}
			// Sprite B = hero, Sprite A = monster
			else if (spriteA->getTag () ==-1&& spriteB->getTag () ==1) {
				if (std::find(toDestroy.begin(), toDestroy.end(), bodyA) 
					== toDestroy.end()) {//bodyA不在toDestroy中
						if(fire_pressed)
							toDestroy.push_back(bodyA);

				}
			}else if(temb->getTag ()==1&&tema->getSpriteName ()=="campfire_1")
			{
				//与火焰碰撞,受伤
				CCLOG("hit fire");
				m_pHero ->_pSprite ->prepareAnimationNamed ("role1Hurt","roleAndObjects.pshs");
				m_pHero ->_pSprite ->setAnimationDelayPerUnit (0.1f);
				m_pHero ->_pSprite ->playAnimation ();
				//m_pHero ->_pSprite ->path
				m_pHero->_pSprite ->setAnimationHasEndedObserver (this,SEL_CallFuncO (callfuncO_selector (Tower ::hurted)));

				//m_pHero ->_iState =2;
			}else if(temb->getTag ()==1&&tema->getSpriteName ()=="sinker")
			{
				//与沉锤碰撞
				CCLOG("hit sinker");
				//m_pHero ->_pSprite ->
				m_pHero ->_pSprite ->prepareAnimationNamed ("role1Hurt","roleAndObjects.pshs");
				m_pHero ->_pSprite ->playAnimation ();
				m_pHero->_pSprite ->setAnimationHasEndedObserver (this,SEL_CallFuncO (callfuncO_selector (Tower ::hurted)));
				if(temb->getPositionX ()<tema ->getPositionX ())
				{
					m_pHero ->_pBody ->SetLinearVelocity (b2Vec2 (-100/PTM_RATIO ,50/PTM_RATIO ));
				}else
				{
					m_pHero ->_pBody ->SetLinearVelocity (b2Vec2 (100/PTM_RATIO ,50/PTM_RATIO ));
				}
			}

			spriteA=NULL;
			spriteB=NULL;
		} 

	}


	std::list<b2Body *>::iterator pos2;
	for(pos2=toDestroy .begin(); pos2 != toDestroy.end(); ++pos2) {
		b2Body *body =*pos2; 

		if (body->GetUserData() != NULL) {

			for(map<int ,list<Monster*>>::iterator i=m_pTowerMonsters  .begin ();i!=m_pTowerMonsters .end ();)
			{
				if(!(i->second.empty()))
				{
					for(list<Monster *>::iterator j=i->second .begin ();j!=i->second .end ();)
					{
						Monster* tem=*j;

						if(tem->monster_sprite ==body->GetUserData ())
						{
							//i->second .erase( j++);
							tem->monster_sprite ->stopAllActions ();
							tem->monster_sprite ->runAction (tem->die_action);//???????????????m_uReference??retain????
							tem->m_bisalive =false;
							tem->monster_sprite =NULL ;
						}
						else
						{
							j++;
						}
					}
				}

				i++;
			}

		}
		m_world->DestroyBody(body);
		body=NULL;			

	}
}

void Tower::gotonx()
{
	//m_pHero ->_pSprite ->removeFromParentAndCleanup (true);
	m_iLevel +=1;

	loader->release ();
	loader =NULL;


	//清理上一关遗留的怪物
	for(map<int ,list<Monster*>>::iterator i=m_pTowerMonsters  .begin ();i!=m_pTowerMonsters .end ();)
	{
		if(!(i->second.empty()))
		{
			for(list<Monster *>::iterator j=i->second .begin ();j!=i->second .end ();)
			{
				Monster* tem=*j;

				if(tem->m_bisalive)
				{
					tem->monster_sprite ->removeFromParentAndCleanup (true);

					m_world ->DestroyBody (tem->monster_body);

					delete tem;
					tem =NULL ;

					i->second .erase( j++);
				}else{

					j++;
				}
			}

		}

		i++;
	}




	m_pHero->_pSprite = next_loader->spriteWithUniqueName("role_right_run1"); 
	m_pHero->_pBody = m_pHero->_pSprite->getBody();
	m_pHero->_pSprite ->setTag (1);

	m_pHero ->_pSprite ->transformScale (0.3f);
}

void Tower::update(float dt)
{

	if(m_pHero ->_pBody ->GetPosition ().x>600/PTM_RATIO &&!lock)
	{
		lock=true;
		CCLOG("goto next");

		next_loader=new LevelHelperLoader("levels/level_01.plhs");
		next_loader ->loadLevelsWithOffset (ccp(0,0));
		next_loader ->addObjectsToWorld (m_world ,this);
		//next_loader ->createPhysicBoundaries (m_world);

	}

	updateHero();

	setViewpointCenter(m_pHero->_pSprite->getPosition());

	afterHit ();

	monster_set_status ();

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


//敌人设置图
static map<int,list<monster_data>* > MonstersList;

void Tower::initMonstersList()
{
	if (MonstersList.size()==0) {
		CCString *xml_path=CCString::create ("settings/monsters.xml");
		TiXmlDocument doc(xml_path->getCString ());
		bool loadok=doc.LoadFile ();
		if(!loadok)
		{
			printf ("load xml failed");
			exit (1);
		}

		//////////////////////////////
		TiXmlElement* monsters = doc.RootElement()->FirstChildElement();
		while (monsters!=NULL) {

			int id =atoi(monsters ->Attribute ("id"));
			std::list<monster_data> *monsterList=new list<monster_data >();
			MonstersList.insert(map<int, list<monster_data>*>::value_type(id, monsterList));
			TiXmlElement* monster = monsters->FirstChildElement();
			while (monster!=NULL) {
				monster_data monsterValue;
				monsterValue.type = atoi(monster->Attribute("type"));
				monsterValue.x = atof(monster->Attribute("x"));
				monsterValue.y = atof(monster->Attribute("y"));

				monsterList->push_back(monsterValue);
				monster= monster->NextSiblingElement(); 
			}
			monsters= monsters->NextSiblingElement();
		}
	}
}

void Tower ::setLevel (int m_iLevel)
{
	CCString *xml_path=CCString::createWithFormat ("settings/%d.xml",m_iLevel);

	TiXmlDocument doc(xml_path->getCString ());
	bool loadok=doc.LoadFile ();
	if(!loadok)
	{
		CCLOG("load xml failed");
		exit (1);
	}

	TiXmlElement* monsters = doc.RootElement()->FirstChildElement()->FirstChildElement ();
	while (monsters!=NULL) {

		int id =atoi(monsters ->Attribute ("id"));

		map<int, list<monster_data>* >::iterator it =MonstersList.find(id);
		list<monster_data>* pList = it->second;
		for (list<monster_data>::iterator fit = pList->begin(); fit!=pList->end(); fit++) {
			monster_data  monster = *fit;

			createMonster(monster);
		}
		monsters = monsters->NextSiblingElement();
	}
}


void Tower::createMonster(monster_data monster)
{
	if (monster.type==0) {
		monster.type = random_range (1,1);
	}
	if (monster.x==0) {
		monster.x=3;//+random%((int)CCDirector::sharedDirector()->getWinSize().width - 40);
	}
	if (monster.y==0) {
		monster.y = 20+random%((int)CCDirector::sharedDirector()->getWinSize().width -40);
	}

	if (monster.type<MONSTER_TYPE_COUNT) { //monster

		addMonster (monster,1);

	}
	else if(monster.type>=MONSTER_TYPE_COUNT)//宝物道具
	{

	}

}


void Tower::addMonster (monster_data monster,int num)
{
	Monster *tem_monster=NULL;

	for(int i=1;i<=num;i++)
	{
		tem_monster=new Monster();

		tem_monster ->monster_cover =monster .type *10;

		tem_monster ->walk_action =CCAnimate::create (CCAnimationCache ::sharedAnimationCache ()->animationByName
			(CCString ::createWithFormat ("monster_%d_run",monster.type)->getCString ()));

		CCAction *temdie=CCAnimate::create(CCAnimationCache ::sharedAnimationCache ()->animationByName 
			(CCString ::createWithFormat ("monster_%d_die",monster.type)->getCString ()));

		CCAction *temfade=CCFadeOut ::create (1.0f);

		tem_monster ->die_action =CCSequence::create ((CCFiniteTimeAction *)temdie,temfade,
			CCCallFuncN::actionWithTarget(this, callfuncN_selector(Tower ::dieCallBack)),NULL);

		tem_monster ->die_action->retain ();

		tem_monster ->monster_sprite =CCSprite::createWithSpriteFrame 
			( CCSpriteFrameCache ::sharedSpriteFrameCache ()->spriteFrameByName 
			(CCString ::createWithFormat ("monster_%d_run-%d",3,1)->getCString ()));

		tem_monster ->monster_sprite->setTag (-1);

		addChild (tem_monster->monster_sprite);
		tem_monster->monster_sprite->runAction (CCRepeatForever::create (tem_monster->walk_action));

		tem_monster->monsterBodyDef .type =b2_dynamicBody ;
		tem_monster->monsterBodyDef .position .Set ((200+1000*monster .x )/PTM_RATIO ,195/PTM_RATIO);
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

		//把monster加入key值为type的list中
		map<int,list<Monster *>> ::iterator iter;
		iter=m_pTowerMonsters.find (monster.type);

		if(iter!=m_pTowerMonsters.end ())
		{
			CCLog("find it");
			iter->second .push_back (tem_monster);
		}else
		{
			CCLOG("not find it");
			list<Monster *> tem_list;
			tem_list .push_back (tem_monster);
			m_pTowerMonsters.insert (map<int,list<Monster*>>::value_type (monster.type,tem_list));

		}

	}
}


void Tower::dieCallBack (CCNode *pSender)
{
	pSender->removeFromParentAndCleanup (true);
}



void Tower ::monster_set_status ()
{
	/////////////////////////////////////////////////////////////
	for(map<int ,list<Monster*>>::iterator i=m_pTowerMonsters  .begin ();i!=m_pTowerMonsters .end ();)
	{
		if(!(i->second.empty()))
		{
			for(list<Monster *>::iterator j=i->second .begin ();j!=i->second .end ();)
			{
				Monster* tem=*j;

				if(!tem->m_bisalive )
				{
					i->second .erase( j++);
				}
				else{

					if(tem->monster_body ->GetPosition ().x-m_pHero->_pBody ->GetPosition().x>=140/PTM_RATIO
						||
						tem->monster_body ->GetPosition ().x-m_pHero->_pBody->GetPosition().x<=-140/PTM_RATIO)
					{
						tem->monster_stadus =1;
					} 

					if(tem->monster_body ->GetPosition ().x-m_pHero->_pBody->GetPosition().x<=140/PTM_RATIO&&
						tem->monster_body ->GetPosition ().x-m_pHero->_pBody->GetPosition().x>=40/PTM_RATIO
						||tem->monster_body ->GetPosition ().x-m_pHero->_pBody->GetPosition().x<=-40/PTM_RATIO&&
						tem->monster_body ->GetPosition ().x-m_pHero->_pBody->GetPosition().x>=-140/PTM_RATIO)
					{
						//CCLog ("monster%d:hey,you stop here...",i);

						if(tem->monster_body ->GetPosition ().x >m_pHero->_pBody ->GetPosition ().x &&tem->monster_speed>=0)
						{
							tem->monster_sprite ->setFlipX (false);
							//monsters[i]->setFlipX (false);
						}

						if(tem->monster_body ->GetPosition ().x <m_pHero->_pBody ->GetPosition ().x &&tem->monster_speed<=0)
						{
							tem->monster_sprite ->setFlipX (true);
							//monsters[i]->setFlipX (true);
						}

						tem->monster_stadus =2;
					}

					if(tem->monster_body ->GetPosition ().x-m_pHero->_pBody->GetPosition().x>=0&&
						tem->monster_body ->GetPosition ().x-m_pHero->_pBody->GetPosition().x<=40/PTM_RATIO
						||tem->monster_body ->GetPosition ().x-m_pHero->_pBody->GetPosition().x>=-40/PTM_RATIO&&
						tem->monster_body ->GetPosition ().x-m_pHero->_pBody->GetPosition().x<=0)
					{
						//CCLog("monster%d:i will kill you!!!",i);
						tem->monster_stadus =3;
					}


					//根据精灵面向，改变速度方向
					if(tem->monster_sprite->isFlipX ())
					{
						tem->monster_speed=40;
					}else
					{
						tem->monster_speed=-40;
					}

					if(tem->monster_body ->GetLinearVelocity ()==b2Vec2 (0,0))
					{
						tem->monster_sprite ->pauseSchedulerAndActions ();

					}else
					{
						tem->monster_sprite ->resumeSchedulerAndActions ();
					}


					j++;
				}

			}
		}

		i++;
	}

}



void Tower::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}


void Tower::ccTouchesBegan (CCSet *pTouches, CCEvent *pEvent)
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
			&&m_pHero->_bJumped ==false)
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


void Tower ::ccTouchesMoved (CCSet *pTouches, CCEvent *pEvent)
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
			&&m_pHero->_bJumped ==false)
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


void Tower::ccTouchesEnded (CCSet *pTouches, CCEvent *pEvent)
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
			unschedule (schedule_selector (Tower ::for_run ));

			run_schedule =false;
		}

		if(right_control ->boundingBox ().containsPoint (tem_touch->getLocation ()))
		{
			CCLOG("right_control cancelled");
			right_pressed=false;
			unschedule (schedule_selector (Tower ::for_run ));

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

Tower::~Tower()
{

	m_pHero ->_pSprite ->removeAnimationHasEndedObserver ();

	delete loader;
	loader=NULL;

	delete m_world;
	m_world =NULL;
	/*if (m_pTowerMonsters!=NULL) {
	delete m_pSeaSprites;
	}*/
}
