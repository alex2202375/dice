#include "AppDelegate.h"
#include "LoadingScene.h"
#include "LoginScene.h"

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
        glview = GLView::create("Dice");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    auto screenSize = glview->getFrameSize();
    
    auto designSize = Size(640, 1136);
    
    auto fileUtils = FileUtils::getInstance();
    std::vector<std::string> searchPaths;
    Size resourceSize;
#if 0 //Enable following lines when has multiple resources
    if (screenSize.height > 1280)
    {
        resourceSize = Size(1080, 1920);
        searchPaths.push_back("xxh");
    }
    else
    {
        resourceSize = Size(720, 1280);
        searchPaths.push_back("xh");
    }
#else 
    resourceSize = Size(1080, 1920);
    searchPaths.push_back("xxh");
#endif
    
    director->setContentScaleFactor(resourceSize.width/designSize.width);
    fileUtils->setSearchPaths(searchPaths);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    // a bug in DirectX 11 level9-x on the device prevents ResolutionPolicy::NO_BORDER from working correctly
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);
#else
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::FIXED_WIDTH);
#endif

    // create a scene. it's an autorelease object
    auto scene = LoadingScene::create();
//    auto scene = LoginScene::create();
    // run
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
