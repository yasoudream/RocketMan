#include "PillarManager.h"
#include "Player.h"

bool PillarManager::init()
{
	//创建柱子
	createPillars();
	//启用Update函数
	this->scheduleUpdate();
	return true;
}

void PillarManager::createPillars()
{
	//初始化柱子和柱子精灵
	Pillar* pillar = NULL;
	Sprite* sprite = NULL;

	for (int i = 0; i < MAX_PILLAR_NUM; i++)
	{
		pillar = Pillar::create();
		//绑柱子和副柱子的精灵
		pillar->bindSprite(Sprite::create("pillar.png"));
		pillar->underPillar = Sprite::create("pillar.png");

		Size size = pillar->underPillar->getContentSize();
		pillar->underPillar->setPosition(Point(size.width * 0.5f, size.height * 0.5f));
		pillar->underPillar->setFlippedY(true);//翻转副柱子图片
		//隐藏初始柱子
		pillar->hide();
		//加入节点
		this->addChild(pillar);
		this->addChild(pillar->underPillar);
		//置入容器
		m_pillarArr.pushBack(pillar);
	}
}

void PillarManager::update(float dt)
{
	static int count = 0;//帧数计数器，用于控制输出柱子
	
	for (auto pillar : m_pillarArr)//遍历容器
	{
		if (pillar->isAlive())//要是柱子活动
		{
			pillar->setPositionX(pillar->getPositionX() - 4);//移动柱子
			pillar->underPillar->setPositionX(pillar->underPillar->getPositionX() - 4);//移动副柱子
			if (pillar->getPositionX() < -150)//若柱子移出了画面，隐藏柱子
			{
				pillar->hide();
			}
			else if (pillar->isCollidWithPlayer(m_player))//若与玩家发生碰撞
			{
					m_player->isAlive = false;//玩家死亡
			}
		}
		else if(count == 0)
		{
			pillar->show();//重新出现柱子
			count++;//刷新参数
		}
	}

	count++;//刷新参数
	if (count == 120)//每120帧放出一根柱子
		count = 0;
}

void PillarManager::bindPlayer(Player* player)
{
	m_player = player;
}