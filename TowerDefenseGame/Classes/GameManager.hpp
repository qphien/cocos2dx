//
//  GameManager.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/7.
//
//

#ifndef GameManager_hpp
#define GameManager_hpp

#include "cocos2d.h"
#include "EnemyInfo.hpp"

class GameManager
{
public:
    static GameManager* getInstance();
    CC_SYNTHESIZE(int, money, Money);
    CC_SYNTHESIZE(std::string, backgroud, Background);
    CC_SYNTHESIZE(std::string, map, Map);
    
    void addEnemyBunch(EnemyInfo* enemyInfo);
private:
    static GameManager *_instance;
    cocos2d::Vector<EnemyInfo*> enemyGroup;
};

#endif /* GameManager_hpp */
