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

bool LogicalEngine::isRoomOwner() {
    return mIsRoomOwner;
}

void LogicalEngine::setPlayerName(const string& name) {
    mPlayerName = name;
}

string LogicalEngine::getPlayerName() {
    return mPlayerName;
}

void LogicalEngine::setPlayerPwd(const string& pwd) {
    mPlayerPwd = pwd;
}

string LogicalEngine::getPlayerPwd() {
    return mPlayerPwd;
}

void LogicalEngine::setAuthCode(const string& code) {
    mAuthCode = code;
}

string LogicalEngine::getAuthCode() {
    return mAuthCode;
}

void LogicalEngine::setPlayerPhone(const string& phone) {
    mPlayerPhone = phone;
}

string LogicalEngine::getPlayerPhone() {
    return mPlayerPhone;
}

int LogicalEngine::getPlayerPicId() {
    return mPlayerPicId;
}

void LogicalEngine::setPlayerPicId(int picId) {
    mPlayerPicId = picId;
}

LogicalEngine::LogicalEngine()
: mStatus(LOADING), mCurrentScene(nullptr),
  mCurrentSceneType(SceneCreater::SCENE_LOAD),
  mNetEngine(nullptr) {
      mPlayerName = "";
      mPlayerPwd = "";
      mPlayerPicId = 0;
      mPlayerPhone = "";
      mRoomId = -1;
      mIsRoomOwner = false;
      mNetEngine = NetEngine::getInstance();
      mNetEngine->setHandler(this);
      mPlayerPicId = -1;
      
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

void LogicalEngine::canRegister(const string& name, const string& phone) {
    mNetEngine->canRegister(name, phone);
}

void LogicalEngine::login(const string& name, const string& password, bool rememberInfo) {
    mNetEngine->login(name, password);
    mPlayerName = name;
    mPlayerPwd = password;
    
    if (rememberInfo) {
        //TODO need to store user info
    }
}

void LogicalEngine::getAuthKey(const string& name, const string& phone) {
    mNetEngine->getAuthKey(name, phone);
}

void LogicalEngine::registerUser(const string& name, const string& password,
                                 const string& phone, int picId, const string& authKey) {
    mPlayerName = name;
    mPlayerPwd = password;
    mPlayerPhone = phone;
    mPlayerPicId = picId;
    mNetEngine->registerUser(name, password, phone, picId, authKey);
}

void LogicalEngine::createRoom(int roomId){
    mRoomId = roomId;
    
    mNetEngine->createRoom(mPlayerName, roomId);
}

void LogicalEngine::joinRoom(int roomId) {
    mRoomId = roomId;
    
    mNetEngine->joinRoom(mPlayerName, roomId);
}

void LogicalEngine::startGame() {
    mNetEngine->startGame(mPlayerName, mRoomId);
}


void LogicalEngine::sendDiceNum(int number) {
    mNetEngine->sendDiceNum(mPlayerName, mRoomId, number);
}

#define CHECK_RSP(rsp) \
    if (rsp.result != RSP_OK) { \
        mCurrentScene->showNotifyDialog(rsp.resultString); \
        return;\
    }

/**
 * Send to server
 */
void LogicalEngine::onCanRegisterRsp(const ResponseBase& rsp)  {
    CHECK_RSP(rsp);
}

void LogicalEngine::onLoginRsp(const ResponseBase& rsp)  {
    CHECK_RSP(rsp);

    switchTo(SceneCreater::SCENE_GAME);
}

void LogicalEngine::onGetAuthKeyRsp(const ResponseBase& rsp)  {
    CHECK_RSP(rsp);
}

void LogicalEngine::onRegisterUserRsp(const ResponseBase& rsp)  {
    CHECK_RSP(rsp);
    
    login(mPlayerName, mPlayerPwd, true);
}

void LogicalEngine::onCreateRoomRsp(const ResponseBase& rsp)  {
    CHECK_RSP(rsp);
    
    //Send room setting
    //TODO need to get last settings
    mNetEngine->setPunishSetting(mPlayerName, mRoomId, mPunishCatId, mPunishTypeId);
    
}

void LogicalEngine::onJoinRoomRsp(const JoinRoomRsp& rsp)  {
    CHECK_RSP(rsp);
    
    mNetEngine->getPunishSetting(mPlayerName, mRoomId);
}

void LogicalEngine::onSendDiceNumRsp(const ResponseBase& rsp)  {
    CHECK_RSP(rsp);
}

void LogicalEngine::onStartRsp(const ResponseBase& rsp)  {
    CHECK_RSP(rsp);
}

void LogicalEngine::onPunishFinishedRsp(const ResponseBase& rsp)  {
    CHECK_RSP(rsp);
}

void LogicalEngine::onGetPunishSettingRsp(const GetPunishSettingRsp& rsp)  {
    CHECK_RSP(rsp);
}

void LogicalEngine::onSetPunishSettingRsp(const ResponseBase& rsp)  {
    CHECK_RSP(rsp);
}

/**
 * Notification from server
 */
//Event
void LogicalEngine::onDisconnected() {

}

void LogicalEngine::onTimeout() {

}

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


