#include "AppDelegate.h"
#include "LoadingScene.hpp"
#include "SettingScene.hpp"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Brave C++ version");
        director->setOpenGLView(glview);
    }

    glview->setDesignResolutionSize(480, 320, ResolutionPolicy::FIXED_HEIGHT);
    director->setContentScaleFactor(864 / 320.0);
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    //Add search path
    std::vector<std::string> searchPath;
    searchPath.push_back("height_864");
    FileUtils::getInstance()->setSearchPaths(searchPath);

    // create a scene. it's an autorelease object
    auto scene = LoadingScene::createScene();
//    auto scene = SettingScene::createScene();
    director->runWithScene(scene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}
