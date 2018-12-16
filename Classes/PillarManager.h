#ifndef __PillarManager_H__
#define __PillarManager_H__

#include "Pillar.h"

#define MAX_PILLAR_NUM 4//最大柱子数（容器大小）

class PillarManager : public Node
{
public:
	CREATE_FUNC(PillarManager);
	virtual bool init();

	virtual void update(float dt);
	//绑定玩家
	void bindPlayer(Player* player);
private:
	//生成柱子
	void createPillars();

private:
	//柱子容器
	Vector<Pillar*> m_pillarArr;
	//被绑定的玩家
	Player* m_player;
};


#endif

