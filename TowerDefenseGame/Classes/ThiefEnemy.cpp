//
//  ThiefEnemy.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/9.
//
//

#include "ThiefEnemy.hpp"
USING_NS_CC;

ThiefEnemy* ThiefEnemy::createWithSpriteFrameName(const std::string &fileName)
{
    auto thiefEnemy = new ThiefEnemy();
    if(thiefEnemy && thiefEnemy->initWithSpriteFrameName(fileName))
    {
        thiefEnemy->autorelease();
        return thiefEnemy;
    }
    else
    {
        delete thiefEnemy;
        thiefEnemy = NULL;
        return NULL;
    }
}

bool ThiefEnemy::initWithSpriteFrameName(const std::string &fileName)
{
    if(!EnemyBase::initWithSpriteFrameName(fileName))
        return false;
    setMaxHp(thiefMaxHp);
    setCurHp(thiefMaxHp);
    setSpeed(thiefSpeed);
    setValue(thiefValue);
    setDamage(thiefDamage);
    leftAnimate = createAnimate("enemyLeft1", 4, 0.1f);
    leftAnimate->retain();
    rightAnimate = createAnimate("enemyRight1", 4, 0.1f);
    rightAnimate->retain();
    explodeAnimate = createAnimate("explode1", 6, 0.15f);
    explodeAnimate->retain();
    return true;
}
