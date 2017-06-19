//
//  MultiDirTower.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/10.
//
//

#ifndef MultiDirTower_hpp
#define MultiDirTower_hpp

#include "TowerBase.hpp"

#define MULTIDIR_SCOPE 90
#define MULTIDIR_RATE 1
#define MULTIDIR_COST 400

#define MULTIDIR_BULLET_LETHALITY 15
#define MULTIDIR_BULLET_SPEED 100

class MultiDirTower: public TowerBase
{
public:
    virtual bool init() override;
    static MultiDirTower* create(int number);

    void shoot(float dt) override;
    
    CC_SYNTHESIZE(int, bulletNumber, BulletNumber);
    
    BulletSprite* createBullet(const std::string &spriteName);
private:
    cocos2d::Sprite *tower;
    
    cocos2d::Vec2 getMoveByVec(float rad);
};

#endif /* MultiDirTower_hpp */
