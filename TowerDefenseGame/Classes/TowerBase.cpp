//
//  TowerBase.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/8.
//
//

#include "TowerBase.hpp"

USING_NS_CC;

TowerBase::TowerBase(): scope(0), rate(0), cost(0), nearestEnemy(NULL)
{
    
}

bool TowerBase::init()
{
    if(!Sprite::init())
        return false;
    return true;
}

EnemyBase* TowerBase::getNearestEnemy(TowerBase *tower)
{
    auto enemyVec = GameManager::getInstance()->getEnemySurvived();
    EnemyBase *nearestEnemy = NULL;
    auto minDistance = std::numeric_limits<float>::max();
    for(int i = 0; i != enemyVec.size(); ++i)
    {
        auto distance = tower->getPosition().getDistance(enemyVec.at(i)->getPosition());
        if(distance < minDistance)
        {
            minDistance = distance;
            nearestEnemy = enemyVec.at(i);
        }
    }
    return nearestEnemy;
}
