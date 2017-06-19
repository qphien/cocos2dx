//
//  MultiDirTower.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/10.
//
//

#include "MultiDirTower.hpp"
USING_NS_CC;

MultiDirTower* MultiDirTower::create(int number)
{
    auto p = new(std::nothrow) MultiDirTower();
    if(p && p->init())
    {
        p->setBulletNumber(number);
        p->autorelease();
        return p;
    }
    else
    {
        delete p;
        p = NULL;
        return NULL;
    }
}
bool MultiDirTower::init()
{
    if(!TowerBase::init())
        return false;
    
    setScope(MULTIDIR_SCOPE);
    setRate(MULTIDIR_RATE);
    setCost(MULTIDIR_COST);
    
    tower = Sprite::createWithSpriteFrameName("multiDirTower.png");
    this->addChild(tower);
    schedule(schedule_selector(MultiDirTower::shoot), 1 / getRate());
    return true;
}

void MultiDirTower::shoot(float dt)
{
    nearestEnemy = getNearestEnemy(this);
    if(nearestEnemy == NULL ||
       nearestEnemy->getPosition().getDistance(this->getPosition()) > this->scope)
        return;
    
    if(nearestEnemy->getCurHp() > 0)
    {
        auto deltaRad = 2 * PI / bulletNumber;
        for(int i = 0; i != bulletNumber; ++i)
        {
            auto bullet = createBullet("bullet.png");
            bullet->setSpeed(MULTIDIR_BULLET_SPEED);
            bullet->setLethality(MULTIDIR_BULLET_LETHALITY);
            
            auto delta = getMoveByVec(deltaRad * i);
            auto distance = sqrt(delta.x * delta.x + delta.y * delta.y);
            auto moveBy = MoveBy::create(distance / bullet->getSpeed(), delta);
            auto callFunc = CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, bullet));
            bullet->runAction(Sequence::create(moveBy, callFunc, NULL));
        }
    }
    
}

BulletSprite* MultiDirTower::createBullet(const std::string &spriteName)
{
    auto bullet = BulletSprite::createWithSpriteFrameName(spriteName);
    bullet->setPosition(tower->getContentSize().width / 2, tower->getContentSize().height);
    tower->addChild(bullet);
    return bullet;
}



Vec2 MultiDirTower::getMoveByVec(float rad)
{
    auto towerPositionX = this->getPositionX();
    auto winSize = Director::getInstance()->getWinSize();
    auto deltaX = 0;
    auto deltaY = 0;
    auto angle = CC_RADIANS_TO_DEGREES(rad);
    if(angle < 0)
        angle += 360;
    if((angle >= 0 && angle <= 90) ||
       (angle > 270 && angle <= 360))
    {
        deltaX = winSize.width - towerPositionX;
        auto distance = deltaX / cos(rad);
        deltaY = distance * sin(rad);
    }
    else
    {
        deltaX = -towerPositionX;
        auto distance = fabs(deltaX / cos(rad));
        deltaY = distance * sin(rad);
    }
    return Vec2(deltaX, deltaY);
}
