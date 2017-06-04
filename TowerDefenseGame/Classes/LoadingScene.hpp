//
//  LoadingScene.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/4.
//
//

#ifndef LoadingScene_hpp
#define LoadingScene_hpp

#include "cocos2d.h"
#include "FilePathHeader.h"
USING_NS_CC;
const int total = 23;

class LoadingScene: public Layer
{
public:
    LoadingScene();
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LoadingScene);
    
    ProgressTimer* addProgressTimer();
    void loadResources();
    void loadMusic();
    void transitionScene();
    void loadingCallBack(Texture2D *texture);
private:
    ProgressTimer* progressTimer;
    int numberOfLoadingResouce;
    int totalResources;
};

#endif /* LoadingScene_hpp */
