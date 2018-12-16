#include "TollgateScene.h"
#include "SimpleAudioEngine.h"

int FinScore;

Scene* TollgateScene::createScene()
{
	auto scene = Scene::create();

	auto layer = TollgateScene::create();

	scene->addChild(layer);

	return scene;
}

bool TollgateScene::init()
{
	
	visibleSize = Director::getInstance()->getVisibleSize();//获取屏幕大小
	
	score = 0;//初始化分数
	
	createPlayer();	//创建玩家
	
	createMenu();//创建跳跃按钮
	
	createPillarMgr();//创建柱子管理器
	
	createScore();//创建分数板
	
	initBG();//初始化前景与背景
	
	this->scheduleUpdate();//启用Update函数

	return true;
}

void TollgateScene::update(float delta)
{
	Size mapSize = m_bgSprite1->getContentSize();//获得

	int posX1 = m_bgSprite1->getPositionX();//获取背景1的X
	int posX2 = m_bgSprite2->getPositionX();//获取背景2的X

	int posX3 = m_fSprite1->getPositionX();//获取前景1的X
	int posX4 = m_fSprite2->getPositionX();//获取前景2的X

	int posPlayerY = m_player->getPositionY();//获取玩家的Y

	/*模拟物理系统*/
	int iSpeed = 3;//背景移动速度
	int fSpeed = 6;//前景移动速度
	int jumpSpeed = 6;//人物跳跃初速度
	float gravity = 0.2;//重力

	static bool book = true;//用于降低分数增长率为两帧一分
	if (!m_player->isAlive)
		gravity = 10;
	else if (book)//加分
		score++;

	book = !book;//改变标记状态
	changeLabel(label);//刷新分数板
	
	/*移动前景与背景*/
	posX1 -= iSpeed;
	posX2 -= iSpeed;
	posX3 -= fSpeed;
	posX4 -= fSpeed;

	if (m_player->jumping)//若主角的状态为“跳起”则赋予跳跃初速度
	{
		m_player->speed = jumpSpeed;
		m_player->jumping = false;//重置“跳起”状态为false
	}

	posPlayerY += m_player->speed;//刷新玩家Y坐标

	m_player->speed -= gravity;//模拟重力
	
	/*当前景或背景出窗时，重置位置*/
	if (posX1 <= -mapSize.width / 2)
		posX1 = mapSize.width + mapSize.width / 2 - 5;

	if (posX2 <= -mapSize.width / 2)
		posX2 = mapSize.width + mapSize.width / 2 - 5;

	if (posX3 <= -mapSize.width / 2)
		posX3 = mapSize.width + mapSize.width / 2 - 15;

	if (posX4 <= -mapSize.width / 2)
		posX4 = mapSize.width + mapSize.width / 2 - 15;

	/*更新前景和背景位置*/
	m_bgSprite1->setPositionX(posX1);
	m_bgSprite2->setPositionX(posX2);
	m_fSprite1->setPositionX(posX3);
	m_fSprite2->setPositionX(posX4);

	m_player->setPositionY(posPlayerY);//更新玩家位置

	if (posPlayerY >= 620)//头顶天花板死亡
		m_player->isAlive = false;

	if (posPlayerY <= 0)//落到地面或死亡上进入结算场景
	{
		//为重开做准备
		m_player->isAlive = true;
		gravity = 0.2;
		m_player->speed = 10;
		FinScore = score;//更新全局变量：分数
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, OverScene::createScene()));//进入结算场景
	}
}

void TollgateScene::initBG()
{
	/*创建前景背景共四张精灵*/
	m_bgSprite1 = Sprite::create("BackGround.png");
	m_bgSprite1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(this->m_bgSprite1, 2);

	m_bgSprite2 = Sprite::create("BackGround.png");
	m_bgSprite2->setPosition(Point(-visibleSize.width / 2 , visibleSize.height / 2));
	m_bgSprite2->setFlippedX(true);
	this->addChild(this->m_bgSprite2, 2);

	m_fSprite1 = Sprite::create("front.png");
	m_fSprite1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(this->m_fSprite1, 6);

	m_fSprite2 = Sprite::create("front.png");
	m_fSprite2->setPosition(Point(-visibleSize.width / 2, visibleSize.height / 2));
	m_fSprite2->setFlippedX(true);
	this->addChild(this->m_fSprite2, 6);
}

void TollgateScene::jumpEvent(Ref* button)//跳跃事件
{
	this->m_player->jumping = true;
}

void TollgateScene::createMenu()
{
	//创建Menu
	auto _menu = Menu::create();

	//设置Menu位置属性
	_menu->setPosition(Vec2::ZERO);

	//创建精灵，分别为正常和按下时显示
	auto _spriteNormal = Sprite::create("button3.png");
	auto _spritePress = Sprite::create("button4.png");

	//创建menuItemSprite
	auto _menuItemSprite = MenuItemSprite::create(_spriteNormal, _spritePress, CC_CALLBACK_1(TollgateScene::jumpEvent, this));

	//设置menuItemSprite位置属性
	_menuItemSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 8));

	//将menuItemSprite添加到Menu上
	_menu->addChild(_menuItemSprite);

	//将Menu添加到父节点层上
	this->addChild(_menu, 7);
}

void TollgateScene::changeLabel(Label* oldLabel)
{
	//数字转字符串中介
	char ch[20];
	char ch2[40] = "SCROE:";
	//删除原计分板
	this->removeChild(oldLabel);
	//分数转字符串
	sprintf(ch, "%15d",this->score);
	strcat(ch2, ch);
	//新建分数板
	Label* newLabel = Label::createWithTTF(ch2, "Marker Felt.ttf", 30);
	newLabel->setPosition(Vec2(visibleSize.width / 6, visibleSize.height / 2));
	//更新分数板
	label = newLabel;
	//加入节点
	this->addChild(label, 5);
}

void TollgateScene::createPlayer()
{
	m_player = Player::create();
	m_player->bindSprite(Sprite::create("player.png"));
	m_player->setPosition(Point(visibleSize.width / 3, visibleSize.height / 2));
	createAnimate();
	this->addChild(m_player, 4);
}

void TollgateScene::createScore()
{
	label = Label::createWithTTF("SCORE:              0", "Marker Felt.ttf", 30);
	label->setPosition(Vec2(visibleSize.width / 6, visibleSize.height / 2));
}

void TollgateScene::createPillarMgr()
{
	pillarMgr = PillarManager::create();
	pillarMgr->bindPlayer(m_player);//绑定玩家
	this->addChild(pillarMgr, 3);
}


void TollgateScene::createAnimate()
{
	Vector<SpriteFrame*> frameVec;//建容器
	//置入动画帧
	frameVec.pushBack(SpriteFrame::create(StringUtils::format("player.png"), Rect(0, 0, 50, 50)));
	frameVec.pushBack(SpriteFrame::create(StringUtils::format("player2.png"), Rect(0, 0, 50, 50)));
	frameVec.pushBack(SpriteFrame::create(StringUtils::format("player3.png"), Rect(0, 0, 50, 50)));

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);

	Animate* action = Animate::create(animation);

	m_player->getSprite()->runAction(action);

}