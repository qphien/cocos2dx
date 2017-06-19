//
//  ThiefEnemy.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/9.
//
//

#ifndef ThiefEnemy_hpp
#define ThiefEnemy_hpp

#include "EnemyBase.hpp"

#define thiefMaxHp 100
#define thiefSpeed 25
#define thiefValue 10
#define thiefDamage 10

class ThiefEnemy: public EnemyBase
{
public:
    static ThiefEnemy* createWithSpriteFrameName(const std::string &fileName);
    bool initWithSpriteFrameName(const std::string &fileName) override;
};

#endif /* ThiefEnemy_hpp */
