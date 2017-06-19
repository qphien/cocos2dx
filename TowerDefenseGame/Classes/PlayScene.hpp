//
//  PlayScene.hpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/8.
//
//

#ifndef PlayScene_hpp
#define PlayScene_hpp

#include "cocos2d.h"
#include "GameManager.hpp"
#include "LevelInfoScene.hpp"
#include "ThiefEnemy.hpp"
#include "PirateEnemy.hpp"
#include "BanditEnemy.hpp"
#include "FilePathHeader.h"
#include "TowerBase.hpp"
#include "ArrowTower.hpp"
#include "AttackTower.hpp"
#include "MultiDirTower.hpp"
#include "GameOver.hpp"
#include "PassLevelScene.hpp"

#define TILE_NUMBER_X 16
#define TILE_NUMBER_Y 9

class PlayScene: public cocos2d::Layer
{
    friend class SettingScene;
public:
    PlayScene();
    ~PlayScene();
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(PlayScene);
    
    void initToolLayer();
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

    void onTouchResume() { cocos2d::Director::getInstance()->resume(); }
    void addEnemy(float dt);

private:
    enum MenuTag
    {
        BACK_TAG,
        SETTING_TAG
    };
    
    GameManager *_instance;
    cocos2d::Label *moneyLabel;
    cocos2d::Label *curBunchLabel;
    //cocos2d::Vec2 tilePos;
    int tileIDX;
    int tileIDY;
    int enemyWaveNumber;
    int money;
    float maxHp;
    float curHp;
    int curBunch;
    float backgroundMusicVolumn;
    float musicEffectVolumn;
    TOWERTYPE towerType;
    cocos2d::Vec2 towerPosition;
    cocos2d::TMXTiledMap *map;
    cocos2d::TMXLayer *tmxLayer;
    std::vector<bool> towerVec[TILE_NUMBER_X];
    cocos2d::EventListenerTouchOneByOne *touchListener;
//    cocos2d::Size tileSize;
    
    cocos2d::ProgressTimer *hpBar;
    cocos2d::Vector<cocos2d::Node*> movingPath;
    
    void backCallback(cocos2d::Ref *pSender);
    void menuStartOrPauseCallBack(cocos2d::Ref *pSender);
    void menuSettingCallBack(cocos2d::Ref *pSender);
    
    void beAttacked(cocos2d::EventCustom *event);
    void getEnemyMovingPath(cocos2d::TMXObjectGroup *objGroup);
    void setMoneyLabel(cocos2d::EventCustom *custom);
    bool canAddTower(const cocos2d::Vec2 &position);
    cocos2d::Vec2 convertToTileCoord(const cocos2d::Vec2 &position);
    void addTower(cocos2d::EventCustom *event);
    void warning(const std::string &fileName, const cocos2d::Vec2 &position);
    void setAward();

};

#endif /* PlayScene_hpp */
