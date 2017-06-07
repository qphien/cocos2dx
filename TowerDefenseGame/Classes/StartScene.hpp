//
//  StartScene.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/6.
//
//

#ifndef StartScene_hpp
#define StartScene_hpp

#include "cocos2d.h"

class StartScene: public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(StartScene);
    
    void menuStartCallBack(cocos2d::Ref* pSender);
    
    virtual void onEnter();
    
private:
    cocos2d::RepeatForever* getStarAction(float controlX, float controlY, float width);
    void transitionScene();
};

#endif /* StartScene_hpp */
