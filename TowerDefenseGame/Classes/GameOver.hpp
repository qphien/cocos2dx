//
//  GameOver.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/12.
//
//

#ifndef GameOver_hpp
#define GameOver_hpp

#include "cocos2d.h"
#include "GameManager.hpp"
#include "LevelScene.hpp"

class GameOver: public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(GameOver);
    
    void menuBackCallBack(cocos2d::Ref *pSender);
};

#endif /* GameOver_hpp */
