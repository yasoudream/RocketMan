#include "BeginScene.h"
#include "TollgateScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* BeginScene::createScene()
{
	auto scene = Scene::create();

	auto layer = BeginScene::create();

	scene->addChild(layer);

	return scene;
}

bool BeginScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	createMenu();//������ʼ��ť
	createTitle();//��������ͼƬ

	//����BGM��Keep in Keeping on)
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM.mp3", true);

	return true;
}

void BeginScene::createTitle()
{
	//��������
	auto sprite = Sprite::create("title.png");
	//����λ��
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//����ڵ�
	this->addChild(sprite, 0);
}

void BeginScene::createMenu()
{
	//������ť
	auto Begin = MenuItemImage::create(
		"button1.png",
		"button2.png",
		CC_CALLBACK_1(BeginScene::menuBegin, this));
	//����λ��
	Begin->setPosition(Vec2(visibleSize.width / 5 * 2, visibleSize.height / 4));
	//�����˵�����Ӱ�ť
	auto menu = Menu::create(Begin, NULL);
	//����λ��
	menu->setPosition(Vec2::ZERO);
	//����ڵ�
	this->addChild(menu, 1);
}

void BeginScene::menuBegin(Ref* pSender)
{
	//ת����Ϸ������
	Director::getInstance()->replaceScene(TollgateScene::createScene());
}
