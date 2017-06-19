//
//  EnemyBase.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/9.
//
//

#include "EnemyBase.hpp"
#include "GameManager.hpp"
USING_NS_CC;

EnemyBase::EnemyBase(): pointCounter(0), hpBar(NULL), 
                        leftAnimate(NULL), rightAnimate(NULL), explodeAnimate(NULL),
                        value(0), curHp(0), maxHp(0), speed(0),
                        direction(LEFT), isExploding(false)
{
    
}

EnemyBase::~EnemyBase()
{
    CC_SAFE_RELEASE(leftAnimate);
    CC_SAFE_RELEASE(rightAnimate);
    CC_SAFE_RELEASE(explodeAnimate);
}
//EnemyBase* EnemyBase::createWithSpriteFrameName(const std::string &fileName)
//{
//    auto enemy = new EnemyBase();
//    if(enemy && enemy->initWithSpriteFrameName(fileName))
//    {
//        enemy->autorelease();
//        return enemy;
//    }
//    else
//    {
//        delete enemy;
//        enemy = NULL;
//        return NULL;
//    }
//}

bool EnemyBase::initWithSpriteFrameName(const std::string &fileName)
{
    if(!Sprite::initWithSpriteFrameName(fileName))
        return false;
//    auto listener = EventListenerCustom::create("EnemyDie", [&](EventCustom* event)
//                                                {
//                                                    this->explode();
//                                                });
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
    addHpBar();
    return true;
}

void EnemyBase::addHpBar()
{
    //Add hp bar background
    auto hpBarBackground = Sprite::createWithSpriteFrameName("hpBg1.png");
    hpBarBackground->setAnchorPoint(Vec2(0.5, 0));
    hpBarBackground->setPosition(this->getContentSize().width / 2, this->getContentSize().height);
    this->addChild(hpBarBackground);
    hpBarBackground->setTag(1);
    
    //Add hp bar
    hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("hp1.png"));
    hpBar->setType(ProgressTimer::Type::BAR);
    hpBar->setMidpoint(Vec2(0, 0.5));
    hpBar->setBarChangeRate(Vec2(1, 0));
    hpBar->setPercentage(100);
    //hpBar->setAnchorPoint(Vec2(0, 0));
    hpBar->setPosition(hpBarBackground->getContentSize().width / 2, hpBarBackground->getContentSize().height / 3 * 2);
    hpBarBackground->addChild(hpBar, 10);
}

void EnemyBase::runFollowPoint(const Vector<Node*> &path)
{
    auto currentPoint = getCurrentPoint(path);
    auto nextPoint = getNextPoint(path);
    
    if(nextPoint != NULL)
    {
        auto distance = nextPoint->getPosition().getDistance(currentPoint->getPosition());
        changeDirection(currentPoint->getPositionX(), nextPoint->getPositionX());
        auto moveTo = MoveTo::create(distance / speed, nextPoint->getPosition());
        this->runAction(Sequence::create(moveTo,
                                 CallFunc::create(CC_CALLBACK_0(EnemyBase::runFollowPoint, this, path)), NULL));
    }
    else
    {
        //send event enemy arrives at destination
        EventCustom event("enemySuccess");
        event.setUserData(&damage);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
        GameManager::getInstance()->eraseEnemy(this);
        //log("enemySurvived size: %d", GameManager::getInstance()->enemyVec.size());
        //remove enemy
        this->setVisible(false);
        this->removeFromParent();
    }
}

void EnemyBase::changeDirection(float currentPosX, float nextPosX)
{
    if(nextPosX > currentPosX && direction != RIGHT)
    {
        direction = RIGHT;
        auto repeat = RepeatForever::create(rightAnimate);
        repeat->setTag(RIGHT);
        this->stopActionByTag(LEFT);
        this->runAction(repeat);
    }
    else if(nextPosX < currentPosX && direction != LEFT)
    {
        direction = LEFT;
        auto repeat = RepeatForever::create(leftAnimate);
        repeat->setTag(LEFT);
        this->stopActionByTag(RIGHT);
        this->runAction(repeat);
    }
}


Node* EnemyBase::getCurrentPoint(const Vector<Node*> &path)
{
    if(pointCounter < path.size())
        return path.at(pointCounter);
    return NULL;
}

Node* EnemyBase::getNextPoint(const Vector<Node*> &path)
{
    if(pointCounter < path.size() - 1)
    {
        ++pointCounter;
        return path.at(pointCounter);
    }
    return NULL;
}

cocos2d::Animate* EnemyBase::createAnimate(const std::string &prefixName, int framesNum, float delay)
{
    Vector<SpriteFrame*> frameVec;
    for(int i = 1; i <= framesNum; ++i)
    {
        char buf[10] = {0};
        snprintf(buf, 10, "_%d.png", i);
        std::string fileName = prefixName + buf;
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
        frameVec.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(frameVec, delay);
    auto animate = Animate::create(animation);
    return animate;
}

void EnemyBase::setHpBarPercentage()
{
    hpBar->setPercentage(curHp / maxHp * 100);
}

void EnemyBase::explode()
{
    //log("enemy die");
    this->getChildByTag(1)->setVisible(false);
    this->stopAllActions();
    auto callFunc = CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, this));
    auto seq = Sequence::create(explodeAnimate, callFunc, NULL);
    isExploding = true;
    this->runAction(seq);
}
