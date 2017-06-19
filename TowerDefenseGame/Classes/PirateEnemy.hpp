//
//  PirateEnemy.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/9.
//
//

#ifndef PirateEnemy_hpp
#define PirateEnemy_hpp

#include "EnemyBase.hpp"

#define pirateSpeed 50
#define pirateValue 20
#define pirateMaxHp 80
#define pirateDamage 15
class PirateEnemy: public EnemyBase
{
public:
    static PirateEnemy* createWithSpriteFrameName(const std::string &fileName);
    bool initWithSpriteFrameName(const std::string &fileName) override;
};

#endif /* PirateEnemy_hpp */
