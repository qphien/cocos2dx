//
//  LevelLayer.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/7.
//
//

#ifndef LevelLayer_hpp
#define LevelLayer_hpp

#include "cocos2d.h"

#define SHORTEST_SLIDE_DISTANCE 100
enum Direction
{
    LEFT = -1,
    RIGHT = 1,
    NOMOVE = 0
};
class LevelLayer: public cocos2d::Layer
{
public:
    LevelLayer();
    CREATE_FUNC(LevelLayer);
    virtual bool init();
    
    void addPage(cocos2d::Node *page);

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    
    void movePage(Direction direction);
    inline Direction moveDirection(const float &distance);
private:
    int totalPages;
    int curPage;
    cocos2d::Vec2 curPos;
    cocos2d::Vec2 touchBeganPos;
};


#endif /* LevelLayer_hpp */
