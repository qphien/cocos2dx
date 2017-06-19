//
//  SettingScene.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/16.
//
//

#include "SettingScene.hpp"
#include "SimpleAudioEngine.h"
#include "PlayScene.hpp"
using namespace CocosDenshion;
USING_NS_CC;
USING_NS_CC_EXT;

SettingScene::SettingScene(float bv, float mv): musicEffectVolumn(mv), backgroundMusicVolumn(bv),
                              preMusicEffectVolumn(mv), preBackgroundMusicVolumn(bv)
{
}

SettingScene* SettingScene::create(float backgroundMusicVolumn, float musicEffectVolumn)
{
    auto p = new SettingScene(backgroundMusicVolumn, musicEffectVolumn);
    if(p && p->init())
    {
        p->autorelease();
        return p;
    }
    else
    {
        delete p;
        p = NULL;
        return p;
    }
}

bool SettingScene::init()
{
    if(!Layer::init())
        return false;
//    this->initWithColor(Color4B(162, 162, 162, 128));
    auto winSize = Director::getInstance()->getWinSize();
    
    auto layColor = LayerColor::create(Color4B(162, 162, 162, 128));
    this->addChild(layColor);
    //Add back button
    auto btnBackItem = MenuItemImage::create("btn_back.png", "btn_back_press.png", CC_CALLBACK_1(SettingScene::menuBackCallBack, this));
    btnBackItem->setPosition(Vec2(40, 40));

    //Add background music slider
    auto backgroundMusicSlider = createSlider("SliderTrack.png", "SliderProgress.png", "SliderThumb.png");
    backgroundMusicSlider->setTag(SettingTag::BACKGROUND_MUSIC_SLIDER);
    backgroundMusicSlider->setPosition(winSize.width / 2, winSize.height / 2 + 50);
    this->addChild(backgroundMusicSlider);
    
    //Add music effect slider
    auto musicEffectSlider = createSlider("SliderTrack.png", "SliderProgress.png", "SliderThumb.png");
    musicEffectSlider->setTag(SettingTag::MUSIC_EFFECT_SLIDER);
    musicEffectSlider->setPosition(winSize.width / 2, winSize.height / 2 - 50);
    this->addChild(musicEffectSlider);
    
    //Add background music box
    auto backgroundMusicBox = createSettingBox("Box.png", "BoxSelected.png");
    backgroundMusicBox->setPosition(backgroundMusicSlider->getPositionX() - backgroundMusicSlider->getContentSize().width / 2 - 50, backgroundMusicSlider->getPositionY());
    backgroundMusicBox->setTag(SettingTag::BACKGROUND_MUSIC_BOX);
    
    //Add music effect box
    auto musicEffectBox = createSettingBox("Box.png", "BoxSelected.png");
    musicEffectBox->setPosition(musicEffectSlider->getPositionX() - musicEffectSlider->getContentSize().width / 2 - 50, musicEffectSlider->getPositionY());
    musicEffectBox->setTag(SettingTag::MUSIC_EFFECT_BOX);
    
    //Add menu
    auto menu = Menu::create(btnBackItem, backgroundMusicBox, musicEffectBox, NULL);
    menu->setPosition(Vec2::ZERO);
    menu->setTag(SettingTag::MENU);
    this->addChild(menu);

    
    //Control slider setValue member function will call sliderCallBack
    //Ater initiation of backgroundMusicBox and musicEffectBox, setValue member function
    //can be called
    backgroundMusicSlider->setValue(backgroundMusicVolumn);
    musicEffectSlider->setValue(musicEffectVolumn);
    
    //Swallow touch
    auto touchListener = EventListenerTouchOneByOne::create();
    
    //Only if onTouchBegan return true, setSwallowTouched works;
    touchListener->onTouchBegan = [](Touch *touch, Event *event)
    {
        return true;
    };
    touchListener->onTouchEnded = [&](Touch *touch, Event *event)
    {
        this->menuBackCallBack(NULL);
    };
    touchListener->setSwallowTouches(true);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

MenuItemToggle* SettingScene::createSettingBox(const std::string &file1, const std::string &file2)
{
    auto boxNormalItem = MenuItemImage::create(file1.c_str(), file1.c_str());
    auto boxSelectedItem = MenuItemImage::create(file2.c_str(), file2.c_str());
//    auto sprite1 = Sprite::create(file1.c_str());
//    auto sprite2 = Sprite::create(file2.c_str());
//    auto boxNormalItem = MenuItemSprite::create(sprite1, sprite1);
//    auto boxSelectedItem = MenuItemSprite::create(sprite2, sprite2);
    auto menuToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScene::menuCallBack, this), boxNormalItem, boxSelectedItem, NULL);
    menuToggle->setSelectedIndex(1);
    return menuToggle;
}

