//
//  LogicalEngine.cpp
//  dice
//
//  Created by Hetty on 14-8-10.
//
//

#include "LogicalEngine.h"

LogicalEngine* LogicalEngine::sInstance = nullptr;

LogicalEngine * LogicalEngine::getInstance() {
  if (!sInstance) {
      sInstance = new LogicalEngine();
  }

  return sInstance;
}

LogicalEngine::LogicalEngine()
: mStatus(LOADING) {

}

LogicalEngine::GameStatus LogicalEngine::getStatus() {
  return mStatus;
}

void LogicalEngine::setStatus(GameStatus status) {
  mStatus = status;
}

void LogicalEngine::switchTo(SceneCreater::SceneType sceneType) {
  DiceScene * next = SceneCreater::getInstance()->getScence(sceneType);
  if (next) {
    setCurrentScene(next, sceneType);
    Director* direct = Director::getInstance();
    direct->replaceScene(next);
    log("switch to scene:%s", SceneCreater::getInstance()->sceneName(sceneType));
  }
  else {
    log("Could not switch to scene:%s", SceneCreater::getInstance()->sceneName(sceneType));
  }
}

SceneCreater::SceneType LogicalEngine::currentScene() {
  return mCurrentSceneType;
}

void LogicalEngine::setCurrentScene(DiceScene* scene, SceneCreater::SceneType sceneType) {
  if (mCurrentScene) {
      mCurrentScene->release();
  }

  mCurrentScene = scene;
  if (mCurrentScene) {
      mCurrentScene->retain();
  }
  mCurrentSceneType = sceneType;
}
