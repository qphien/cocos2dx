//
//  LevelSelected.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/6.
//
//

#ifndef LevelSelected_hpp
#define LevelSelected_hpp

#include "cocos2d.h"

#define ROW 2
#define COL 3


class LevelSelected: public cocos2d::Node
{
public:
    static LevelSelected* createLevelSelected(const std::string &fileName, int number);
    bool initLevelSelected(const std::string &fileName, int number);
    
    void menuCallBack(cocos2d::Ref *pSender);
};

#endif /* LevelSelected_hpp */
