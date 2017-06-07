//
//  LevelScene.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/6.
//
//

#include "LevelScene.hpp"
#include "StartScene.hpp"
#include "LevelSelected.hpp"
#include "LevelLayer.hpp"

USING_NS_CC;

Scene* LevelScene::createScene()
{
    auto scene = Scene::create();
    auto layer = LevelScene::create();
    scene->addChild(layer);
    return scene;
}

bool LevelScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    auto winSize = Director::getInstance()->getWinSize();
    //Add background
    auto background = Sprite::create("playbg.png");
    background->setPosition(winSize / 2);
    this->addChild(background, -2);

    //Add house
    auto house = Sprite::create("House.png");
    house->setPosition(winSize.width - house->getContentSize().width - 30, winSize.height / 4);
    this->addChild(house);
    
    //Add Back Button
    auto btnBackItem = MenuItemImage::create("btn_back.png", "btn_back_press.png", CC_CALLBACK_1(LevelScene::menuBackCallBack, this));
    btnBackItem->setPosition(Vec2(40, 40));
    auto menu = Menu::create(btnBackItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    //Add LevelSelected Node
    auto levelLayer = LevelLayer::create();
    levelLayer->setAnchorPoint(Vec2(0, 0));
    levelLayer->setPosition(0, 0);
    for(int i = 0; i != 3; ++i)
    {
        auto str = __String::createWithFormat("selectLevelBg%d.png", i);
        auto levelSelected = LevelSelected::createLevelSelected(str->getCString(), i);
        levelLayer->addPage(levelSelected);
    }
    this->addChild(levelLayer, -1);
    
    //Add Snow Particle
    auto snow = ParticleSystemQuad::create("snow.plist");
    auto batch = ParticleBatchNode::createWithTexture(snow->getTexture());
    batch->addChild(snow);
    snow->setPosition(winSize.width / 2, winSize.height);
    this->addChild(batch, 10);
    
    return true;
}

void LevelScene::menuBackCallBack(cocos2d::Ref *pSender)
{
    log("in menuBackCallBack");
    transitionScene();
}

void LevelScene::transitionScene()
{
    auto startScene = StartScene::createScene();
    auto transitionFade = TransitionFade::create(0.1f, startScene);
    Director::getInstance()->replaceScene(transitionFade);
}
