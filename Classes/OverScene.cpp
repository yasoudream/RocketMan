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

	createMenu();//������ť
	createBG();//��������
	createLabel();//����������

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
	//����ת�ַ���
	char ch[50];
	char ch2[50] = "SCORE:";
	sprintf(ch, "%d", FinScore);
	strcat(ch2, ch);
	//����������
	Label* newLabel = Label::createWithTTF(ch2, "Marker Felt.ttf", 36);
	newLabel->setPosition(Vec2(visibleSize.width / 5 * 4, visibleSize.height / 4 * 3));
	//����ڵ�
	this->addChild(newLabel, 5);
}

void OverScene::createMenu()
{
	//������ť
	auto closeItem = MenuItemImage::create(
		"button5.png",
		"button6.png",
		CC_CALLBACK_1(OverScene::menuCloseCallback, this));
	//����λ��
	closeItem->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 4 - 40));

	//������ť
	auto RestartItem = MenuItemImage::create(
		"button7.png",
		"button8.png",
		CC_CALLBACK_1(OverScene::menuRestartCallback, this));
	//����λ��
	RestartItem->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 4 + 50));

	//�����˵�
	auto menu = Menu::create(RestartItem, closeItem, NULL);

	menu->setPosition(Vec2::ZERO);
	//����ڵ�
	this->addChild(menu, 1);
}

void OverScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();//����

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void OverScene::menuRestartCallback(Ref* pSender)
{
	CCDirector::sharedDirector()->replaceScene(TollgateScene::createScene());
}
