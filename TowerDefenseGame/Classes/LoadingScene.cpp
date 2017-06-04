//
//  LoadingScene.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/4.
//
//

#include "LoadingScene.hpp"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
LoadingScene::LoadingScene(): progressTimer(NULL), numberOfLoadingResouce(0),
                            totalResources(total)
{
    
}

Scene* LoadingScene::createScene()
{
    auto scene = Scene::create();
    auto layer = LoadingScene::create();
    scene->addChild(layer);
    return scene;
}

bool LoadingScene::init()
{
    if(!Layer::init())
        return false;
    progressTimer = addProgressTimer();
    loadResources();
    return true;
}

ProgressTimer* LoadingScene::addProgressTimer()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //Add loadingBar background
    auto loadingBarBackground = Sprite::create("load.png");
    //CCASSERT(loadingBarBackground != NULL, "loadingBarBackground is NULL");
    loadingBarBackground->setPosition(visibleSize / 2);
    loadingBarBackground->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->addChild(loadingBarBackground, -1);
    
    //Add ProgressTimer
    auto pt = ProgressTimer::create(Sprite::create("loadBar.png"));
    //CCASSERT(pt != NULL, "pt is NULL");
    pt->setPosition(loadingBarBackground->getContentSize().width / 2, loadingBarBackground->getContentSize().height / 6);
    pt->setAnchorPoint(Vec2(0.5f, 0.5f));
    pt->setType(ProgressTimer::Type::BAR);
    pt->setMidpoint(Vec2(0, 0.5f));
    pt->setBarChangeRate(Vec2(1, 0));
    pt->setPercentage(0);
    loadingBarBackground->addChild(pt);
    
    return pt;
}
void LoadingScene::loadMusic()
{
    auto audioEngine = SimpleAudioEngine::getInstance();
    audioEngine->preloadBackgroundMusic(backgroundMusic);
    ++numberOfLoadingResouce;
    audioEngine->preloadEffect(playerDeadMusicEffect);
    ++numberOfLoadingResouce;
    audioEngine->preloadEffect(enemyDeadMusicEffect);
    ++numberOfLoadingResouce;
    audioEngine->preloadEffect(buttonMusicEffect);
    ++numberOfLoadingResouce;
    audioEngine->preloadEffect(bulletShootMusicEffect);
    ++numberOfLoadingResouce;
    audioEngine->preloadEffect(backMusicEffect);
    ++numberOfLoadingResouce;
    audioEngine->preloadEffect(tipMusicEffect);
    ++numberOfLoadingResouce;
}

void LoadingScene::loadResources()
{
    //preload music and music effect
    auto musicThread = new std::thread(&LoadingScene::loadMusic, this);
    musicThread->join();
    CC_SAFE_DELETE(musicThread);
    
    //add image resources
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Play.plist");
    ++numberOfLoadingResouce;
    auto textureCache = Director::getInstance()->getTextureCache();
    textureCache->addImageAsync("playbg.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
    textureCache->addImageAsync("playbg1.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
    textureCache->addImageAsync("successfulBg.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
    textureCache->addImageAsync("btn_back.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
    textureCache->addImageAsync("btn_back_press.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
    textureCache->addImageAsync("card_1.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
    textureCache->addImageAsync("card_2.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
    textureCache->addImageAsync("card_3.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
    textureCache->addImageAsync("LevelInfoPanel.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
    textureCache->addImageAsync("House.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
    textureCache->addImageAsync("selectLevelBg.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
    textureCache->addImageAsync("selectLevelBg1.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
    textureCache->addImageAsync("selectLevelBg2.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
    textureCache->addImageAsync("start_1.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
    textureCache->addImageAsync("start_2.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
}

void LoadingScene::loadingCallBack(cocos2d::Texture2D *texture)
{
    ++numberOfLoadingResouce;
    float percentage = static_cast<float>(numberOfLoadingResouce) / totalResources * 100;
    //log("percentage: %f", percentage);
    progressTimer->setPercentage(percentage);
//    if(numberOfLoadingResouce == totalResources)
//    {
//        //Transit into home scene
//        transitionScene();
//    }
}

void LoadingScene::transitionScene()
{
    
}
