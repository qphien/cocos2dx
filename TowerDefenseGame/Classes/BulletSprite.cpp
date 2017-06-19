//
//  BulletSprite.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/9.
//
//

#include "BulletSprite.hpp"
USING_NS_CC;

BulletSprite* BulletSprite::createWithSpriteFrameName(const std::string &fileName)
{
    BulletSprite *p = new BulletSprite();
    if(p && p->initWithSpriteFrameName(fileName))
    {
        p->autorelease();
        return p;
    }
    else
    {
        delete p;
        p = NULL;
        return NULL;
    }
}

bool BulletSprite::initWithSpriteFrameName(const std::string &fileName)
{
    if(!Sprite::initWithSpriteFrameName(fileName))
        return false;
    //_instance = GameManager::getInstance();
    schedule(schedule_selector(BulletSprite::detectCollision));
    return true;
}

void BulletSprite::detectCollision(float dt)
{
    //Recommend to use physical engine to detect collision
    Vector<EnemyBase*> enemyToBeDeleted;
    auto bulletSize = this->getContentSize();
    //auto enemySurvived = GameManager::getInstance()->getEnemySurvived();
    auto end = GameManager::getInstance()->enemyVec.end();
    for(auto enemyIter = GameManager::getInstance()->enemyVec.begin(); enemyIter != end; ++enemyIter)
    {
        Size enemySize = (*enemyIter)->getContentSize();
        auto bulletPos = this->getParent()->convertToWorldSpace(this->getPosition());
        auto bulletRect = Rect(bulletPos.x,
                               bulletPos.y,
                               bulletSize.width, bulletSize.height);
        auto enemyRect = Rect((*enemyIter)->getPositionX(),
                              (*enemyIter)->getPositionY(),
                              enemySize.width, enemySize.height);
       // log("bulletRect origin: %f, %f, size: %f, %f", bulletPos.x, bulletPos.y,
        //    bulletSize.width, bulletSize.height);
        //log("enemyRect origin: %f, %f, size: %f, %f", enemyRect.origin.x, enemyRect.origin.y,
         //   enemyRect.size.width, enemyRect.size.height);

        //bullet collides with enemy
        //bullet can not collide with enemy when enemy is exploding
        if(bulletRect.intersectsRect(enemyRect) && !(*enemyIter)->getIsExploding())
        {
            //set enemy hp
           // log("bullet collides with enemy");
            (*enemyIter)->setCurHp((*enemyIter)->getCurHp() - lethality);
            (*enemyIter)->setHpBarPercentage();
            
            //enemy die
            if((*enemyIter)->getCurHp() <= 0)
            {
                //playscene receive the custome event
                //playscene set moneyLabel
                
                EventCustom event("EnemyDie");
                auto enemyValue = (*enemyIter)->getValue();
                event.setUserData(&enemyValue);
                _eventDispatcher->dispatchEvent(&event);
                
                (*enemyIter)->explode();
                
                //Add Dead enemy to enemyTobeDeleted
                enemyToBeDeleted.pushBack((*enemyIter));
            }
            
            //one bullet can only collide with one enemy
            //bullet disappear
            bulletDisappear();
            break;
        }
    }
    for(auto enemy: enemyToBeDeleted)
    {
        //log("remove enemy from enemySurvived");
        GameManager::getInstance()->enemyVec.eraseObject(enemy);
    }
   // log("enemySurvied vector size: %d", GameManager::getInstance()->getEnemySurvived().size());
}

void BulletSprite::bulletDisappear()
{
    this->setVisible(false);
    this->stopAllActions();
    this->removeFromParent();
}
