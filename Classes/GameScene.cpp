//
//  GameScene.cpp
//  dice
//
//  Created by Hetty on 14-8-9.
//
//

#include "GameScene.h"
#include "GameBackgroundLayer.h"
#include "GameLayer.h"

GameScene::~GameScene() {

}

GameScene::GameScene() {

}

bool GameScene::init() {
    if (!DiceScene::init()) {
        return false;
    }
    auto backLayer = GameBackgroundLayer::create();
    addChild(backLayer);
    auto gameLayer = GameLayer::create();
    addChild(gameLayer, 1);
    return true;
}

GameStatus GameScene::initStatus() {
  return ROOM_SELECTING;
}
