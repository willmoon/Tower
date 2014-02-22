#include "Hero.h"
Hero::Hero(void)
{
	_pBody =NULL;
	_pSprite =NULL;
	_iSpeed =0;
	_iState =0;
	_bAlive =true;
	_bJumped =false;

}


Hero::~Hero(void)
{
}
