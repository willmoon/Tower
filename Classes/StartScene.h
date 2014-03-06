#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "StartLayer.h"

class StartScene : public cocos2d::CCScene
{
public:
    virtual bool init();  

    CREATE_FUNC(StartScene);
};

#endif