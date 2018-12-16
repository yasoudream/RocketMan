#include "OverScene.h"
#include "SimpleAudioEngine.h"
#include "TollgateScene.h"

USING_NS_CC;

extern int FinScore;

Scene* OverScene::createScene()
{
	auto scene = Scene::create();

	auto layer = OverScene::create();

	scene->addChild(layer);

	return scene;
}

bool OverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	createMenu();//创建按钮
	createBG();//创建背景
	createLabel();//创建分数板

	return true;
}

void OverScene::createBG()
{
	auto sprite = Sprite::create("end.png");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite, 0);
}

void OverScene::createLabel()
{
	//数字转字符串
	char ch[50];
	char ch2[50] = "SCORE:";
	sprintf(ch, "%d", FinScore);
	strcat(ch2, ch);
	//创建分数板
	Label* newLabel = Label::createWithTTF(ch2, "Marker Felt.ttf", 36);
	newLabel->setPosition(Vec2(visibleSize.width / 5 * 4, visibleSize.height / 4 * 3));
	//加入节点
	this->addChild(newLabel, 5);
}

void OverScene::createMenu()
{
	//创建按钮
	auto closeItem = MenuItemImage::create(
		"button5.png",
		"button6.png",
		CC_CALLBACK_1(OverScene::menuCloseCallback, this));
	//设置位置
	closeItem->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 4 - 40));

	//创建按钮
	auto RestartItem = MenuItemImage::create(
		"button7.png",
		"button8.png",
		CC_CALLBACK_1(OverScene::menuRestartCallback, this));
	//设置位置
	RestartItem->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 4 + 50));

	//创建菜单
	auto menu = Menu::create(RestartItem, closeItem, NULL);

	menu->setPosition(Vec2::ZERO);
	//加入节点
	this->addChild(menu, 1);
}

void OverScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();//结束

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void OverScene::menuRestartCallback(Ref* pSender)
{
	CCDirector::sharedDirector()->replaceScene(TollgateScene::createScene());
}
