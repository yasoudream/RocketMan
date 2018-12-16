#include "Pillar.h"

Pillar::Pillar()
{
	underPillar = NULL;//��ʼ��������
	m_isAlive = false;
}

Pillar::~Pillar(){}

bool Pillar::init()
{
	return true;
}

void Pillar::show()
{
	if (getSprite() != NULL)
	{
		setVisible(true);//��ʾ����
		this->underPillar->setVisible(true);//��ʾ������
		m_isAlive = true;//�������Ϊ�
	}
}

void Pillar::hide()
{
	if (getSprite() != NULL)
	{
		setVisible(false);//��������
		this->underPillar->setVisible(false);//���ظ�����
		reset();//��������
		m_isAlive = false;//�������Ϊ�ǻ
	}
}

void Pillar::reset()
{
	int height = CCRANDOM_0_1() * 400 + 300;//������ɸ߶�
	if (getSprite() != NULL)
	{
		setPosition(Point(1030, height));//�������Ӹ߶�
		this->underPillar->setPosition(Point(1100, height - 480));//���ø����Ӹ߶�
	}
}

bool Pillar::isAlive()
{
	return m_isAlive;
}

bool Pillar::isCollidWithPlayer(Player* player)
{
	Rect playerRect = player->getBoundingBox();//��������ײ��
	Rect pillarRect = this->getBoundingBox();//���������ײ��
	Rect underpillarRect = this->underPillar->getBoundingBox();//��ø�������ײ��
	/*��ײ�ж�*/
	if (playerRect.getMaxX() > pillarRect.getMinX() && playerRect.getMaxY() > pillarRect.getMinY() && playerRect.getMinX() <= pillarRect.getMaxX() ||
		playerRect.getMaxX() > underpillarRect.getMinX() && playerRect.getMinY() < underpillarRect.getMaxY() && playerRect.getMinX() <= underpillarRect.getMaxX())
		return true;
	else
		return false;
}