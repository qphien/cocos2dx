//
//  TowerPanelLayer.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/8.
//
//

#ifndef TowerPanelLayer_hpp
#define TowerPanelLayer_hpp

#include "cocos2d.h"
#include "FilePathHeader.h"



class TowerPanelLayer: public cocos2d::Layer
{
    CC_SYNTHESIZE_READONLY(TOWERTYPE, towerType, TowerType);
public:
    virtual ~TowerPanelLayer();
    virtual bool init() override;
    CREATE_FUNC(TowerPanelLayer);

    void addTower(cocos2d::Sprite *tower);
    
    void placeTower(cocos2d::Sprite *touch);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) override;
private:
    cocos2d::Vector<cocos2d::Sprite*> towerVec;
    
    void addListener();
};

#endif /* TowerPanelLayer_hpp */
