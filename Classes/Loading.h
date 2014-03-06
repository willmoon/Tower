#ifndef _LOADING_H
#define _LOADING_H
#include "TowerScene.h"
#include "cocos2d.h"
#include "Defines.h"

class Loading :public cocos2d::CCScene
{
public:
	virtual bool init();

	void load(float dt);

	CREATE_FUNC(Loading);
};
#endif