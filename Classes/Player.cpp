#include "Player.h"

Player::Player(){}

Player::~Player(){}

bool Player::init()
{
	this->jumping = true;//����С��
	this->speed = 0;//��ʼ���ٶ�
	this->isAlive = true;//��ʼ�����
	return true;
}
