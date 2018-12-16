#ifndef __Pillar_H__
#define __Pillar_H_

#include "Entity.h"
#include "Player.h"
/*用每一根柱子挂载一根副柱子的方法同时管理一对柱子*/
class Pillar : public Entity
{
public:
	Pillar();
	~Pillar();
	CREATE_FUNC(Pillar);
	virtual bool init();
	Sprite* underPillar;//副柱子

public:
	void show();//显示柱子
	void hide();//隐藏柱子
	void reset();//重置柱子
	bool isAlive();//活动标记
	bool isCollidWithPlayer(Player* player);//碰撞判定

private:
	bool m_isAlive;//活动状态
};


#endif

