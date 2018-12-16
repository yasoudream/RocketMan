#ifndef __Pillar_H__
#define __Pillar_H_

#include "Entity.h"
#include "Player.h"
/*��ÿһ�����ӹ���һ�������ӵķ���ͬʱ����һ������*/
class Pillar : public Entity
{
public:
	Pillar();
	~Pillar();
	CREATE_FUNC(Pillar);
	virtual bool init();
	Sprite* underPillar;//������

public:
	void show();//��ʾ����
	void hide();//��������
	void reset();//��������
	bool isAlive();//����
	bool isCollidWithPlayer(Player* player);//��ײ�ж�

private:
	bool m_isAlive;//�״̬
};


#endif

