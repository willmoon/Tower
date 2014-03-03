#include "Tower.h"
#include "platform\CCFileUtils.h"

using namespace cocos2d;

bool Tower::init()
{

	//设置操作层
	set_operating ();

	m_iLevel=1;  //第几关
	lock=false;	//进入下一关的时候的锁

	//设置关卡
	setLevel (m_iLevel);

	//设置英雄
	set_hero();


	//设置碰撞检测
	contactListener=new MyContactListener();
	m_world->SetContactListener(contactListener);

	schedule(schedule_selector(Tower ::monster_patrol),0.2f);

	setAccelerometerEnabled (true);
	setTouchEnabled (true);

	scheduleUpdate();
	return true;
}

//更新herobody的动作
void Tower::updateHero ()
{
	//CCLOG ("-----------------------%f",m_pHero ->_pBody ->GetPosition ().y*PTM_RATIO);
	if(m_pHero->_bAlive )
	{

		if(
			m_pHero ->_pBody ->GetPosition ().y <(m_iLevel -3/5)*
			WINSIZE .height /PTM_RATIO&&
			m_pHero->_pBody->GetLinearVelocity ().y>=-1/PTM_RATIO&&
			m_pHero->_pBody->GetLinearVelocity ().y <1/PTM_RATIO
			)
		{
			m_pHero->_bJumped =false;
		}
		else 
		{
			m_pHero->_bJumped =true;
		}

		//攻击
		if(rocker ->isAttack)
		{
			if(m_pHero ->_pSprite ->numberOfRunningActions () == 0)
			{
				m_pHero ->_pSprite ->runAction (CCSequence ::create (m_pHero ->hero_attack ,
					CCCallFuncN ::actionWithTarget 
					(this,callfuncN_selector (Tower::normalstate)),NULL));
			}
			else
			{
				m_pHero ->_pSprite ->stopAllActions ();

				m_pHero ->_pSprite ->runAction (CCSequence ::create (m_pHero ->hero_attack ,
					CCCallFuncN ::actionWithTarget 
					(this,callfuncN_selector (Tower::normalstate)),NULL));
			}

			rocker ->isAttack=false;
			rocker ->setVisible (false);
		}
		//向上移动
		if(rocker ->getDirection ().y<-0.9&&!m_pHero ->_bJumped
			&&rocker ->getVelocity ()>30.0f)
		{
			m_pHero ->_pBody ->SetLinearVelocity (b2Vec2 (0,300/PTM_RATIO));
		}
		//向右移动
		if(rocker ->getDirection ().x<0&&rocker ->getDirection ().y>-0.2
			&&rocker ->getDirection ().y <0.7&&rocker ->getVelocity ()>10.0f
			&&!m_pHero ->_bJumped)
		{
			m_pHero ->_pSprite ->setFlipX (false);

			if(m_pHero ->_pSprite ->numberOfRunningActions () == 0)
			{
				m_pHero ->_pSprite ->runAction (m_pHero ->hero_walk);
			}

			m_pHero ->_pBody ->SetLinearVelocity (b2Vec2 (4*rocker ->getVelocity ()/PTM_RATIO,0));

		}
		//向右上移动
		if(rocker ->getDirection ().x<0&&rocker ->getDirection ().y <=-0.2&&
			rocker ->getDirection ().y>=-0.9&&!m_pHero ->_bJumped&&rocker ->getVelocity ()>30.0f)
		{
			m_pHero ->_pSprite ->setFlipX (false);

			if(m_pHero ->_pSprite ->numberOfRunningActions () == 0)
			{
				m_pHero ->_pSprite ->runAction (CCSequence ::create (m_pHero ->hero_jump ,
					CCCallFuncN ::actionWithTarget 
					(this,callfuncN_selector (Tower::normalstate)),NULL));
			}
			else
			{
				m_pHero ->_pSprite ->stopAllActions ();

				m_pHero ->_pSprite ->runAction (CCSequence ::create (m_pHero ->hero_jump ,
					CCCallFuncN ::actionWithTarget 
					(this,callfuncN_selector (Tower::normalstate)),NULL));
			}

			m_pHero ->_pBody ->SetLinearVelocity (b2Vec2 (200/PTM_RATIO ,
				300/PTM_RATIO));
		}

		//向左移动
		if(rocker ->getDirection ().x>0&&rocker ->getDirection ().y>-0.2
			&&rocker ->getDirection ().y <0.7&&rocker ->getVelocity ()>10.0f
			&&!m_pHero ->_bJumped)
		{
			m_pHero ->_pSprite ->setFlipX (true);

			if(m_pHero ->_pSprite ->numberOfRunningActions () == 0)
			{
				m_pHero ->_pSprite ->runAction (m_pHero ->hero_walk);
			}

			m_pHero ->_pBody ->SetLinearVelocity (b2Vec2 (-5*rocker ->getVelocity ()/PTM_RATIO,0));
		}
		//向左上移动
		if(rocker ->getDirection ().x>0&&rocker ->getDirection ().y <=-0.2&&
			rocker ->getDirection ().y>=-0.8&&!m_pHero ->_bJumped
			&&rocker ->getVelocity ()>30)
		{
			m_pHero ->_pSprite ->setFlipX (true);

			if(m_pHero ->_pSprite ->numberOfRunningActions () == 0)
			{
				m_pHero ->_pSprite ->runAction (CCSequence ::create (m_pHero ->hero_jump ,
					CCCallFuncN ::actionWithTarget 
					(this,callfuncN_selector (Tower::normalstate)),NULL));
			}
			else
			{
				m_pHero ->_pSprite ->stopAllActions ();

				m_pHero ->_pSprite ->runAction (CCSequence ::create (m_pHero ->hero_jump ,
					CCCallFuncN ::actionWithTarget 
					(this,callfuncN_selector (Tower::normalstate)),NULL));
			}

			m_pHero ->_pBody ->SetLinearVelocity (b2Vec2 (-200/PTM_RATIO ,
				300/PTM_RATIO));

		}

	}
}

