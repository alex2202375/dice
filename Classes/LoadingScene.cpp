//
//  LoadingScene.cpp
//  dice
//
//  Created by Hetty on 14-8-9.
//
//

#include "LoadingScene.h"
#include "InitBackgroundLayer.h"
#include "LoginScene.h"
#include "CCDirector.h"
#include "SceneCreater.h"
#include "LogicalEngine.h"

LoadingScene::LoadingScene() {

}

LoadingScene::~LoadingScene() {

}

void LoadingScene::nextScene(float delta) {
    LogicalEngine::getInstance()->switchTo(SceneCreater::SCENE_LOGIN);
}

void LoadingScene::onEnter() {
    DiceScene::onEnter();
    auto backLayer = InitBackgroundLayer::create();
    addChild(backLayer);
    schedule(schedule_selector(LoadingScene::nextScene), 1, kRepeatForever, 0);
}

GameStatus LoadingScene::initStatus() {
  return LOADING;
}
