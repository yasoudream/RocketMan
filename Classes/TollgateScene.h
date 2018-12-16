#ifndef __TollgateScene_H__
#define __TollgateScene_H__

#include "PillarManager.h"
#include "cocos2d.h"
#include "Player.h"
#include "OverScene.h"

USING_NS_CC;

class TollgateScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TollgateScene);

	void createMenu();//�����˵�
	void createPlayer();//�������
	void createScore();//����������
	void createPillarMgr();//�������ӹ�����

	virtual void update(float delta);

	void changeLabel(Label* oldLabel);//ˢ�·�����
	void createAnimate();

private:
	void initBG();


private:
	/*ǰ����������*/
	Sprite* m_bgSprite1;
	Sprite* m_bgSprite2;
	Sprite* m_fSprite1;
	Sprite* m_fSprite2;
	
	Size visibleSize;//���ڴ�С

	Player* m_player;//���

	PillarManager* pillarMgr;//���ӹ�����

	Label* label;//������

	int score;//����

	void jumpEvent(Ref* button);//��Ծ
};


#endif
