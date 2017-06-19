//
//  PirateEnemy.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/9.
//
//

#include "PirateEnemy.hpp"
USING_NS_CC;

PirateEnemy* PirateEnemy::createWithSpriteFrameName(const std::string &fileName)
{
    auto pirate = new PirateEnemy();
    if(pirate && pirate->initWithSpriteFrameName(fileName))
    {
        pirate->autorelease();
        return pirate;
    }
    else
    {
        delete pirate;
        pirate = NULL;
        return NULL;
    }
}

bool PirateEnemy::initWithSpriteFrameName(const std::string &fileName)
{
    if(!EnemyBase::initWithSpriteFrameName(fileName))
        return false;
    setCurHp(pirateMaxHp);
    setMaxHp(pirateMaxHp);
    setSpeed(pirateSpeed);
    setValue(pirateValue);
    setDamage(pirateDamage);
    leftAnimate = createAnimate("enemyLeft2", 4, 0.1f);
    //if not retain, the animate will be autoreleased
    //remember to release the animate manually 
    leftAnimate->retain();
    rightAnimate = createAnimate("enemyRight2", 4, 0.1f);
    rightAnimate->retain();
    explodeAnimate = createAnimate("explode2", 6, 0.15f);
    explodeAnimate->retain();
    return true;
}
