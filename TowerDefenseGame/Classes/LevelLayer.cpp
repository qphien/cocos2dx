//
//  LevelLayer.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/7.
//
//

#include "LevelLayer.hpp"
USING_NS_CC;

LevelLayer::LevelLayer(): totalPages(0), curPage(0)
{
    
}

bool LevelLayer::init()
{
    if(!Layer::init())
        return false;
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(LevelLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(LevelLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(LevelLayer::onTouchEnded, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void LevelLayer::addPage(cocos2d::Node *page)
{
    auto winSize = Director::getInstance()->getWinSize();
    if(page)
    {
        page->setContentSize(winSize);
        page->setAnchorPoint(Vec2(0, 0));
        page->setPosition(totalPages * winSize.width, 0);
       // log("page pos: %f, %f", page->getPositionX(), page->getPositionY());
        ++totalPages;
        this->addChild(page);
    }
}

bool LevelLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    touchBeganPos = touch->getLocation();
    curPos = this->getPosition();
    //log("in onTouchBegan, curPos: %f, %f", curPos.x, curPos.y);
    return true;
}

void LevelLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto movedPos = touch->getLocation();
    auto distance = movedPos.x - touchBeganPos.x;
    //log("in onTouchMoved, distance: %f", distance);
    this->setPosition(Vec2(curPos.x + distance, curPos.y));
}

void LevelLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto endedPos = touch->getLocation();
    auto distance = endedPos.x - touchBeganPos.x;
    auto direction = moveDirection(distance);
    if(direction != NOMOVE)
        movePage(direction);
    else
    {
        auto moveTo = MoveTo::create(0.2f, curPos);
        this->runAction(moveTo);
    }

}

Direction LevelLayer::moveDirection(const float &distance)
{
    
    if(distance > SHORTEST_SLIDE_DISTANCE && curPage > 0)
        return RIGHT;
    else if(distance < -SHORTEST_SLIDE_DISTANCE && curPage < totalPages - 1)
        return LEFT;
    return NOMOVE;
}
void LevelLayer::movePage(Direction direction)
{
    auto winSize = Director::getInstance()->getWinSize();
    MoveTo *moveTo = NULL;
    if(direction == LEFT)
    {
        moveTo = MoveTo::create(0.4, Vec2(-winSize.width * (curPage + 1), 0));
        ++curPage;
    }
    else
    {
        log("curPage: %d", curPage);
        moveTo = MoveTo::create(0.4, Vec2(-winSize.width * (curPage - 1), 0));
        --curPage;
    }
    this->runAction(moveTo);
}

