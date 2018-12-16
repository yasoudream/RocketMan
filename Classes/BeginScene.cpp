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

	createMenu();//创建开始按钮
	createTitle();//创建背景图片

	//播放BGM（Keep in Keeping on)
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM.mp3", true);

	return true;
}

void BeginScene::createTitle()
{
	//创建精灵
	auto sprite = Sprite::create("title.png");
	//设置位置
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//加入节点
	this->addChild(sprite, 0);
}

void BeginScene::createMenu()
{
	//创建按钮
	auto Begin = MenuItemImage::create(
		"button1.png",
		"button2.png",
		CC_CALLBACK_1(BeginScene::menuBegin, this));
	//设置位置
	Begin->setPosition(Vec2(visibleSize.width / 5 * 2, visibleSize.height / 4));
	//创建菜单并添加按钮
	auto menu = Menu::create(Begin, NULL);
	//设置位置
	menu->setPosition(Vec2::ZERO);
	//加入节点
	this->addChild(menu, 1);
}

void BeginScene::menuBegin(Ref* pSender)
{
	//转到游戏主场景
	Director::getInstance()->replaceScene(TollgateScene::createScene());
}
