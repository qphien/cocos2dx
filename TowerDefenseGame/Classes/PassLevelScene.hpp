//
//  PassLevelScene.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/12.
//
//

#ifndef PassLevelScene_hpp
#define PassLevelScene_hpp

#include "cocos2d.h"

class PassLevelScene: public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(PassLevelScene);
    
    void menuNextCallBack(cocos2d::Ref *pSender);
    void menuBackCallBack(cocos2d::Ref *pSender);
};

#endif /* PassLevelScene_hpp */
