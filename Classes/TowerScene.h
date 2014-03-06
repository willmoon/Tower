#ifndef __TOWER_SCENE_H__
#define __TOWER_SCENE_H__

#include "cocos2d.h"
#include "Tower.h"

class TowerScene : public cocos2d::CCScene
{
public:
    virtual bool init();  
   
	cocos2d::CCLayer *tower;

	~TowerScene ();

    CREATE_FUNC(TowerScene);
};

#endif