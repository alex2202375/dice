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

void LoadingScene::nextScene(float delta) {
    Scene * next = LoginScene::create();
    Director* direct = Director::getInstance();
    direct->replaceScene(next);
    log("next scene");
}

void LoadingScene::onEnter() {
    Scene::onEnter();
    auto backLayer = InitBackgroundLayer::create();
    addChild(backLayer);
    schedule(schedule_selector(LoadingScene::nextScene), 1, kRepeatForever, 0);
}