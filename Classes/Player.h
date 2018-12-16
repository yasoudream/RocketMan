#ifndef __Player_H__
#define __Player_H__

#include "cocos2d.h"
#include "Entity.h"

USING_NS_CC;

#define JUMP_ACTION_TAG 1

class Player : public Entity
{
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	virtual bool init();

	bool jumping;//��Ծ״̬
	float speed;//Y���ٶ�
	bool isAlive;//�����
};

#endif
