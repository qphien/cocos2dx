//
//  LevelInfoScene.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/7.
//
//

#ifndef LevelInfoScene_hpp
#define LevelInfoScene_hpp

#include "cocos2d.h"

#define STAR_NUMBER 3


class LevelInfoScene: public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(LevelInfoScene);
    
    void menuStartCallBack(cocos2d::Ref *pSender);
    void menuBackCallBack(cocos2d::Ref *pSender);
    
    
};

#endif /* LevelInfoScene_hpp */
