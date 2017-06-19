//
//  PassLevelScene.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/12.
//
//

#include "PassLevelScene.hpp"
#include "GameManager.hpp"
#include "SimpleAudioEngine.h"
#include "LevelScene.hpp"
#include "LevelInfoScene.hpp"

using namespace CocosDenshion;
USING_NS_CC;

Scene* PassLevelScene::createScene()
{
    auto scene = Scene::create();
    auto layer = PassLevelScene::create();
    scene->addChild(layer);
    return scene;
}

bool PassLevelScene::init()
{
    if(!Layer::init())
        return false;
    
    auto winSize = Director::getInstance()->getWinSize();
    
    GameManager::getInstance()->clear();
    
    auto background = Sprite::create("successfulBg.png");
    background->setPosition(winSize / 2);
    this->addChild(background, -1);
    
    auto backItem1 = Sprite::createWithSpriteFrameName("btnBack.png");
    auto nextItem1 = Sprite::createWithSpriteFrameName("btnNext.png");
    auto menuBack = MenuItemSprite::create(backItem1, backItem1, CC_CALLBACK_1(PassLevelScene::menuBackCallBack, this));
    auto menuNext = MenuItemSprite::create(nextItem1, nextItem1, CC_CALLBACK_1(PassLevelScene::menuNextCallBack, this));
    auto menu = Menu::create(menuNext, menuBack, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(winSize.width / 2, winSize.height / 6);
    this->addChild(menu);
    
    return true;
}

void PassLevelScene::menuBackCallBack(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect("sound/button.wav", false);
    Director::getInstance()->replaceScene(TransitionFade::create(0.1f, LevelScene::createScene()));
}

void PassLevelScene::menuNextCallBack(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect("sound/button.wav", false);
    Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5f, LevelInfoScene::createScene()));
}
