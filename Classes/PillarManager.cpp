#include "PillarManager.h"
#include "Player.h"

bool PillarManager::init()
{
	//��������
	createPillars();
	//����Update����
	this->scheduleUpdate();
	return true;
}

void PillarManager::createPillars()
{
	//��ʼ�����Ӻ����Ӿ���
	Pillar* pillar = NULL;
	Sprite* sprite = NULL;

	for (int i = 0; i < MAX_PILLAR_NUM; i++)
	{
		pillar = Pillar::create();
		//�����Ӻ͸����ӵľ���
		pillar->bindSprite(Sprite::create("pillar.png"));
		pillar->underPillar = Sprite::create("pillar.png");

		Size size = pillar->underPillar->getContentSize();
		pillar->underPillar->setPosition(Point(size.width * 0.5f, size.height * 0.5f));
		pillar->underPillar->setFlippedY(true);//��ת������ͼƬ
		//���س�ʼ����
		pillar->hide();
		//����ڵ�
		this->addChild(pillar);
		this->addChild(pillar->underPillar);
		//��������
		m_pillarArr.pushBack(pillar);
	}
}

void PillarManager::update(float dt)
{
	static int count = 0;//֡�������������ڿ����������
	
	for (auto pillar : m_pillarArr)//��������
	{
		if (pillar->isAlive())//Ҫ�����ӻ
		{
			pillar->setPositionX(pillar->getPositionX() - 4);//�ƶ�����
			pillar->underPillar->setPositionX(pillar->underPillar->getPositionX() - 4);//�ƶ�������
			if (pillar->getPositionX() < -150)//�������Ƴ��˻��棬��������
			{
				pillar->hide();
			}
			else if (pillar->isCollidWithPlayer(m_player))//������ҷ�����ײ
			{
					m_player->isAlive = false;//�������
			}
		}
		else if(count == 0)
		{
			pillar->show();//���³�������
			count++;//ˢ�²���
		}
	}

	count++;//ˢ�²���
	if (count == 120)//ÿ120֡�ų�һ������
		count = 0;
}

void PillarManager::bindPlayer(Player* player)
{
	m_player = player;
}