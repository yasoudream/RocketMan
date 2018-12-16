#include "Player.h"

Player::Player(){}

Player::~Player(){}

bool Player::init()
{
	this->jumping = true;//开局小跳
	this->speed = 0;//初始化速度
	this->isAlive = true;//初始化存活
	return true;
}
