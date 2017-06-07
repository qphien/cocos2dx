//
//  LoadInfo.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/7.
//
//

#ifndef LoadInfo_hpp
#define LoadInfo_hpp

#include "GameManager.hpp"
#include "EnemyInfo.hpp"
#include "cocos2d.h"

class LoadInfo: public cocos2d::Ref
{
public:
    static LoadInfo* createWithFile(const std::string &fileName);
    bool initwithFile(const std::string &fileName);
    
    void readInfo();
    
private:
    cocos2d::ValueMap levelInfo;
    cocos2d::ValueMap resources;
};

#endif /* LoadInfo_hpp */
