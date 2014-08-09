//
//  LoginScene.cpp
//  dice
//
//  Created by Hetty on 14-8-9.
//
//

#include "LoginScene.h"
#include "InitBackgroundLayer.h"
#include "LoginLayer.h"

void LoginScene::onEnter() {
    Scene::onEnter();
    auto backLayer = InitBackgroundLayer::create();
    addChild(backLayer);
    auto loginLayer = LoginLayer::create();
    addChild(loginLayer, 1);
}