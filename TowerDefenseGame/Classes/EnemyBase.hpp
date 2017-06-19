//
//  EnemyBase.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/9.
//
//

#ifndef EnemyBase_hpp
#define EnemyBase_hpp

#include "cocos2d.h"


//Recomend to create a enemy factory to spawn enemy
class EnemyBase:public cocos2d::Sprite
{
    enum Direction
    {
        LEFT,
        RIGHT
    };
    
    
    CC_SYNTHESIZE(float, speed, Speed);
    CC_SYNTHESIZE(float, maxHp, MaxHp);
    CC_SYNTHESIZE(float, value, Value);
    CC_SYNTHESIZE(float, curHp, CurHp);
    CC_SYNTHESIZE(float, damage, Damage);
    CC_SYNTHESIZE_READONLY(bool, isExploding, IsExploding);
public:
    EnemyBase();
    virtual ~EnemyBase();
    
    void setHpBarPercentage();
    virtual bool initWithSpriteFrameName(const std::string &fileName) override;
    void explode();
    //virtual EnemyBase* createWithSpriteFrameName(const std::string &fileName);
    
    void runFollowPoint(const cocos2d::Vector<cocos2d::Node*> &path);
protected:
    cocos2d::Animate* createAnimate(const std::string &prefixName, int framesNum, float delay);
    
    cocos2d::Animate *leftAnimate;
    cocos2d::Animate *rightAnimate;
    cocos2d::Animate *explodeAnimate;
private:
    cocos2d::Node* getCurrentPoint(const cocos2d::Vector<cocos2d::Node*> &path);
    cocos2d::Node* getNextPoint(const cocos2d::Vector<cocos2d::Node*> &path);

    void changeDirection(float currentPosX, float nextPosX);
    void addHpBar();
    
    cocos2d::ProgressTimer *hpBar;
    int pointCounter;
    //GameManager *_instance;
    Direction direction;
};

#endif /* EnemyBase_hpp */
