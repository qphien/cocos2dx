//
//  GameManager.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/7.
//
//

#include "GameManager.hpp"

USING_NS_CC;

GameManager* GameManager::_instance;

GameManager::~GameManager()
{
    enemyGroup.clear();
    enemyVec.clear();
}

GameManager* GameManager::getInstance()
{
    if(_instance == NULL)
        _instance = new GameManager();
    return _instance;
}

void GameManager::addEnemyBunch(EnemyInfo *enemyInfo)
{
    enemyGroup.pushBack(enemyInfo);
}


void GameManager::clear()
{
    enemyGroup.clear();
    enemyVec.clear();
    money = 0;
    backgroud = "";
    map = "";
    totalEnemy = 0;
}

//Vector<EnemyInfo*> GameManager::getEnemyGroup()
//{
//    return enemyGroup;
//}

//void GameManager::addEnemyMovingPathPoint(Node *point)
//{
//    enemyMovingPath.pushBack(point);
//}

