//
//  PlayScene.cpp
//  SLG_GAME
//
//  Created by Dummy on 2017/6/8.
//
//

#include "PlayScene.hpp"
#include "SimpleAudioEngine.h"
#include "ThiefEnemy.hpp"
#include "TowerPanelLayer.hpp"
#include "SettingScene.hpp"

using namespace CocosDenshion;
USING_NS_CC;

PlayScene::PlayScene(): _instance(NULL), moneyLabel(NULL), curBunchLabel(NULL),
                        tileIDX(0), tileIDY(0), enemyWaveNumber(0), money(0), maxHp(100), curHp(100), backgroundMusicVolumn(50), musicEffectVolumn(50),
                        curBunch(0), towerType(TOWERTYPE::OTHER), towerPosition(Vec2(0, 0)),
                        hpBar(NULL), map(NULL), tmxLayer(NULL), touchListener(NULL)
{
    for(int i = 0; i != TILE_NUMBER_X; ++i)
        towerVec[i] = std::vector<bool>(TILE_NUMBER_Y, false);
}

PlayScene::~PlayScene()
{
    movingPath.clear();
    _instance->clear();
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    //listener which is added by use addwithfixedproprity must be removed manually
    touchListener->release();
    dispatcher->removeCustomEventListeners("EnemyDie");
    dispatcher->removeCustomEventListeners("towerType");
    dispatcher->removeCustomEventListeners("enemySuccess");
    log("PlayScene destroy");
}

Scene* PlayScene::createScene()
{
    auto scene = Scene::create();
    auto layer = PlayScene::create();
    scene->addChild(layer);
    return scene;
}

