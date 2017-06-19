//
//  GameOver.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/12.
//
//

#include "GameOver.hpp"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

Scene* GameOver::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOver::create();
    scene->addChild(layer);
    return scene;
}

bool GameOver::init()
{
    if(!Layer::init())
        return false;
    
    auto winSize = Director::getInstance()->getWinSize();
    //Clear gameManager
    GameManager::getInstance()->clear();
    
    auto background = Sprite::create("playbg.png");
    background->setPosition(winSize / 2);
    this->addChild(background, -1);
    
    auto failedPanel = Sprite::createWithSpriteFrameName("failedPanel.png");
    failedPanel->setPosition(-winSize.width / 2, winSize.height / 2);
    this->addChild(failedPanel, -1);
    
    auto backItem = Sprite::createWithSpriteFrameName("btnBack.png");
    auto back = MenuItemSprite::create(backItem, backItem, CC_CALLBACK_1(GameOver::menuBackCallBack, this));
    back->setPosition(failedPanel->getContentSize().width / 2, failedPanel->getContentSize().height / 6);
    
    auto menu = Menu::create(back, NULL);
    menu->setPosition(Vec2::ZERO);
    failedPanel->addChild(menu);
    
    failedPanel->runAction(Sequence::create(DelayTime::create(0.5),
                                            EaseElasticOut::create(MoveBy::create(0.8f, Vec2(winSize.width, 0))), NULL));
    
    auto particle = ParticleSystemQuad::create("changjing.plist");
    particle->retain();
    auto batch = ParticleBatchNode::createWithTexture(particle->getTexture());
    batch->addChild(particle);
    particle->release();
    particle->setPosition(winSize.width / 2, 0);
    this->addChild(batch, 10);
    
    return true;
}

void GameOver::menuBackCallBack(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect("sound/button.wav", false);
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, LevelScene::createScene()));
}
