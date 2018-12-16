#ifndef __PillarManager_H__
#define __PillarManager_H__

#include "Pillar.h"

#define MAX_PILLAR_NUM 4//�����������������С��

class PillarManager : public Node
{
public:
	CREATE_FUNC(PillarManager);
	virtual bool init();

	virtual void update(float dt);
	//�����
	void bindPlayer(Player* player);
private:
	//��������
	void createPillars();

private:
	//��������
	Vector<Pillar*> m_pillarArr;
	//���󶨵����
	Player* m_player;
};


#endif

