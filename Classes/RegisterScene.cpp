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
    Scene::onEnter();
    auto reglayer = RegisterLayer::create();
    addChild(reglayer);

}