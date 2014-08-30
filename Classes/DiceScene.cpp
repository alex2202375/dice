/*
 * DiceScene.cpp
 *
 *  Created on: Aug 25, 2014
 *      Author: root
 */

#include "DiceScene.h"
#include "LogicalEngine.h"
#include "CCSprite.h"
#include "CCLabel.h"
#include "CCActionInterval.h"
#include "ccTypes.h"
#include "CommonUtil.h"

DiceScene::DiceScene():
mNotifyDialog(nullptr), mNotifyLabel(nullptr)
{
}

DiceScene::~DiceScene()
{
    CommonUtil::releaseRef(mNotifyDialog);
    CommonUtil::releaseRef(mNotifyLabel);
}

bool DiceScene::init() {
    if (!Scene::init()) {
        return false;
    }
    
    LogicalEngine* engine = LogicalEngine::getInstance();
    engine->setStatus(initStatus());
    
    scheduleUpdate();
    return true;
}

static pthread_mutex_t sceneMutex = PTHREAD_MUTEX_INITIALIZER;

void DiceScene::update(float delta) {
    Scene::update(delta);
//    pthread_mutex_lock(&sceneMutex);
    if (mCallBackList.size()) {
        SEL_CallFunc cb = mCallBackList.at(0);
        mCallBackList.erase(mCallBackList.begin());
        (this->*cb)();
    }
//    pthread_mutex_unlock(&sceneMutex);
    
}

void DiceScene::callInMainThread(SEL_CallFunc cb){
//    pthread_mutex_lock(&sceneMutex);
    mCallBackList.push_back(cb);
//    pthread_mutex_unlock(&sceneMutex);
}

void DiceScene::switchTo(SceneCreater::SceneType type) {
    mNextScene = type;
    callInMainThread(callfunc_selector(DiceScene::_swithTo));
}

void DiceScene::_swithTo() {
    LogicalEngine::getInstance()->switchTo(mNextScene);
}

void DiceScene::switchToHandler(EventCustom* event) {
    SceneCreater::SceneType * to = static_cast<SceneCreater::SceneType *>(event->getUserData());
    LogicalEngine::getInstance()->switchTo(*to);
    delete to;
}

void DiceScene::setStatus(GameStatus status)
{
    LogicalEngine* engine = LogicalEngine::getInstance();
    engine->setStatus(status);
}

void DiceScene::_showNotifyDialog() {
    if (!mNotifyDialog) {
        auto bg = Sprite::create(NotifyBgImg);
        Size visibleSize = Director::getInstance()->getVisibleSize();
        mNotifyLabel = Label::create(mNotifyMessage, NotifyFontName, NotifyFontSize);
        mNotifyLabel->setTextColor(Color4B::BLACK);
        mNotifyLabel->setPosition(Vec2(bg->getContentSize().width/2, bg->getContentSize().height/2));
        mNotifyLabel->retain();
        bg->addChild(mNotifyLabel);
        bg->setPosition(Vec2(visibleSize.width/2, bg->getContentSize().height));
        bg->retain();
        mNotifyDialog = bg;
        addChild(mNotifyDialog, 3);
    }
    
    mNotifyLabel->setString(mNotifyMessage);
    mNotifyDialog->setVisible(true);
    mNotifyDialog->setScale(0);
    auto action = ScaleTo::create(NotifyShowHideDuration, 1);
    mNotifyDialog->runAction(action);
    if (mNotifyCloseDelay > 0) {
        scheduleOnce(schedule_selector(DiceScene::hideNotifyDialog), mNotifyCloseDelay);
    }
}

void DiceScene::showNotifyDialog(const string& content, int closeDelay)
{
    mNotifyMessage = content;
    mNotifyCloseDelay = closeDelay;
    callInMainThread(callfunc_selector(DiceScene::_showNotifyDialog));
}

void DiceScene::hideNotifyDialog(float delta) {
    if (mNotifyDialog && mNotifyDialog->isVisible()) {
        mNotifyDialog->stopAllActions();
        auto hideAction = Hide::create();
        auto scaleAction = ScaleTo::create(NotifyShowHideDuration, 0);
        auto action = Sequence::create(scaleAction, hideAction, NULL);
        mNotifyDialog->runAction(action);
    }
}
