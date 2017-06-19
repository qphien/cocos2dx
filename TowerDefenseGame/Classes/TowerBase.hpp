//
//  TowerBase.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/8.
//
//

#ifndef TowerBase_hpp
#define TowerBase_hpp

#include "cocos2d.h"
#include "EnemyBase.hpp"
#include "GameManager.hpp"
#include "BulletSprite.hpp"
#include "FilePathHeader.h"


//Recomend to create a tower factory to generate tower
class TowerBase: public cocos2d::Sprite
{
public:
    TowerBase();
    virtual void shoot(float dt) {}
    
    virtual bool init();
    CC_SYNTHESIZE(float, scope, Scope);
    //set the rate of shoot bullet
    CC_SYNTHESIZE(float, rate, Rate);
    CC_SYNTHESIZE(int, cost, Cost);
    
protected:
    EnemyBase* getNearestEnemy(TowerBase *tower);
    
    EnemyBase* nearestEnemy;
};

#endif /* TowerBase_hpp */
