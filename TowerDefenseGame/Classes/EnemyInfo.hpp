//
//  EnemyInfo.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/7.
//
//

#ifndef EnemyInfo_hpp
#define EnemyInfo_hpp
#include "cocos2d.h"

class EnemyInfo: public cocos2d::Ref
{
public:
    static EnemyInfo* createEnemyInfo(int type1Num, int type1HP,
                                      int type2Num, int type2HP,
                                      int type3Num, int type3HP);
    bool initEnemyInfo(int type1Num, int type1HP,
                       int type2Num, int type2HP,
                       int type3Num, int type3HP);
    
    CC_SYNTHESIZE(int , type1Num, Type1Num);
    CC_SYNTHESIZE(int, type1HP, Type1HP);
    CC_SYNTHESIZE(int , type2Num, Type2Num);
    CC_SYNTHESIZE(int, type2HP, Type2Hp);
    CC_SYNTHESIZE(int, type3Num, Type3Num);
    CC_SYNTHESIZE(int, type3HP, Type3HP);
};

#endif /* EnemyInfo_hpp */