ControlSlider* SettingScene::createSlider(const std::string &trackFile, const std::string &progressFile, const std::string &thumbFile)
{
    auto slider = ControlSlider::create(trackFile.c_str(), progressFile.c_str(), thumbFile.c_str());
    slider->setMinimumValue(0);
    slider->setMaximumValue(100);
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(SettingScene::sliderCallBack), Control::EventType::VALUE_CHANGED);
    return slider;
}

void SettingScene::menuCallBack(cocos2d::Ref *pSender)
{
    auto menuToggle = static_cast<MenuItemToggle*>(pSender);
    int tag = menuToggle->getTag();
    if(tag == SettingTag::BACKGROUND_MUSIC_BOX)
    {
        auto backgroundMusicSlider = static_cast<ControlSlider*>(this->getChildByTag(SettingTag::BACKGROUND_MUSIC_SLIDER));
        if(menuToggle->getSelectedIndex() == 0)
        {
            preBackgroundMusicVolumn = backgroundMusicVolumn;
            backgroundMusicVolumn = 0;
            SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(backgroundMusicVolumn);
            backgroundMusicSlider->setValue(backgroundMusicVolumn);
        }
        else
        {
            backgroundMusicVolumn = preBackgroundMusicVolumn;
            SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(backgroundMusicVolumn);
            backgroundMusicSlider->setValue(backgroundMusicVolumn);
        }
    }
    else
    {
        auto musicEffectSlider = static_cast<ControlSlider*>(this->getChildByTag(SettingTag::MUSIC_EFFECT_SLIDER));
        if(menuToggle->getSelectedIndex() == 0)
        {
            preMusicEffectVolumn = musicEffectVolumn;
            musicEffectVolumn = 0;
            SimpleAudioEngine::getInstance()->setEffectsVolume(musicEffectVolumn / 100);
            musicEffectSlider->setValue(musicEffectVolumn);
        }
        else
        {
            musicEffectVolumn = preMusicEffectVolumn;
            SimpleAudioEngine::getInstance()->setEffectsVolume(musicEffectVolumn / 100);
            musicEffectSlider->setValue(musicEffectVolumn);
        }
    }
}

void SettingScene::sliderCallBack(cocos2d::Ref *pSender, cocos2d::extension::Control::EventType controlEvent)
{
    auto slider = static_cast<ControlSlider*>(pSender);
    int tag = slider->getTag();
    auto menu = static_cast<Menu*>(this->getChildByTag(SettingTag::MENU));
    if(tag == SettingTag::BACKGROUND_MUSIC_SLIDER)
    {
        
        backgroundMusicVolumn = slider->getValue();
        log("backgroundMusicVolumn: %f", backgroundMusicVolumn);
       // preBackgroundMusicVolumn = backgroundMusicVolumn;
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(backgroundMusicVolumn / 100);
         auto backgroundMusicBox = static_cast<MenuItemToggle*>(menu->getChildByTag(SettingTag::BACKGROUND_MUSIC_BOX));
        if(backgroundMusicVolumn == 0)
            backgroundMusicBox->setSelectedIndex(0);
        else
            backgroundMusicBox->setSelectedIndex(1);
    }
    else if(tag == SettingTag::MUSIC_EFFECT_SLIDER)
    {
        musicEffectVolumn = slider->getValue();
       // preMusicEffectVolumn = musicEffectVolumn;
        SimpleAudioEngine::getInstance()->setEffectsVolume(musicEffectVolumn / 100);
        auto musicEffectBox = static_cast<MenuItemToggle*>(menu->getChildByTag(SettingTag::MUSIC_EFFECT_BOX));
        if(musicEffectVolumn == 0)
            musicEffectBox->setSelectedIndex(0);
        else
            musicEffectBox->setSelectedIndex(1);
    }
}

void SettingScene::menuBackCallBack(cocos2d::Ref *pSender)
{
    auto playScene = static_cast<PlayScene*>(this->getParent());
    auto allChildren = playScene->getChildren();
    for(auto child: allChildren)
        child->resume();
    playScene->schedule(schedule_selector(PlayScene::addEnemy), 2.0f);
    playScene->musicEffectVolumn = musicEffectVolumn;
    playScene->backgroundMusicVolumn = backgroundMusicVolumn;
    this->removeFromParentAndCleanup(true);
}