bool PlayScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    auto winSize = Director::getInstance()->getWinSize();
    _instance = GameManager::getInstance();
    
    //Add background
    auto background = Sprite::create(_instance->getBackground());
    background->setPosition(winSize / 2);
    this->addChild(background, -10);
    
    //Add Map
    map = TMXTiledMap::create(_instance->getMap());
    map->setAnchorPoint(Vec2(0.5, 0.5));
    map->setPosition(winSize / 2);
    this->addChild(map, -9);
    
    //Get TMXLayer
    tmxLayer = map->getLayer("bg");
    
    
    //Get Enemy Moving Path
    auto objGroup = map->getObjectGroup("obj");
    getEnemyMovingPath(objGroup);
    
    //Add tool layer
    initToolLayer();
    
    //Add touch listener
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    touchListener->retain();
    
    //Add custom event listener to reveive the event when enemy dies
    auto enemyDieListener = EventListenerCustom::create("EnemyDie", CC_CALLBACK_1(PlayScene::setMoneyLabel, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(enemyDieListener, 1);
    
    //Add custom eventListener to receive tower type
    auto towerTypeListener = EventListenerCustom::create("towerType", CC_CALLBACK_1(PlayScene::addTower, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(towerTypeListener, 1);
    
    //Add custom eventListener to receive enemySuccess event
    auto beAttackedListener = EventListenerCustom::create("enemySuccess", CC_CALLBACK_1(PlayScene::beAttacked, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(beAttackedListener, 1);
    
    //Add enemy
    //schedule(schedule_selector(PlayScene::addEnemy), 2.0f);
    auto enemy = ThiefEnemy::createWithSpriteFrameName("enemyRight1_1.png");
    enemy->setPosition(300, 140);
    this->addChild(enemy);
    
    _instance->addEnemy(enemy);
    
    return true;
}


void PlayScene::menuSettingCallBack(cocos2d::Ref *pSender)
{
    //pause
    unschedule(schedule_selector(PlayScene::addEnemy));
    auto allChildren = this->getChildren();
    for(auto child: allChildren)
    {
        child->pause();
    }
    auto settingLayer = SettingScene::create(backgroundMusicVolumn, musicEffectVolumn);
    //settingLayer->setPosition(winSize.width / 2, winSize.height / 2);
    auto fadeIn = FadeIn::create(0.3f);
    this->addChild(settingLayer);
//    auto callFunc = CallFunc::create([](){
//        Director::getInstance()->pause();
//    });
    settingLayer->runAction(fadeIn);
}

void PlayScene::menuStartOrPauseCallBack(cocos2d::Ref *pSender)
{
//    log("in pause");
//    log("ispaused: %d", Director::getInstance()->isPaused());
    //会让所有事件都不发送，从而menu也无法收到触摸事件
    //Director::getInstance()->getEventDispatcher()->setEnabled(false);
    auto menuItem = static_cast<MenuItem*>(pSender);
    auto menu = static_cast<Menu*>(menuItem->getParent());
    auto backItem = static_cast<MenuItem*>(menu->getChildByTag(MenuTag::BACK_TAG));
    auto settingItem = static_cast<MenuItem*>(menu->getChildByTag(MenuTag::SETTING_TAG));
    if(!Director::getInstance()->isPaused())
    {
        Director::getInstance()->pause();
        Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
        backItem->setEnabled(false);
        settingItem->setEnabled(false);
    }
    else
    {
        Director::getInstance()->resume();
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
        backItem->setEnabled(true);
        settingItem->setEnabled(true);
    }
}

void PlayScene::beAttacked(cocos2d::EventCustom *event)
{
    float damage = *static_cast<float*>(event->getUserData());
    this->curHp -= damage;
    hpBar->setPercentage(this->curHp / this->maxHp * 100);
    if(this->curHp <= 0)
    {
        //transition into GameOver scene
        auto gameOverScene = GameOver::createScene();
        auto transitionFade = TransitionFade::create(0.2f, gameOverScene);
        //unscheduleAllCallbacks();
        Director::getInstance()->replaceScene(transitionFade);
    }
    
}

void PlayScene::addEnemy(float dt)
{
    //log("addEnemy money: %d", money);
    //Next wave enemy
   // log("enemy number: %ld", _instance->getEnemySurvived().size());
    auto enemySurvived = _instance->getEnemySurvived();
    //log("total enemy: %d", _instance->getTotalEnemy());
    if(_instance->getTotalEnemy() == 0)
    {
        //一波敌人全部添加完等待，直到地图中没有敌人
        if(curBunch > 0 && enemySurvived.size() > 0)
            return;
        if(enemyWaveNumber < _instance->getEnemyGroup().size())
        {
            ++curBunch;
            //log("curBunch: %d", curBunch);
            curBunchLabel->setString(std::to_string(curBunch));
            auto enemyInfo = _instance->getEnemyGroup().at(enemyWaveNumber);
            ++enemyWaveNumber;
            _instance->setTotalEnemy(enemyInfo->getType1Num() + enemyInfo->getType2Num() +
                                     enemyInfo->getType3Num());
        }
        else if(enemySurvived.size() == 0)
        {
            //该关卡全部敌人已经死亡或到达终点, 过关
            int levelNum = UserDefault::getInstance()->getIntegerForKey("levelNum");
            if(levelNum <= UserDefault::getInstance()->getIntegerForKey("choosedLevel"))
                UserDefault::getInstance()->setIntegerForKey("levelNum", levelNum + 1);
            //log("max opened levelNum: %d", levelNum);
            //log("choosed level number: %d", UserDefault::getInstance()->getIntegerForKey("choosedLevel"));
            setAward();
            auto passLevelScene = PassLevelScene::createScene();
            auto transitionFade = TransitionFade::create(0.2f, passLevelScene);
            
           // unscheduleAllCallbacks();
            Director::getInstance()->replaceScene(transitionFade);
            return;
        }
    }
    else
    {
        //log("enemyWaveNumber - 1: %d", enemyWaveNumber - 1);
        auto enemyInfo = _instance->getEnemyGroup().at(enemyWaveNumber - 1);
        EnemyBase *enemy = NULL;
        if(enemyInfo->getType1Num() > 0)
        {
            enemyInfo->setType1Num(enemyInfo->getType1Num() - 1);
            enemy = ThiefEnemy::createWithSpriteFrameName("enemyRight1_1.png");
           // log("spawn thief");
        }
        else if(enemyInfo->getType2Num() > 0)
        {
            enemyInfo->setType2Num(enemyInfo->getType2Num() - 1);
            enemy = PirateEnemy::createWithSpriteFrameName("enemyRight2_1.png");
            //log("spawn pirate");
        }
        else if(enemyInfo->getType3Num() > 0)
        {
            enemyInfo->setType3Num(enemyInfo->getType3Num() - 1);
            enemy = BanditEnemy::createWithSpriteFrameName("enemyRight3_1.png");
            //log("spawn bandit");
        }
        if(!movingPath.empty())
            enemy->setPosition(movingPath.at(0)->getPosition());
        enemy->runFollowPoint(movingPath);
        _instance->setTotalEnemy(_instance->getTotalEnemy() - 1);
        _instance->addEnemy(enemy);
        this->addChild(enemy, 10);
    }
}

//设置过关获得的星星
void PlayScene::setAward()
{
    auto starNumber = 0;
    if(curHp > 0 && curHp <= 30)
        starNumber = 1;
    else if(curHp<= 60)
        starNumber = 2;
    else
        starNumber = 3;
    auto file = UserDefault::getInstance()->getStringForKey("levelFile");
    UserDefault::getInstance()->setIntegerForKey(file.c_str(), starNumber);
}

void PlayScene::getEnemyMovingPath(TMXObjectGroup  *objGroup)
{
    int count = 0;
    ValueMap obj = objGroup->getObject(std::to_string(count));
    while(obj.begin() != obj.end())
    {
        auto node = Node::create();
        auto x = obj.at("x").asFloat();
        auto y = obj.at("y").asFloat();
        node->setPosition(x, y);
        movingPath.pushBack(node);
        obj = objGroup->getObject(std::to_string(++count));
    }
}

void PlayScene::initToolLayer()
{
    auto winSize = Director::getInstance()->getWinSize();
    
    //Music Volumn
    musicEffectVolumn = SimpleAudioEngine::getInstance()->getEffectsVolume() * 100;
    backgroundMusicVolumn = SimpleAudioEngine::getInstance()->getBackgroundMusicVolume() * 100;
    log("musicEffectVolumn: %f", musicEffectVolumn);
    log("backgroundEffectVolumn: %f", backgroundMusicVolumn);
    
    //Create new layer
    auto toolLayer = Layer::create();
    this->addChild(toolLayer);
    
    //Add tool background
    auto spriteTool = Sprite::createWithSpriteFrameName("toolbg.png");
    spriteTool->setAnchorPoint(Vec2(0.5, 1));
    spriteTool->setPosition(winSize.width / 2, winSize.height);
    toolLayer->addChild(spriteTool);
    
    //
    auto spriteToolSize = spriteTool->getContentSize();
    
    //Add money label
   // money = _instance->getMoney();
    money = 10000;
    auto moneyText = std::to_string(money);
    moneyLabel = Label::createWithBMFont(fontsPath, moneyText);
    moneyLabel->setAnchorPoint(Vec2(0, 0.5));
    moneyLabel->setPosition(spriteToolSize.width / 8, spriteToolSize.height / 2);
    spriteTool->addChild(moneyLabel);

    
    //Add Hp bar
    hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("playhp.png"));
    hpBar->setType(ProgressTimer::Type::BAR);
    hpBar->setMidpoint(Vec2(0, 0.5));
    hpBar->setBarChangeRate(Vec2(1, 0));
    hpBar->setPercentage(100);
    hpBar->setPosition(spriteToolSize.width / 5 * 4, spriteToolSize.height / 2);
    spriteTool->addChild(hpBar);
    
    //Add Star
    auto star = Sprite::createWithSpriteFrameName("playstar.png");
    star->setPosition(spriteToolSize.width / 5 * 4, spriteToolSize.height / 2);
    spriteTool->addChild(star);
    
    //Add total bunch number
    auto totoalBunch = _instance->getEnemyGroup().size();
    auto totalBunchText = std::to_string(totoalBunch);
    auto totalBunchLabel = Label::createWithBMFont(fontsPath, totalBunchText);
    totalBunchLabel->setPosition(spriteTool->getContentSize() / 2);
    spriteTool->addChild(totalBunchLabel);
    
    //Add Current bunch Number
    auto curBunchText = std::to_string(curBunch);
    curBunchLabel = Label::createWithBMFont(fontsPath, curBunchText);
    curBunchLabel->setPosition(spriteToolSize.width / 8 * 3,
                               spriteToolSize.height / 2);
    spriteTool->addChild(curBunchLabel);
    
    //Add back button
    auto backNormal = Sprite::createWithSpriteFrameName("playbutton1.png");
    auto backPressed = Sprite::createWithSpriteFrameName("playbutton2.png");
    auto menuItem = MenuItemSprite::create(backNormal, backPressed, CC_CALLBACK_1(PlayScene::backCallback, this));
    menuItem->setPosition(winSize.width - menuItem->getContentSize().width / 2, winSize.height - menuItem->getContentSize().height / 2);
    menuItem->setTag(MenuTag::BACK_TAG);
    
    //Add pause button
    auto pauseItem = MenuItemImage::create("pause.png", "pause.png");
    //pauseItem->setPosition(pauseItem->getContentSize().width / 2, winSize.height - pauseItem->getContentSize().height / 2);
    auto startItem = MenuItemImage::create("start.png", "start.png");
    auto menuToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(PlayScene::menuStartOrPauseCallBack, this), pauseItem, startItem, NULL);
    menuToggle->setScale(0.15f);
    auto boundingBox = menuToggle->getBoundingBox();
    menuToggle->setPosition(boundingBox.size.width / 2, winSize.height - boundingBox.size.height / 2 + 15);
    
    //Add setting button
    auto settingItem = MenuItemImage::create("SettingButton.png", "SettingButton.png", CC_CALLBACK_1(PlayScene::menuSettingCallBack, this));
    settingItem->setPosition(winSize.width - boundingBox.size.width / 2, menuItem->getPositionY() - menuItem->getContentSize().height);
    settingItem->setScale(0.15f);
    settingItem->setTag(MenuTag::SETTING_TAG);
    auto menu = Menu::create(menuItem, menuToggle, settingItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
}

void PlayScene::backCallback(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
    auto levelScene = LevelScene::createScene();
    auto transitionFade = TransitionFade::create(0.2, levelScene);
    Director::getInstance()->replaceScene(transitionFade);
}

bool PlayScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto touchPos = touch->getLocation();
    //log("touch Pos: %f, %f", touchPos.x, touchPos.y);
    auto tilePos = convertToTileCoord(touchPos);
    tileIDX = tilePos.x;
    tileIDY = tilePos.y;
    //Get tile size
    auto tileX = map->getContentSize().width / map->getMapSize().width;
    auto tileY = map->getContentSize().height / map->getMapSize().height;
    
    auto posX = tileX * tilePos.x + tileX / 2;
    auto posY = tileY * (map->getMapSize().height - 1 - tilePos.y) + tileY / 2;
    if(canAddTower(touchPos))
    {
        //Get tile index
        towerPosition = Vec2(posX, posY);
        auto towerPanelLayer = TowerPanelLayer::create();
        towerPanelLayer->setPosition(posX, posY);
        this->addChild(towerPanelLayer);
    }
    else
        warning("no.png", Vec2(posX, posY));
    
    return false;
}

bool PlayScene::canAddTower(const cocos2d::Vec2 &position)
{
    auto tilePos = convertToTileCoord(position);
    //log("tile ID: %f, %f", tilePos.x, tilePos.y);
    auto gid = tmxLayer->getTileGIDAt(tilePos);
    auto tileProperty = map->getPropertiesForGID(gid).asValueMap();
    //log("tileProperty type : %d", t.getType());
    
    int tileValue = 0;
    if(tileProperty.empty())
    {
        tileValue = 1;
        log("tileProperty empty");
    }
    else
    {
        tileValue = tileProperty.at("canTouch").asInt();
    }
    if(towerVec[static_cast<int>(tilePos.x)].at(tilePos.y) == false && tileValue == 1)
        return true;
    return false;
}

Vec2 PlayScene::convertToTileCoord(const cocos2d::Vec2 &position)
{
    auto winSize = Director::getInstance()->getWinSize();
    float tileSizeX = map->getContentSize().width / map->getMapSize().width;
    float tileSizeY = map->getContentSize().height / map->getMapSize().height;
    int x = position.x / tileSizeX;
    int y = (winSize.height - position.y) / tileSizeY;
    
    //In case towerVec out of range
    if(x >= TILE_NUMBER_X)
        x = TILE_NUMBER_X - 1;
    if(y >= TILE_NUMBER_Y)
        y = TILE_NUMBER_Y - 1;
    return Vec2(x, y);
}

void PlayScene::setMoneyLabel(cocos2d::EventCustom *custom)
{
    auto enemyValue = *static_cast<float*>(custom->getUserData());
//    if(!enemy)
//        return;
    money += enemyValue;
    moneyLabel->setString(std::to_string(money));
}

void PlayScene::addTower(cocos2d::EventCustom *event)
{
    towerType = *static_cast<TOWERTYPE*>(event->getUserData());
    bool moneyNotEnough = true;
    switch (towerType) {
        case TOWERTYPE::ARROW_TOWER:
        {
            if(money >= ARROW_COST)
            {
                auto tower = ArrowTower::create();
                tower->setPosition(towerPosition);
                this->addChild(tower);
                money -= ARROW_COST;
                this->moneyLabel->setString(std::to_string(money));
                towerVec[tileIDX][tileIDY] = true;
                moneyNotEnough = false;
            }
            break;
        }
        case TOWERTYPE::ATTACK_TOWER:
        {
            if(money >= ATTACK_COST)
            {
                auto tower = AttackTower::create();
                tower->setPosition(towerPosition);
                this->addChild(tower);
                money -= ATTACK_COST;
                this->moneyLabel->setString(std::to_string(money));
                towerVec[tileIDX][tileIDY] = true;
                moneyNotEnough = false;
            }
            break;
        }
        case TOWERTYPE::MULTIIDR_TOWER:
        {
            if(money >= MULTIDIR_COST)
            {
                auto tower = MultiDirTower::create(6);
                tower->setPosition(towerPosition);
                this->addChild(tower);
                money -= MULTIDIR_COST;
                this->moneyLabel->setString(std::to_string(money));
                towerVec[tileIDX][tileIDY] = true;
                moneyNotEnough = false;
            }
            break;
        }
        default:
            log("TowerType Other");
            moneyNotEnough = false;
            break;
    }
    if(moneyNotEnough)
    {
        //log("money rest: %d", money);
        warning("nomoney_mark.png", towerPosition);
    }
}

void PlayScene::warning(const std::string &fileName, const Vec2 &position)
{
    //log("warning: %s", fileName.c_str());
    SimpleAudioEngine::getInstance()->playEffect("sound/tip.wav", false);
    auto tips = Sprite::createWithSpriteFrameName(fileName);
    tips->setPosition(position);
    this->addChild(tips);
    tips->runAction(Sequence::create(DelayTime::create(0.5f),
                                     CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)), NULL));
}
