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

LogicalEngine::GameStatus GameScene::initStatus() {
  return LogicalEngine::ROOM_SELECTING;
}
