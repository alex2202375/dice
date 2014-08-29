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

  return true;
}

void DiceScene::setStatus(GameStatus status)
{
  LogicalEngine* engine = LogicalEngine::getInstance();
  engine->setStatus(status);
}

void DiceScene::showNotifyDialog(const string& content, int closeDelay)
{
    if (!mNotifyDialog) {
        auto bg = Sprite::create(NotifyBgImg);
        Size visibleSize = Director::getInstance()->getVisibleSize();
        mNotifyLabel = Label::create(content, NotifyFontName, NotifyFontSize);
        mNotifyLabel->setPosition(Vec2(bg->getContentSize().width/2, bg->getContentSize().height/2));
        mNotifyLabel->retain();
        bg->addChild(mNotifyLabel);
        bg->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
        bg->retain();
        mNotifyDialog = bg;
        addChild(mNotifyDialog);
    }

    mNotifyLabel->setString(content);
    mNotifyDialog->setVisible(true);
    mNotifyDialog->setScale(0);
    auto action = ScaleTo::create(NotifyShowHideDuration, 1);
    mNotifyDialog->runAction(action);
    if (closeDelay > 0) {
        scheduleOnce(schedule_selector(DiceScene::hideNotifyDialog), closeDelay);
    }
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
