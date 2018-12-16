#ifndef __BeginScene_H__
#define __BeginScene_H__

#include "cocos2d.h"

USING_NS_CC;

class BeginScene : public Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuBegin(Ref* pSender);//��ʼ��ť

	void createMenu();//������ʼ��ť
	void createTitle();//��������ͼƬ

	CREATE_FUNC(BeginScene);

private:
	Vec2 origin;
	Size visibleSize;
};

#endif

