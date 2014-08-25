//
//  headscene.cpp
//  dice
//
//  Created by sockyjam on 14-8-17.
//
//

#include "HeadScene.h"
#include "HeadLayer.h"

void HeadScene::onEnter() {
    DiceScene::onEnter();
    auto headlayer = HeadLayer::create();
    addChild(headlayer);
    
}

GameStatus HeadScene::initStatus() {
  return LOADING;
}
