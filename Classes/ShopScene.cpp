#include "ShopScene.h"

bool ShopScene::init()
{
	addChild (ShopScene::create ());

	return true;
}