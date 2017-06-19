//
//  AttackTower.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/10.
//
//

#include "AttackTower.hpp"
USING_NS_CC;

bool AttackTower::init()
{
    if(!TowerBase::init())
        return false;
    setScope(ATTACK_SCOPE);
    setCost(ATTACK_COST);
    setRate(ATTACK_RATE);
    tower = Sprite::createWithSpriteFrameName("attackTower.png");
    this->addChild(tower);
    
    schedule(schedule_selector(AttackTower::shoot), 1 / getRate());
    return true;
}

void AttackTower::shoot(float dt)
{
    nearestEnemy = this->getNearestEnemy(this);
    if(nearestEnemy == NULL ||
       nearestEnemy->getPosition().getDistance(this->getPosition()) > this->scope)
    {
        return;
    }
    if(nearestEnemy->getCurHp() > 0)
    {
        //Add bullet
        auto bullet = BulletSprite::createWithSpriteFrameName("bullet1.png");
        bullet->setPosition(tower->getContentSize().width / 2 - 3, tower->getContentSize().height - 3);
        tower->addChild(bullet);
        
        //Set bullet properties
        bullet->setLethality(ATTACK_BULLET_LETHALITY);
        bullet->setSpeed(ATTACK_BULLET_SPEED);
        
        //Get Rad
        auto rad = (nearestEnemy->getPosition() - tower->convertToWorldSpace(bullet->getPosition())).getAngle();
        auto delta = getMoveByVec(rad);
        auto distance = sqrt(delta.x * delta.x + delta.y * delta.y);
        auto moveBy = MoveBy::create(distance / bullet->getSpeed(), delta);
        auto callFunc = CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, bullet));
        bullet->runAction(Sequence::create(moveBy, callFunc, NULL));
    }
}

//Get bullet moveBy Vec2 
Vec2 AttackTower::getMoveByVec(float rad)
{
    auto towerPositionX = this->getPositionX();
    auto winSize = Director::getInstance()->getWinSize();
    auto deltaX = 0;
    auto deltaY = 0;
    auto angle = CC_RADIANS_TO_DEGREES(rad);
    if(angle < 0)
        angle += 360;
    //log("angle: %f", angle);
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
