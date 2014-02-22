#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "StartLayer.h"

class StartScene : public cocos2d::CCScene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
   

    // implement the "static node()" method manually
    CREATE_FUNC(StartScene);
};

#endif