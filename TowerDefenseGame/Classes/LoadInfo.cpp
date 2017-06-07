//
//  LoadInfo.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/7.
//
//

#include "LoadInfo.hpp"
USING_NS_CC;


LoadInfo* LoadInfo::createWithFile(const std::string &fileName)
{
    LoadInfo *p = new LoadInfo();
    if(p && p->initwithFile(fileName))
    {
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

bool LoadInfo::initwithFile(const std::string &fileName)
{
    if(fileName == "")
        return false;
    auto dict = FileUtils::getInstance()->getValueMapFromFile(fileName);
    levelInfo = dict["levelInfo"].asValueMap();
    resources = dict["resources"].asValueMap();
    
    return true;
}

void LoadInfo::readInfo()
{
    auto gameManager = GameManager::getInstance();
    
    //Add Money, Map, Backgrond
    gameManager->setMoney(levelInfo.at("money").asInt());
    gameManager->setMap(resources.at("map").asString());
    gameManager->setBackground(resources.at("image").asString());
    
    //Add Level Enemy Info
    //each level has several bunch enemy
    auto group = levelInfo.at("group").asValueMap();
    for(auto iter = group.begin(); iter != group.end(); ++iter)
    {
        auto bunch = iter->second.asValueMap();
        auto type1Num = bunch.at("type1Num").asInt();
        auto type1Hp = bunch.at("type1Hp").asInt();
        auto type2Num = bunch.at("type2Num").asInt();
        auto type2Hp = bunch.at("type2Hp").asInt();
        auto type3Num = bunch.at("type3Num").asInt();
        auto type3Hp = bunch.at("type3Hp").asInt();
        
        auto enemyInfo = EnemyInfo::createEnemyInfo(type1Num, type1Hp, type2Num, type2Hp
                                                    , type3Num, type3Hp);
        gameManager->addEnemyBunch(enemyInfo);
    }
    
}
