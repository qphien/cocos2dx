//
//  AttackTower.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/10.
//
//

#ifndef AttackTower_hpp
#define AttackTower_hpp

#include "TowerBase.hpp"

#define ATTACK_SCOPE 90
#define ATTACK_RATE 1
#define ATTACK_COST 150

#define ATTACK_BULLET_LETHALITY 15
#define ATTACK_BULLET_SPEED 150

class AttackTower: public TowerBase
{
public:
    virtual bool init() override;
    CREATE_FUNC(AttackTower);
    
    void shoot(float dt) override;
    
private:
    cocos2d::Sprite *tower;
    
    cocos2d::Vec2 getMoveByVec(float rad);
};

#endif /* AttackTower_hpp */
