/*
 * SceneCreater.cpp
 *
 *  Created on: Aug 25, 2014
 *      Author: root
 */

#include "SceneCreater.h"
#include "LoadingScene.h"
#include "GameScene.h"
#include "RegisterScene.h"
#include "LoginScene.h"
#include "HeadScene.h"

SceneCreater* SceneCreater::sInstance = nullptr;

SceneCreater::SceneCreater()
{
  // TODO Auto-generated constructor stub

}

SceneCreater::~SceneCreater()
{
  // TODO Auto-generated destructor stub
}


SceneCreater* SceneCreater::getInstance() {
  if (!sInstance) {
      sInstance = new SceneCreater();
  }
  return sInstance;
}

DiceScene* SceneCreater::getScene(SceneType type) {
    DiceScene * scene = nullptr;
    switch (type) {
        case SCENE_LOAD:
            scene = LoadingScene::create();
            break;
            
        case SCENE_REGISTER:
            scene = RegisterScene::create();
            break;
            
        case SCENE_PIC_SEL:
            scene = HeadScene::create();
            break;
            
        case SCENE_LOGIN:
            scene = LoginScene::create();
            break;
            
        case SCENE_GAME:
            scene = GameScene::create();
            break;
            
        default:
            break;
    }
    
    return scene;
}


string SceneCreater::sceneName(SceneType type) {
    string name("UnKnown_scence");
    switch (type) {
        case SCENE_LOAD:
            name = "SCENE_LOAD";
            break;
            
        case SCENE_REGISTER:
            name = "SCENE_REGISTER";
            break;
            
        case SCENE_LOGIN:
            name = "SCENE_LOGIN";
            break;
            
        case SCENE_PIC_SEL:
            name = "SCENE_PIC_SEL";
            break;
            
        case SCENE_GAME:
            name = "SCENE_GAME";
            break;
            
        default:
            name = "UnKnown_scence";
            break;
    }
    
    return name;
}
