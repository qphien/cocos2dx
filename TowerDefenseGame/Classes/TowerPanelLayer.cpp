//
//  TowerPanelLayer.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/8.
//
//

#include "TowerPanelLayer.hpp"
USING_NS_CC;

TowerPanelLayer::~TowerPanelLayer()
{
    towerVec.clear();
}

bool TowerPanelLayer::init()
{
    if(!Layer::init())
        return false;
    
    towerType = TOWERTYPE::OTHER;
    auto touchSprite = Sprite::createWithSpriteFrameName("towerPos.png");
    touchSprite->setPosition(Vec2::ZERO);
    this->addChild(touchSprite);
    
    auto arrowTower = Sprite::createWithSpriteFrameName("ArrowTower1.png");
    arrowTower->setTag(ARROW_TOWER);
    this->addTower(arrowTower);
    
    auto attackTower = Sprite::createWithSpriteFrameName("AttackTower1.png");
    attackTower->setTag(ATTACK_TOWER);
    this->addTower(attackTower);
    
    auto multiDirTower = Sprite::createWithSpriteFrameName("MultiDirTower1.png");
    multiDirTower->setTag(MULTIIDR_TOWER);
    this->addTower(multiDirTower);
    
    placeTower(touchSprite);
    
    //Add touchListener
    this->addListener();
    
    return true;
}

void TowerPanelLayer::addListener()
{
//    auto towerVecSize = towerVec.size();
//    if(towerVecSize == 0)
//        return;
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(TowerPanelLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(TowerPanelLayer::onTouchEnded, this);
    touchListener->setSwallowTouches(true);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
//    if(towerVecSize > 1)
//    {
//        for(int i = 1; i != towerVecSize; ++i)
//            dispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), towerVec.at(i));
//    }
}

void TowerPanelLayer::addTower(cocos2d::Sprite *tower)
{
    this->addChild(tower);
    towerVec.pushBack(tower);
}

//This function can changed according to requirments
void TowerPanelLayer::placeTower(Sprite *touch)
{
    auto touchSpirteSize = touch->getContentSize();
    for(int i = 0; i != towerVec.size(); ++i)
    {
        auto tower = towerVec.at(i);
        tower->setAnchorPoint(Vec2(0.5, 0));
        auto posX = touchSpirteSize.width * (i - 1);
        tower->setPosition(posX, touchSpirteSize.height / 2);
    }
}

bool TowerPanelLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    //eventListener add with scene priority 会对所有add的节点进行判别直到有一个返回true
    //并且判断顺序为添加顺序的相反顺序
//    auto target = static_cast<Sprite*>(event->getCurrentTarget());
//    log("target tag: %d", target->getTag());
//    towerType = TOWERTYPE(target->getTag());
    
    //convert world touch position to node position
//    if(target->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch)))
//    {
//        log("in if");
//        target->setOpacity(180);
//        return true;
//    }
//    return false;
    auto touchPos = this->convertTouchToNodeSpace(touch);
    for(int i = 0; i != towerVec.size(); ++i)
    {
        if(towerVec.at(i)->getBoundingBox().containsPoint(touchPos))
        {
            towerType = TOWERTYPE(towerVec.at(i)->getTag());
            towerVec.at(i)->setOpacity(180);
            break;
        }
    }
    return true;
}

//Remove this layer when touch ends
void TowerPanelLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    //log("in TowerPanelLayer touchEnded");
    
    //remove TowerPanel Layer
    EventCustom customeEvent("towerType");
    customeEvent.setUserData(&towerType);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&customeEvent);
    this->removeFromParent();
}
