#ifndef __OverScene_H__
#define __OverScene_H__

#include "cocos2d.h"

USING_NS_CC;

class OverScene : public Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallback(Ref* pSender);
	void menuRestartCallback(Ref* pSender);
	void createMenu();
	void createLabel();
	void createBG();

	CREATE_FUNC(OverScene);

private:
	Size visibleSize;
};

#endif
