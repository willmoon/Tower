#include "TowerScene.h"

bool TowerScene::init()
{
	tower=Tower::create ();

	addChild (tower);

	return true;
}

TowerScene::~TowerScene()
{
	CCLOG("TowerScene destructed");

	tower->autorelease();
}