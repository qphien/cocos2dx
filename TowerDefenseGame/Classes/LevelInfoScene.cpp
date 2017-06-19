//
//  LevelInfoScene.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/7.
//
//

#include "LevelInfoScene.hpp"
#include "SimpleAudioEngine.h"
#include "LevelScene.hpp"
#include "LoadInfo.hpp"
#include "PlayScene.hpp"

using namespace CocosDenshion;

USING_NS_CC;

Scene* LevelInfoScene::createScene()
{
    auto scene = Scene::create();
    auto layer = LevelInfoScene::create();
    scene->addChild(layer);
    return scene;
}

bool LevelInfoScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    
    //Add background
    auto background = Sprite::create("playbg.png");
    background->setPosition(winSize / 2);
    this->addChild(background, -1);
    
    //Get star number
    auto levelFile = UserDefault::getInstance()->getStringForKey("levelFile");
    auto starNumber = UserDefault::getInstance()->getIntegerForKey(levelFile.c_str());
    log("starNumber: %d", starNumber);
    
    //Add Star
    auto starbgWidth = Sprite::createWithSpriteFrameName("starbg.png")->getContentSize().width;
    //log("starbgSize: %f", starbgWidth);
    auto startPosX = (winSize.width - STAR_NUMBER * starbgWidth) / 2;
    for(int i = 0; i != STAR_NUMBER; ++i)
    {
        auto star = Sprite::createWithSpriteFrameName("starbg.png");
        star->setPosition(startPosX + i * starbgWidth, winSize.height * 2 /3);
        star->setAnchorPoint(Vec2(0, 0.5));
        this->addChild(star);
    }
    for(int i = 0; i != starNumber; ++i)
    {
        auto starbg = Sprite::createWithSpriteFrameName("star.png");
        starbg->setPosition(startPosX + i * starbgWidth, winSize.height * 2 / 3);
        starbg->setAnchorPoint(Vec2(0, 0.5));
        this->addChild(starbg);
    }
    
    //Add LevelInfo Panel
    auto levelInfoPanel = Sprite::create("LevelInfoPanel.png");
    levelInfoPanel->setPosition(winSize / 2);
    this->addChild(levelInfoPanel, -1);
    
    //Add Button
    auto btnStartSp = Sprite::createWithSpriteFrameName("btnStart.png");
    auto btnBackSp = Sprite::createWithSpriteFrameName("btnBack.png");
    auto btnStartItem = MenuItemSprite::create(btnStartSp, btnStartSp, CC_CALLBACK_1(LevelInfoScene::menuStartCallBack, this));
    auto btnBackItem = MenuItemSprite::create(btnBackSp, btnBackSp, CC_CALLBACK_1(LevelInfoScene::menuBackCallBack, this));
    auto menu = Menu::create(btnStartItem, btnBackItem, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(winSize.width / 2, winSize.height / 6);

    this->addChild(menu);
    return true;
}

void LevelInfoScene::menuStartCallBack(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
    
    //Load level info
    std::string fileName = UserDefault::getInstance()->getStringForKey("levelFile");
    //log("load info file: %s",fileName.c_str());
    
    auto loadInfo = LoadInfo::createWithFile(fileName);
    loadInfo->readInfo();
    
    //transition Scene
    auto playScene = PlayScene::createScene();
    auto transitionFade = TransitionFade::create(0.2f, playScene);
    Director::getInstance()->replaceScene(transitionFade);
}

void LevelInfoScene::menuBackCallBack(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
    auto scene = LevelScene::createScene();
    auto transitionFadeTR = TransitionFadeTR::create(0.5, scene);
    Director::getInstance()->replaceScene(transitionFadeTR);
}


