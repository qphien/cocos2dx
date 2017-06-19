//
//  SettingScene.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/16.
//
//

#ifndef SettingScene_hpp
#define SettingScene_hpp

#include "cocos2d.h"
#include "cocos-ext.h"

class SettingScene: public cocos2d::Layer
{
    enum SettingTag
    {
        BACKGROUND_MUSIC_BOX = 1,
        MUSIC_EFFECT_BOX,
        BACKGROUND_MUSIC_SLIDER,
        MUSIC_EFFECT_SLIDER,
        MENU
    };
public:
    SettingScene(float bv, float mv);
    SettingScene() {};
//  static cocos2d::Scene* createScene();
    virtual bool init();
    static SettingScene* create(float backgroundMusicVolumn, float musicEffectVolumn);
    
    cocos2d::MenuItemToggle* createSettingBox(const std::string &file1, const std::string &file2);
    cocos2d::extension::ControlSlider* createSlider(const std::string &trackFile, const std::string &progressFile,
                                const std::string &thumbFile);
    
    void menuCallBack(cocos2d::Ref *pSender);
    
    void sliderCallBack(cocos2d::Ref *pSender, cocos2d::extension::Control::EventType controlEvent);
    
    void menuBackCallBack(cocos2d::Ref *pSender);
private:
    float backgroundMusicVolumn;
    float musicEffectVolumn;
    float preBackgroundMusicVolumn;
    float preMusicEffectVolumn;
};

#endif /* SettingScene_hpp */
