//
//  EnemyInfo.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/7.
//
//

#include "EnemyInfo.hpp"
USING_NS_CC;

EnemyInfo* EnemyInfo::createEnemyInfo(int type1Num, int type1HP, int type2Num, int type2HP, int type3Num, int type3HP)
{
    auto p = new EnemyInfo();
    if(p && p->initEnemyInfo(type1Num, type1HP, type2Num, type2HP, type3Num, type3HP))
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

bool EnemyInfo::initEnemyInfo(int type1Num, int type1HP, int type2Num, int type2HP, int type3Num, int type3HP)
{
    setType1Num(type1Num);
    setType1HP(type1HP);
    setType2Num(type2Num);
    setType2Hp(type2HP);
    setType3Num(type3Num);
    setType3HP(type3HP);
    
    return true;
}
