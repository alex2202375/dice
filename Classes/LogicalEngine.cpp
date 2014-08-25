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
: mStatus(LOADING), mCurrentScene(nullptr), mNetEngine(nullptr) {
    mNetEngine = NetEngine::getInstance();
    mNetEngine->setHandler(this);
}

LogicalEngine::~LogicalEngine() {
    
}

GameStatus LogicalEngine::getStatus() {
  return mStatus;
}

void LogicalEngine::setStatus(GameStatus status) {
  mStatus = status;
}

void LogicalEngine::switchTo(SceneCreater::SceneType sceneType) {
  DiceScene * next = SceneCreater::getInstance()->getScene(sceneType);
  if (next) {
    setCurrentScene(next, sceneType);
    Director* direct = Director::getInstance();
    direct->replaceScene(next);
    log("switch to scene:%s", SceneCreater::getInstance()->sceneName(sceneType).c_str());
  }
  else {
    log("Could not switch to scene:%s", SceneCreater::getInstance()->sceneName(sceneType).c_str());
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

void LogicalEngine::getLastLoginInfo(string& name, string& password) {
    
}

void LogicalEngine::login(const string& name, const string& password, bool rememberInfo) {
    
}

void LogicalEngine::onLoginRsp() {
    
}

void LogicalEngine::getAuthKey(const string& phone) {
    
}

void LogicalEngine::onGetAuthKeyRsp(bool rsp) {
    
}

void LogicalEngine::registerUser(const string& name, const string& password,
                                 const string& phone, const string& authKey) {
    
}

void LogicalEngine::onRegisterUserRsp() {
    
}

void LogicalEngine::createRoom(){
}

void LogicalEngine::onCreateRoomRsp() {
    
}

void LogicalEngine::joinRoom() {
    
}

void LogicalEngine::onJoinRoomRsp() {
    
}

void LogicalEngine::sendDiceNum(int number) {
    
}

void LogicalEngine::onSendDiceNumRsp() {
    
}


/**
 * Notification from server
 */
void LogicalEngine::onStartRollDice() {
    
}

void LogicalEngine::onUserJoined() {
    
}

void LogicalEngine::onUserLeft() {
    
}

void LogicalEngine::onPunishUser() {
    
}

void LogicalEngine::onGameFinished() {
    
}

