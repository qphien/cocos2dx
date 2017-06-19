//
//  ArrowTower.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/8.
//
//

#ifndef ArrowTower_hpp
#define ArrowTower_hpp

#include "TowerBase.hpp"
#include "GameManager.hpp"


#define ARROW_SCOPE 90
#define ARROW_RATE 1
#define ARROW_COST 200
#define ARROW_RORATION_SPEED 360 * 2

#define ARROW_BULLET_LETHALITY 10
#define ARROW_BULLET_SPEED 150





class ArrowTower: public TowerBase
{
    CC_SYNTHESIZE(float, arrowRotationSpeed, ArrowRotationSpeed);
public:
    ArrowTower();
    virtual bool init() override;
    CREATE_FUNC(ArrowTower);
    
    void shoot(float dt) override;
private:
    void shootBullet(float rad);
    cocos2d::Vec2 getMoveByVec(float rad);
    
    //float rad;
    cocos2d::Sprite *arrow;
    cocos2d::Sprite *plate;
    
    void test(cocos2d::Node *p);
};

#endif /* ArrowTower_hpp */