void Tower::loadingProgress(float progressValue){
	CCLog("LOAD PROGRESS IS %f", progressValue);    
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
	int temp;
	/*
	*当hero在WINSIZE.width/2到320*（m_iLevel+1）-WINSIZE.height/2的时候，
	*移动背景层来模拟hero的移动.此过程中hero的position始终在变且在屏幕中间。
	*说明CCLayer中的object的position是相对的？？？
	*/
	int x = MAX(position.x, WINSIZE.width / 2);
	int y = MAX(position.y, WINSIZE.height / 2);
	x = MIN(x, (568*6) - WINSIZE.width / 2);
	y = MIN(y, 320*(m_iLevel+1) - WINSIZE.height / 2 );
	CCPoint actualPosition = ccp(x, y);

	temp = m_iLevel >1 ? 1:0;	//矫正值

	CCPoint centerOfView = ccp(WINSIZE.width / 2, WINSIZE.height/2-38*temp);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	CCPoint operating_layer_point = ccpSub(actualPosition,centerOfView );

	this->setPosition(viewPoint);
	operating_layer ->setPosition (operating_layer_point);
}


void Tower::normalstate(CCNode *pSender)
{
	CCLOG("-----------------------------------------------after action to be normal");
	m_pHero ->_pSprite ->runAction (m_pHero ->hero_walk );
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
		if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL)
		{
			CCSprite *spriteA = (CCSprite *) bodyA->GetUserData();
			CCSprite *spriteB = (CCSprite *) bodyB->GetUserData();

			//CCLOG("spriteA--%s,spriteB--%s",spriteA ->description (),spriteB ->description ());

			// Sprite A = hero, Sprite B = monster
			if (spriteA->getTag () ==1&& spriteB->getTag () ==-1) 
			{
				if (std::find(toDestroy.begin(), toDestroy.end(), bodyB) 
					== toDestroy.end()) 
				{
					if(rocker->isAttack)
						toDestroy.push_back(bodyB);

				}
			}
			// Sprite B = hero, Sprite A = monster
			else if (spriteA->getTag () ==-1&& spriteB->getTag () ==1)
			{
				if (std::find(toDestroy.begin(), toDestroy.end(), bodyA) 
					== toDestroy.end()) 
				{
					//bodyA不在toDestroy中
					if(rocker->isAttack)
						toDestroy.push_back(bodyA);

				}
			}
			//spriteA为hero
			else if(spriteA->getTag ()==1&&spriteB->getTag ()==2)
			{
				//与火焰碰撞,受伤
				CCLOG("-----hit stone");

				if(m_pHero ->_pSprite ->numberOfRunningActions () ==0)
				{
					m_pHero ->_pSprite ->runAction (CCSequence ::create (m_pHero ->hero_hurt ,
						CCCallFuncN ::actionWithTarget 
						(this,callfuncN_selector (Tower::normalstate)),NULL));
				}
				else
				{
					m_pHero ->_pSprite ->stopAllActions ();
					m_pHero ->_pSprite ->runAction (CCSequence ::create (m_pHero ->hero_hurt ,
						CCCallFuncN ::actionWithTarget 
						(this,callfuncN_selector (Tower::normalstate )),NULL));
				}

				if(spriteA->getPositionX ()<spriteB ->getPositionX ())
				{
					m_pHero ->_pBody ->SetLinearVelocity (b2Vec2 (-100/PTM_RATIO ,50/PTM_RATIO ));
				}
				else
				{
					m_pHero ->_pBody ->SetLinearVelocity (b2Vec2 (100/PTM_RATIO ,50/PTM_RATIO ));
				}

			}
			//spriteB为hero
			else if(spriteB->getTag ()==1&&spriteA->getTag ()==2)
			{
				//与沉锤碰撞
				CCLOG("-------------hit fire");

				if(m_pHero ->_pSprite ->numberOfRunningActions () ==0)
				{
					m_pHero ->_pSprite ->runAction (CCSequence ::create (m_pHero ->hero_hurt ,
						CCCallFuncN ::actionWithTarget 
						(this,callfuncN_selector (Tower::normalstate )),NULL));
				}
				else
				{
					m_pHero ->_pSprite ->stopAllActions ();

					m_pHero ->_pSprite ->runAction (CCSequence ::create (m_pHero ->hero_hurt ,
						CCCallFuncN ::actionWithTarget 
						(this,callfuncN_selector (Tower::normalstate )),NULL));
				}

				if(spriteB->getPositionX ()<spriteA ->getPositionX ())
				{
					m_pHero ->_pBody ->SetLinearVelocity (b2Vec2 (-100/PTM_RATIO ,50/PTM_RATIO ));
				}
				else
				{
					m_pHero ->_pBody ->SetLinearVelocity (b2Vec2 (100/PTM_RATIO ,50/PTM_RATIO ));
				}

			}

			spriteA=NULL;
			spriteB=NULL;
		} 

	}


	std::list<b2Body *>::iterator pos2;
	for(pos2=toDestroy .begin(); pos2 != toDestroy.end(); ++pos2) 
	{
		b2Body *body =*pos2; 

		if (body->GetUserData() != NULL)
		{
			for(map<int ,list<Monster*>>::iterator i=m_pTowerMonsters  .begin ();i!=m_pTowerMonsters .end ();)
			{
				if(!(i->second.empty()))
				{
					for(list<Monster *>::iterator j=i->second .begin ();j!=i->second .end ();)
					{
						Monster* tem=*j;

						if(body!=NULL&&tem->monster_sprite ==body->GetUserData ())
						{
							//i->second .erase( j++);
							tem->monster_sprite ->stopAllActions ();
							tem->monster_sprite ->runAction (tem->die_action);//???????????????m_uReference??retain????
							tem->m_bisalive =false;
							tem->monster_sprite =NULL ;


							//m_world->DestroyBody(body);
							//body=NULL;	

							//tem->monster_fixture =NULL ;
							//delete tem;
							//tem =NULL ;
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

void Tower::gotonx(float dt)
{
	m_iLevel +=1;

	//释放上一关，加载下一关
	if(m_iLevel %2 == 0)
	{
		loader->release ();

		loader = new LevelHelperLoader((CCString ::createWithFormat 
			("levels/level%d01.plhs",m_iLevel%5 + 1))->getCString ());//耗时1、2
		loader ->loadLevelsWithOffset (ccp(0,-640*m_iLevel));
		loader->addObjectsToWorld(m_world ,this);//加载图片的原因

	}
	else
	{
		next_loader->release ();

		next_loader = new LevelHelperLoader((CCString ::createWithFormat 
			("levels/level%d01.plhs",m_iLevel%5 + 1))->getCString ());
		next_loader ->loadLevelsWithOffset (ccp(0,-640*m_iLevel));
		next_loader->addObjectsToWorld(m_world ,this);

	}


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

	setLevel (m_iLevel);

	//进入下一关的lock解锁
	lock =false;
}

void Tower::update(float dt)
{
	if(m_iLevel%2==1&&
		m_pHero ->_pBody ->GetPosition ().x>568*6/PTM_RATIO &&!lock)
	{
		lock=true;
		CCLOG("-------------go to next");
		m_pHero ->_pBody ->SetLinearVelocity (b2Vec2 (-1,15));

		m_pHero ->_pSprite ->setFlipX (true);

		scheduleOnce (schedule_selector (Tower::gotonx ),1);
	}
	else if(m_iLevel%2==0&&
		m_pHero ->_pBody ->GetPosition ().x<0/PTM_RATIO &&!lock)
	{
		lock=true;
		CCLOG("-------------go to next");
		m_pHero ->_pBody ->SetLinearVelocity (b2Vec2 (1,15));

		m_pHero ->_pSprite ->setFlipX (false);

		scheduleOnce (schedule_selector (Tower::gotonx ),1);
	}

	//碰撞效果检测
	afterHit ();
	//更新hero状态
	updateHero();

	//保证视图
	setViewpointCenter(ccp(m_pHero ->_pBody ->GetPosition ().x*PTM_RATIO,
		m_pHero ->_pBody ->GetPosition ().y *PTM_RATIO ));

	//更新monster状态
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


//monster设置图
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
	if(1==m_iLevel)
	{
		m_pGroudBody =NULL ;
		m_pWallBody =NULL ;

		//加载关卡到世界
		m_world = new b2World(b2Vec2(0,-10));
		m_world->SetContinuousPhysics(true);

		loader = new LevelHelperLoader((CCString ::createWithFormat 
			("levels/level%d01.plhs",m_iLevel ))->getCString ());
		loader->addObjectsToWorld(m_world ,this);

		next_loader = new LevelHelperLoader((CCString ::createWithFormat 
			("levels/level%d01.plhs",m_iLevel +2))->getCString ());
		next_loader ->loadLevelsWithOffset (ccp(0,-640*m_iLevel));
		next_loader ->addObjectsToWorld (m_world ,this);

	}

	//销毁上一关的边界
	if(m_pGroudBody !=NULL )
	{
		m_world ->DestroyBody (m_pGroudBody);
		m_pGroudBody =NULL ;
	}

	if(m_pWallBody !=NULL )
	{
		m_world ->DestroyBody (m_pWallBody);
		m_pWallBody =NULL ;
	}

	//建立关卡边界
	b2BodyDef groundBodyDef;
	groundBodyDef .position .SetZero ();//???
	m_pGroudBody =m_world ->CreateBody (&groundBodyDef);

	b2EdgeShape groundEdge;
	b2FixtureDef shapeDef;
	shapeDef.shape =&groundEdge ;
	groundEdge .Set (
		b2Vec2(0,(320*(m_iLevel -1)+70)/PTM_RATIO),
		b2Vec2(6*WINSIZE.width/PTM_RATIO,(320*(m_iLevel -1)+70)/PTM_RATIO )
		);

	m_pGroudBody ->CreateFixture(&shapeDef);

	int tem;//wall的x 位置
	tem= (m_iLevel %2 ==0 ? 6:0);
	//建立墙的边界
	b2BodyDef wallBodyDef;
	wallBodyDef .position .SetZero ();
	m_pWallBody =m_world ->CreateBody (&wallBodyDef);

	b2EdgeShape wallEdge;
	b2FixtureDef wallshapeDef;
	wallshapeDef .shape =&wallEdge ;
	wallEdge .Set (
		b2Vec2(tem*WINSIZE.width/PTM_RATIO,320*(m_iLevel -1)/PTM_RATIO),
		b2Vec2(tem*WINSIZE.width/PTM_RATIO,(320*m_iLevel)/PTM_RATIO )
		);
	m_pWallBody ->CreateFixture (&wallshapeDef);



	//读取关卡文件，可以在一组同难度的关卡中进行随机
	CCString *xml_path=CCString::createWithFormat ("settings/%d.xml",m_iLevel%7 +1);

	TiXmlDocument doc(xml_path->getCString ());
	bool loadok=doc.LoadFile ();
	if(!loadok)
	{
		CCLOG("------------load xml failed");
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
		monster.y = 40+random%((int)CCDirector::sharedDirector()->getWinSize().width -40);
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
			(CCString ::createWithFormat ("monster_%d_run",monster .type )->getCString ()));

		CCAction *temdie=CCAnimate::create(CCAnimationCache ::sharedAnimationCache ()->animationByName 
			(CCString ::createWithFormat ("monster_%d_die",monster .type )->getCString ()));

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
		tem_monster->monsterBodyDef .position .Set ((200+1000*monster .x )/PTM_RATIO ,(100+(m_iLevel-1) *320)/PTM_RATIO);
		tem_monster->monsterBodyDef .userData =tem_monster->monster_sprite ;

		tem_monster->monster_body = m_world->CreateBody(&tem_monster->monsterBodyDef);
		tem_monster->monster_body ->SetFixedRotation (true);

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





void Tower::set_operating ()
{
	operating_layer =CCLayer::create();
	operating_layer ->setAnchorPoint (ccp(0,0));
	operating_layer ->setPosition (ccp(0,0));

	addChild (operating_layer,20);

	CCSprite *spRocker=CCSprite::create("settings/yg2.png");//摇杆
	CCSprite *spRockerBG=CCSprite::create("settings/yg1.png");//摇杆背景

	spRocker ->setScale (0.8f);
	spRockerBG ->setScale (0.8f);

	spRockerBG ->setOpacity (150);

	rocker=HRocker::HRockerWithCenter
		(ccp(100.0f,250.0f),50.0f ,spRocker ,spRockerBG,true);//创建摇杆

	operating_layer->addChild(rocker);
}


void Tower::set_hero()
{
	m_pHero =new Hero ();
	addChild (m_pHero->_pSprite,99,1);//标号tag为1

	//设定body信息
	m_pHero ->hero_bodyDef .type =b2_dynamicBody ;
	m_pHero ->hero_bodyDef .position .Set (100/PTM_RATIO ,190/PTM_RATIO);
	m_pHero ->hero_bodyDef .userData =m_pHero->_pSprite ;
	m_pHero ->_pBody =m_world ->CreateBody (&m_pHero ->hero_bodyDef);

	m_pHero ->_pBody ->SetFixedRotation (true);   //禁止旋转

	//设定shape信息
	m_pHero ->hero_shape .SetAsBox (
		m_pHero ->_pSprite ->getContentSize ().width/PTM_RATIO /10,
		m_pHero ->_pSprite ->getContentSize ().height /PTM_RATIO /6
		);
	b2FixtureDef shapeDef;
	shapeDef.shape =&m_pHero ->hero_shape ;
	shapeDef.density =4.0f;
	shapeDef.friction =5.0f;
	shapeDef.restitution =0.01f;
	//shapeDef.filter.groupIndex =-1;

	//通过fixture 把body和shape信息绑定
	m_pHero ->_phero_fixture =m_pHero ->_pBody ->CreateFixture (&shapeDef);

	//绑定动作
	//攻击动画
	m_pHero ->hero_attack =CCAnimate ::create (CCAnimationCache ::sharedAnimationCache ()
		->animationByName (CCString ::createWithFormat ("1climb")->getCString ())) ;
	m_pHero ->hero_attack ->retain ();

	//行走动画
	m_pHero ->hero_walk =CCAnimate ::create (CCAnimationCache ::sharedAnimationCache ()
		->animationByName (CCString ::createWithFormat ("1rrun")->getCString ()));
	m_pHero ->hero_walk ->retain ();
	/*m_pHero ->_pSprite ->runAction (CCRepeatForever ::create (
	m_pHero ->hero_walk) );*/

	//跳跃动画
	m_pHero ->hero_jump =CCAnimate ::create (CCAnimationCache ::sharedAnimationCache ()
		->animationByName (CCString ::createWithFormat ("1rjump")->getCString ()));
	m_pHero ->hero_jump ->retain ();

	//受伤动画
	m_pHero ->hero_hurt =CCAnimate ::create (CCAnimationCache ::sharedAnimationCache ()
		->animationByName (CCString ::createWithFormat ("1hurt")->getCString ()));
	m_pHero ->hero_hurt ->retain ();
}


Tower::~Tower()
{

	delete loader;
	loader=NULL;

	delete m_world;
	m_world =NULL;
	/*if (m_pTowerMonsters!=NULL) {
	delete m_pSeaSprites;
	}*/
}
