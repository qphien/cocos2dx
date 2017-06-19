//
//  BulletSprite.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/9.
//
//

#ifndef BulletSprite_hpp
#define BulletSprite_hpp

#include "cocos2d.h"
#include "GameManager.hpp"


class BulletSprite: public cocos2d::Sprite
{
    CC_SYNTHESIZE(float, lethality, Lethality);
    CC_SYNTHESIZE(float, speed, Speed);
public:
    static BulletSprite* createWithSpriteFrameName(const std::string &fileName);
    virtual bool initWithSpriteFrameName(const std::string &fileName);
private:
    void detectCollision(float dt);
    void bulletDisappear();
    
    //cocos2d::Size bulletSize;
    //GameManager *_instance;
    //cocos2d::Vector<EnemyBase*> enemyToBeDeleted;
};

#endif /* BulletSprite_hpp */
