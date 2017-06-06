//
//  LevelSelected.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/6.
//
//

#include "LevelSelected.hpp"
USING_NS_CC;

LevelSelected* LevelSelected::createLevelSelected(const std::string &fileName, int number)
{
    auto p = new LevelSelected();
    if(p && p->initLevelSelected(fileName, number))
    {
        p->autorelease();
        return p;
    }
    else
    {
        delete p;
        p = nullptr;
        return NULL;
    }
}

bool LevelSelected::initLevelSelected(const std::string &fileName, int number)
{
    if(!Node::init())
        return false;
    
    auto winSize = Director::getInstance()->getWinSize();
    //Add background
    auto background = Sprite::create(fileName);
    background->setPosition(winSize / 2);
    this->addChild(background, -1);
    
    //Get Item Start Position
    auto itemContentSize = Sprite::create("card_1.png")->getContentSize();
    auto gap = itemContentSize.width / 4;
    auto startPosX = background->getContentSize().width / 2 + background->getPositionX() - COL * (
                                                                                                  itemContentSize.width + gap) - gap;
    auto startPosY = background->getPositionY() + background->getContentSize().height / 2 - 2 * gap;
    
    //Add Items
    Vector<MenuItem*> menuItemVec;
    for(int i = 0; i != COL; ++i)
    {
        for(int j = 0; j != ROW; ++j)
        {
            auto posX = startPosX + i * (itemContentSize.width + gap);
            auto posY = startPosY - j * (itemContentSize.height + gap);
            auto menuItem = MenuItemImage::create("card_1.png", "card_2.png", "card_3.png", CC_CALLBACK_1(LevelSelected::menuCallBack, this));
            menuItem->setAnchorPoint(Vec2(0, 1));
            menuItem->setPosition(posX, posY);
            auto levelNum = UserDefault::getInstance()->getIntegerForKey("levelNum");
            log("levelNum: %d", levelNum);
            if(levelNum - ROW * COL * number < i * COL + j)
            {
                menuItem->setEnabled(false);
            }
            menuItemVec.pushBack(menuItem);
        }
    }
    auto menu = Menu::createWithArray(menuItemVec);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    return true;
}

void LevelSelected::menuCallBack(cocos2d::Ref *pSender)
{
    
}
