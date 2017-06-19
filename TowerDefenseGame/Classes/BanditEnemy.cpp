//
//  BanditEnemy.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/9.
//
//

#include "BanditEnemy.hpp"

BanditEnemy* BanditEnemy::createWithSpriteFrameName(const std::string &fileName)
{
    auto bandit = new BanditEnemy();
    if(bandit && bandit->initWithSpriteFrameName(fileName))
    {
        bandit->autorelease();
        return bandit;
    }
    else
    {
        delete bandit;
        bandit = NULL;
        return NULL;
    }
}

bool BanditEnemy::initWithSpriteFrameName(const std::string &fileName)
{
    if(!EnemyBase::initWithSpriteFrameName(fileName))
        return false;
    setMaxHp(banditMaxHp);
    setCurHp(banditMaxHp);
    setSpeed(banditSpeed);
    setValue(banditValue);
    setDamage(banditDamage);
    leftAnimate = createAnimate("enemyLeft3", 4, 0.1);
    leftAnimate->retain();
    rightAnimate = createAnimate("enemyRight3", 4, 0.1);
    rightAnimate->retain();
    explodeAnimate = createAnimate("explode3", 6, 0.15);
    explodeAnimate->retain();
    return true;
}
