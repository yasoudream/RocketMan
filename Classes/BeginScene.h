#ifndef __BeginScene_H__
#define __BeginScene_H__

#include "cocos2d.h"

USING_NS_CC;

class BeginScene : public Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuBegin(Ref* pSender);//开始按钮

	void createMenu();//创建开始按钮
	void createTitle();//创建背景图片

	CREATE_FUNC(BeginScene);

private:
	Vec2 origin;
	Size visibleSize;
};

#endif

