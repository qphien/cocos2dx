//
//  LevelScene.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/6.
//
//

#ifndef LevelScene_hpp
#define LevelScene_hpp

#include "cocos2d.h"

class LevelScene: public cocos2d::Layer
{
public:
    static cocos2d::Scene *createScene();
    virtual bool init();
    
    CREATE_FUNC(LevelScene);
private:
    void transitionScene();
    void menuBackCallBack(cocos2d::Ref *pSender);
};

#endif /* LevelScene_hpp */
