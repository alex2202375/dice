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

LoginScene::LoginScene() {

}

LoginScene::~LoginScene() {

}

void LoginScene::onEnter() {
    DiceScene::onEnter();
    auto backLayer = InitBackgroundLayer::create();
    addChild(backLayer);
    auto loginLayer = LoginLayer::create();
    addChild(loginLayer, 1);
}

GameStatus LoginScene::initStatus() {
  return LOGINING;
}
