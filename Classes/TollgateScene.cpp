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
	
	visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��Ļ��С
	
	score = 0;//��ʼ������
	
	createPlayer();	//�������
	
	createMenu();//������Ծ��ť
	
	createPillarMgr();//�������ӹ�����
	
	createScore();//����������
	
	initBG();//��ʼ��ǰ���뱳��
	
	this->scheduleUpdate();//����Update����

	return true;
}

void TollgateScene::update(float delta)
{
	Size mapSize = m_bgSprite1->getContentSize();//���

	int posX1 = m_bgSprite1->getPositionX();//��ȡ����1��X
	int posX2 = m_bgSprite2->getPositionX();//��ȡ����2��X

	int posX3 = m_fSprite1->getPositionX();//��ȡǰ��1��X
	int posX4 = m_fSprite2->getPositionX();//��ȡǰ��2��X

	int posPlayerY = m_player->getPositionY();//��ȡ��ҵ�Y

	/*ģ������ϵͳ*/
	int iSpeed = 3;//�����ƶ��ٶ�
	int fSpeed = 6;//ǰ���ƶ��ٶ�
	int jumpSpeed = 6;//������Ծ���ٶ�
	float gravity = 0.2;//����

	static bool book = true;//���ڽ��ͷ���������Ϊ��֡һ��
	if (!m_player->isAlive)
		gravity = 10;
	else if (book)//�ӷ�
		score++;

	book = !book;//�ı���״̬
	changeLabel(label);//ˢ�·�����
	
	/*�ƶ�ǰ���뱳��*/
	posX1 -= iSpeed;
	posX2 -= iSpeed;
	posX3 -= fSpeed;
	posX4 -= fSpeed;

	if (m_player->jumping)//�����ǵ�״̬Ϊ������������Ծ���ٶ�
	{
		m_player->speed = jumpSpeed;
		m_player->jumping = false;//���á�����״̬Ϊfalse
	}

	posPlayerY += m_player->speed;//ˢ�����Y����

	m_player->speed -= gravity;//ģ������
	
	/*��ǰ���򱳾�����ʱ������λ��*/
	if (posX1 <= -mapSize.width / 2)
		posX1 = mapSize.width + mapSize.width / 2 - 5;

	if (posX2 <= -mapSize.width / 2)
		posX2 = mapSize.width + mapSize.width / 2 - 5;

	if (posX3 <= -mapSize.width / 2)
		posX3 = mapSize.width + mapSize.width / 2 - 15;

	if (posX4 <= -mapSize.width / 2)
		posX4 = mapSize.width + mapSize.width / 2 - 15;

	/*����ǰ���ͱ���λ��*/
	m_bgSprite1->setPositionX(posX1);
	m_bgSprite2->setPositionX(posX2);
	m_fSprite1->setPositionX(posX3);
	m_fSprite2->setPositionX(posX4);

	m_player->setPositionY(posPlayerY);//�������λ��

	if (posPlayerY >= 620)//ͷ���컨������
		m_player->isAlive = false;

	if (posPlayerY <= 0)//�䵽����������Ͻ�����㳡��
	{
		//Ϊ�ؿ���׼��
		m_player->isAlive = true;
		gravity = 0.2;
		m_player->speed = 10;
		FinScore = score;//����ȫ�ֱ���������
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, OverScene::createScene()));//������㳡��
	}
}

void TollgateScene::initBG()
{
	/*����ǰ�����������ž���*/
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

void TollgateScene::jumpEvent(Ref* button)//��Ծ�¼�
{
	this->m_player->jumping = true;
}

void TollgateScene::createMenu()
{
	//����Menu
	auto _menu = Menu::create();

	//����Menuλ������
	_menu->setPosition(Vec2::ZERO);

	//�������飬�ֱ�Ϊ�����Ͱ���ʱ��ʾ
	auto _spriteNormal = Sprite::create("button3.png");
	auto _spritePress = Sprite::create("button4.png");

	//����menuItemSprite
	auto _menuItemSprite = MenuItemSprite::create(_spriteNormal, _spritePress, CC_CALLBACK_1(TollgateScene::jumpEvent, this));

	//����menuItemSpriteλ������
	_menuItemSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 8));

	//��menuItemSprite��ӵ�Menu��
	_menu->addChild(_menuItemSprite);

	//��Menu��ӵ����ڵ����
	this->addChild(_menu, 7);
}

void TollgateScene::changeLabel(Label* oldLabel)
{
	//����ת�ַ����н�
	char ch[20];
	char ch2[40] = "SCROE:";
	//ɾ��ԭ�Ʒְ�
	this->removeChild(oldLabel);
	//����ת�ַ���
	sprintf(ch, "%15d",this->score);
	strcat(ch2, ch);
	//�½�������
	Label* newLabel = Label::createWithTTF(ch2, "Marker Felt.ttf", 30);
	newLabel->setPosition(Vec2(visibleSize.width / 6, visibleSize.height / 2));
	//���·�����
	label = newLabel;
	//����ڵ�
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
	pillarMgr->bindPlayer(m_player);//�����
	this->addChild(pillarMgr, 3);
}


void TollgateScene::createAnimate()
{
	Vector<SpriteFrame*> frameVec;//������
	//���붯��֡
	frameVec.pushBack(SpriteFrame::create(StringUtils::format("player.png"), Rect(0, 0, 50, 50)));
	frameVec.pushBack(SpriteFrame::create(StringUtils::format("player2.png"), Rect(0, 0, 50, 50)));
	frameVec.pushBack(SpriteFrame::create(StringUtils::format("player3.png"), Rect(0, 0, 50, 50)));

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);

	Animate* action = Animate::create(animation);

	m_player->getSprite()->runAction(action);

}