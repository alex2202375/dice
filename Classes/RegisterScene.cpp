//
//  RegisterScene.cpp
//  dice
//
//  Created by Hetty on 14-8-9.
//
//

#include "RegisterScene.h"
#include "RegisterLayer.h"

void RegisterScene::onEnter() {
    DiceScene::onEnter();
    auto reglayer = RegisterLayer::create();
    addChild(reglayer);

}

LogicalEngine::GameStatus RegisterScene::initStatus() {
  return LogicalEngine::REGISTERING;
}
