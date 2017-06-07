//
//  GameManager.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/7.
//
//

#include "GameManager.hpp"

GameManager* GameManager::_instance;

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
