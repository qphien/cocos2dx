//
//  ArrowTower.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/8.
//
//

#include "ArrowTower.hpp"
USING_NS_CC;

ArrowTower::ArrowTower():  arrow(NULL)
{
    
}

bool ArrowTower::init()
{
    if(!TowerBase::init())
        return false;
    
    
    setScope(ARROW_SCOPE);
    setRate(ARROW_RATE);
    setCost(ARROW_COST);
    setArrowRotationSpeed(ARROW_RORATION_SPEED);
    
    //Add tower plate
    plate = Sprite::createWithSpriteFrameName("baseplate.png");
    this->addChild(plate);
    
    //Add Arrow
    arrow = Sprite::createWithSpriteFrameName("arrow.png");
    arrow->setPosition(0, plate->getContentSize().height / 4);
    this->addChild(arrow);
    
    schedule(schedule_selector(ArrowTower::shoot), 1 / getRate());
    
    return true;
}

void ArrowTower::shoot(float dt)
{
    //is in shoot scope
    nearestEnemy = this->getNearestEnemy(this);
    if(nearestEnemy == NULL ||
       nearestEnemy->getPosition().getDistance(this->getPosition()) > this->scope)
    {
        return;
    }
    //get rotation angle
    auto rad = (nearestEnemy->getPosition() - this->convertToWorldSpace(arrow->getPosition())).getAngle();
    auto angle = CC_RADIANS_TO_DEGREES(-rad);
    //get rotation time
    auto rotationDuration = fabs(angle / getArrowRotationSpeed());
    
    auto rotationTo = RotateTo::create(rotationDuration, angle);
    auto callFunc = CallFunc::create(CC_CALLBACK_0(ArrowTower::shootBullet, this, rad));
    
    arrow->runAction(Sequence::create(rotationTo, callFunc, NULL));
}


void ArrowTower::shootBullet(float rad)
{
    if(nearestEnemy->getCurHp() > 0 && !nearestEnemy->getIsExploding())
    {
        //Add bullet
        auto bullet = BulletSprite::createWithSpriteFrameName("arrowBullet.png");
        bullet->setPosition(arrow->getPositionX() + arrow->getContentSize().width / 2, arrow->getPositionY() + arrow->getContentSize().height / 2);
        bullet->setRotation(arrow->getRotation());
        bullet->setLethality(ARROW_BULLET_LETHALITY);
        bullet->setSpeed(ARROW_BULLET_SPEED);
        //MoveTo 和 MoveBy是根据父节点的坐标原点来进行移动的，而不是根据openGL坐标系原点
        //并且随着物体旋转，该物体的坐标轴也会跟着旋转
        //所以这里应将bullet添加到plate而不是arrow，
        //如果添加到arrow，bullet的moveBy就要根据arrow的旋转而发生变化，使得到moveBy变得复杂
        plate->addChild(bullet, 10);
        
        
        auto delta = getMoveByVec(rad);
        auto distance = sqrt(delta.x * delta.x + delta.y * delta.y);
        auto moveBy = MoveBy::create(distance / bullet->getSpeed(), delta);
        auto callFunc = CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, bullet));
        bullet->runAction(Sequence::create(moveBy, callFunc, NULL));
        
    }
}



Vec2 ArrowTower::getMoveByVec(float rad)
{
    auto arrowPositionX = this->getPositionX();
    log("towre position: %f, %f", arrowPositionX, this->getPositionY());
    auto winSize = Director::getInstance()->getWinSize();
    float deltaX = 0;
    float deltaY = 0;
    auto angle = CC_RADIANS_TO_DEGREES(rad);
    if(angle < 0)
        angle += 360;
    if((angle >= 0 && angle <= 90) ||
       (angle > 270 && angle <= 360))
    {
        deltaX = winSize.width - arrowPositionX;
        auto distance = deltaX / cos(rad);
        deltaY = distance * sin(rad);
    }
    else
    {
        deltaX = -arrowPositionX;
        auto distance = fabs(deltaX / cos(rad));
        deltaY = distance * sin(rad);
    }
    return Vec2(deltaX, deltaY);
}
