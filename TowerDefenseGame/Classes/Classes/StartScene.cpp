//
//  StartScene.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/6.
//
//

#include "StartScene.hpp"
#include "LevelScene.hpp"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* StartScene::createScene()
{
    auto scene = Scene::create();
    auto layer = StartScene::create();
    scene->addChild(layer);
    return scene;
}

void StartScene::onEnter()
{
    Layer::onEnter();
    SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/music.mp3", true);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
}

bool StartScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    
    //Add background
    auto background = Sprite::create("playbg.png");
    background->setPosition(winSize / 2);
    this->addChild(background, -1);
    
    //Add title
    auto title = Sprite::createWithSpriteFrameName("title.png");
    title->setPosition(winSize.width / 3, winSize.height / 3 * 2);
    this->addChild(title, 0);
    //Add title action
    auto action = MoveBy::create(1.0, Vec2(0, 10));
    auto seq = Sequence::create(action, action->reverse(), NULL);
    title->runAction(RepeatForever::create(seq));
    
    //Add StartGame Button
    auto buttonItem = MenuItemImage::create("start_1.png", "start_2.png", CC_CALLBACK_1(StartScene::menuStartCallBack, this));
    buttonItem->setPosition(winSize.width / 2, winSize.height / 6);
    auto menu = Menu::create(buttonItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    //Add Star
    auto star = Sprite::createWithSpriteFrameName("star.png");
    star->setScale(0.7f);
    star->setPosition(buttonItem->getPosition().x - buttonItem->getContentSize().width / 2, buttonItem->getPosition().y - buttonItem->getContentSize().height / 2);
    this->addChild(star, 11);
    
    //Add Star particle
    auto emitter = ParticleSystemQuad::create("button.plist");
    auto batch = ParticleBatchNode::createWithTexture(emitter->getTexture());
    batch->addChild(emitter);
    emitter->setPosition(buttonItem->getPosition().x - buttonItem->getContentSize().width / 2, buttonItem->getPosition().y - buttonItem->getContentSize().height / 2);
    this->addChild(batch, 10);
    
    //Set Star Action
    auto starAction = getStarAction(50, buttonItem->getContentSize().height, buttonItem->getContentSize().width);
    star->runAction(starAction);
    emitter->runAction(starAction->clone());
    
    return true;
}

RepeatForever* StartScene::getStarAction(float controlX, float controlY, float width)
{
    ccBezierConfig bezier1;
    bezier1.controlPoint_1 = Vec2(-controlX, 0);
    bezier1.controlPoint_2 = Vec2(-controlX, controlY);
    bezier1.endPosition = Vec2(0, controlY);
    auto bezierBy1 = BezierBy::create(0.6f, bezier1);
    
    auto moveBy1 = MoveBy::create(0.7f, Vec2(width, 0));
    
    ccBezierConfig bezier2;
    bezier2.controlPoint_1 = Vec2(controlX, 0);
    bezier2.controlPoint_2 = Vec2(controlX, -controlY);
    bezier2.endPosition = Vec2(0, -controlY);
    auto bezierBy2 = BezierBy::create(0.6f, bezier2);
    
    auto moveBy2 = MoveBy::create(0.7f, Vec2(-width, 0));
    
    auto seq = Sequence::create(bezierBy1, moveBy1, bezierBy2, moveBy2, NULL);
    
    return RepeatForever::create(seq);
}

void StartScene::menuStartCallBack(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
    transitionScene();
}

void StartScene::transitionScene()
{
    auto levelScene = LevelScene::createScene();
    auto transitionFade = TransitionFade::create(0.1f, levelScene);
    Director::getInstance()->pushScene(transitionFade);
}
