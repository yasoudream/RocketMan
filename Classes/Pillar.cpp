#include "Pillar.h"

Pillar::Pillar()
{
	underPillar = NULL;//初始化副柱子
	m_isAlive = false;
}

Pillar::~Pillar(){}

bool Pillar::init()
{
	return true;
}

void Pillar::show()
{
	if (getSprite() != NULL)
	{
		setVisible(true);//显示柱子
		this->underPillar->setVisible(true);//显示副柱子
		m_isAlive = true;//标记柱子为活动
	}
}

void Pillar::hide()
{
	if (getSprite() != NULL)
	{
		setVisible(false);//隐藏柱子
		this->underPillar->setVisible(false);//隐藏副柱子
		reset();//重置柱子
		m_isAlive = false;//标记柱子为非活动
	}
}

void Pillar::reset()
{
	int height = CCRANDOM_0_1() * 400 + 300;//随机生成高度
	if (getSprite() != NULL)
	{
		setPosition(Point(1030, height));//设置柱子高度
		this->underPillar->setPosition(Point(1100, height - 480));//设置副柱子高度
	}
}

bool Pillar::isAlive()
{
	return m_isAlive;
}

bool Pillar::isCollidWithPlayer(Player* player)
{
	Rect playerRect = player->getBoundingBox();//获得玩家碰撞盒
	Rect pillarRect = this->getBoundingBox();//获得柱子碰撞盒
	Rect underpillarRect = this->underPillar->getBoundingBox();//获得副柱子碰撞盒
	/*碰撞判定*/
	if (playerRect.getMaxX() > pillarRect.getMinX() && playerRect.getMaxY() > pillarRect.getMinY() && playerRect.getMinX() <= pillarRect.getMaxX() ||
		playerRect.getMaxX() > underpillarRect.getMinX() && playerRect.getMinY() < underpillarRect.getMaxY() && playerRect.getMinX() <= underpillarRect.getMaxX())
		return true;
	else
		return false;
}