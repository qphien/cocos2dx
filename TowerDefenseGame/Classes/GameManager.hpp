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
#include "EnemyBase.hpp"


class GameManager
{
public:
    ~GameManager();
    void clear();
    static GameManager* getInstance();
    CC_SYNTHESIZE(int, money, Money);
    CC_SYNTHESIZE(std::string, backgroud, Background);
    CC_SYNTHESIZE(std::string, map, Map);
    CC_SYNTHESIZE(int, totalEnemy, TotalEnemy);
    
    void addEnemyBunch(EnemyInfo* enemyInfo);
    //void addEnemyMovingPathPoint(cocos2d::Node *point);
    //inline const cocos2d::Vector<cocos2d::Node*>& getEnemyMovingPath() { return enemyMovingPath; }
    inline cocos2d::Vector<EnemyInfo*> getEnemyGroup() { return enemyGroup; }
    inline cocos2d::Vector<EnemyBase*> getEnemySurvived() { return enemyVec; }
    inline void addEnemy(EnemyBase* enemy) { enemyVec.pushBack(enemy); }
    inline void eraseEnemy(EnemyBase *enemy) { enemyVec.eraseObject(enemy); }
    
    //Enemy survived
     cocos2d::Vector<EnemyBase*> enemyVec;
private:
    static GameManager *_instance;
    
    //Enemy group info
    cocos2d::Vector<EnemyInfo*> enemyGroup;
    
    //Enemy survived
};

#endif /* GameManager_hpp */
