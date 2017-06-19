//
//  BanditEnemy.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/9.
//
//

#ifndef BanditEnemy_hpp
#define BanditEnemy_hpp

#include "EnemyBase.hpp"

#define banditMaxHp 60
#define banditValue 30
#define banditSpeed 60
#define banditDamage 20

class BanditEnemy: public EnemyBase
{
public:
    static BanditEnemy* createWithSpriteFrameName(const std::string &fileName);
    bool initWithSpriteFrameName(const std::string &fileName) override;
};

#endif /* BanditEnemy_hpp */
