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
      sInstance->retain();
  }

  return sInstance;
}

LogicalEngine::LogicalEngine()
: mStatus(LOADING), mCurrentScene(nullptr),
  mCurrentSceneType(SceneCreater::SCENE_LOAD),
  mNetEngine(nullptr) {
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
    mNetEngine->sendRequest()
}


void LogicalEngine::getAuthKey(const string& phone) {
    
}



void LogicalEngine::registerUser(const string& name, const string& password,
                                 const string& phone, const string& authKey) {
    
}


void LogicalEngine::createRoom(){
}



void LogicalEngine::joinRoom() {
    
}


void LogicalEngine::sendDiceNum(int number) {
    
}

/**
 * Send to server
 */
void LogicalEngine::onCanRegisterRsp(const ResponseBase& rsp)  {
}

void LogicalEngine::onLoginRsp(const ResponseBase& rsp)  {
}
    
void LogicalEngine::onGetAuthKeyRsp(const ResponseBase& rsp)  {
}
    
void LogicalEngine::onRegisterUserRsp(const ResponseBase& rsp)  {
}
    
void LogicalEngine::onCreateRoomRsp(const ResponseBase& rsp)  {
}
    
void LogicalEngine::onJoinRoomRsp(const JoinRoomRsp& rsp)  {
}
    
void LogicalEngine::onSendDiceNumRsp(const ResponseBase& rsp)  {
}
    
void LogicalEngine::onStartRsp(const ResponseBase& rsp)  {
}
    
void LogicalEngine::onPunishFinishedRsp(const ResponseBase& rsp)  {
}

/**
 * Notification from server
 */
//Event
void LogicalEngine::onStartRollDice()  {
}

void LogicalEngine::onPlayerJoined(const Player& player)  {
}
    
void LogicalEngine::onPlayerLeft(const string& name)  {
}
    
void LogicalEngine::onPlayerDiceNum(const string& name, int num)  {
}
    
void LogicalEngine::onPunishPlayer(const string& name, const string& punish)  {
}
    
void LogicalEngine::onGameFinished()  {
}
    

