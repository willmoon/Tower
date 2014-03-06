#ifndef __SHOP_SCENE_H__
#define __SHOP_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Tower.h"

class ShopScene : public cocos2d::CCScene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
   

    // implement the "static node()" method manually
    CREATE_FUNC(ShopScene);
};

#endif