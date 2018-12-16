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

	void createMenu();//创建菜单
	void createPlayer();//创建玩家
	void createScore();//创建分数板
	void createPillarMgr();//创建柱子管理器

	virtual void update(float delta);

	void changeLabel(Label* oldLabel);//刷新分数板
	void createAnimate();

private:
	void initBG();


private:
	/*前景背景精灵*/
	Sprite* m_bgSprite1;
	Sprite* m_bgSprite2;
	Sprite* m_fSprite1;
	Sprite* m_fSprite2;
	
	Size visibleSize;//窗口大小

	Player* m_player;//玩家

	PillarManager* pillarMgr;//柱子管理器

	Label* label;//分数板

	int score;//分数

	void jumpEvent(Ref* button);//跳跃
};


#endif
