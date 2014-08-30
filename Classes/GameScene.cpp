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
#include "CommonUtil.h"

GameScene::~GameScene() {
    CommonUtil::releaseRef(mGameLayer);
}

GameScene::GameScene():mGameLayer(nullptr) {

}

bool GameScene::init() {
    if (!DiceScene::init()) {
        return false;
    }
    auto backLayer = GameBackgroundLayer::create();
    addChild(backLayer);
    mGameLayer = GameLayer::create();
    mGameLayer->retain();
    addChild(mGameLayer, 1);
    return true;
}

GameStatus GameScene::initStatus() {
  return ROOM_SELECTING;
}

void GameScene::enterredRoom() {
    mGameLayer->enterredRoom();
}

void GameScene::rollDice() {
    mGameLayer->rollDice();
}

void GameScene::showPunishment() {
    mGameLayer->showPunishment();
}

void GameScene::updatePunishSettings() {
    mGameLayer->updatePunishSettings();
}

void GameScene::updatePlayerList() {
    mGameLayer->updatePlayerList();
}

void GameScene::punishFinished() {
    mGameLayer->punishFinished();
}

void GameScene::gameFinished() {
    mGameLayer->gameFinished();
}