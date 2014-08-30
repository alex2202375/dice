//
//  LogicalEngine.cpp
//  dice
//
//  Created by Hetty on 14-8-10.
//
//

#include "LogicalEngine.h"
#include "GameScene.h"


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
      mPunishCatId = PunishCatSmall;
      mPunishTypeId = PunishTypeBuy;
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
    mAuthCode = authKey;
    mNetEngine->registerUser(name, password, phone, picId, authKey);
}

void LogicalEngine::createRoom(int roomId, const string& pwd){
    mRoomId = roomId;
    
    mNetEngine->createRoom(mPlayerName, roomId, pwd);
}

void LogicalEngine::joinRoom(int roomId, const string& pwd) {
    mRoomId = roomId;
    
    mNetEngine->joinRoom(mPlayerName, roomId, pwd);
}

void LogicalEngine::leaveRoom() {
    mNetEngine->leaveRoom(mPlayerName, mRoomId);
}

void LogicalEngine::startGame() {
    mNetEngine->startGame(mPlayerName, mRoomId);
}


void LogicalEngine::sendDiceNum(int number) {
    mNetEngine->sendDiceNum(mPlayerName, mRoomId, number);
}

void LogicalEngine::punishFinished() {
    mNetEngine->punishFinished(mPlayerName, mRoomId);
}

void LogicalEngine::getPunishSetting() {
    mNetEngine->getPunishSetting(mPlayerName, mRoomId);
}

void LogicalEngine::setPunishSetting(PunishCat punishCat, PunishType punishType) {
    mPunishCatId = punishCat;
    mPunishTypeId = punishType;
    mNetEngine->setPunishSetting(mPlayerName, mRoomId, mPunishCatId, mPunishTypeId);
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
    
    mCurrentScene->switchTo(SceneCreater::SCENE_GAME);
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
    
    mIsRoomOwner = true;
    mPlayerList.clear();
    if (mCurrentSceneType == SceneCreater::SCENE_GAME) {
        GameScene* game = (GameScene*)mCurrentScene;
        game->callInMainThread(callfunc_selector(GameScene::enterredRoom));
    }
}

void LogicalEngine::onJoinRoomRsp(const JoinRoomRsp& rsp)  {
    CHECK_RSP(rsp);
    
    mNetEngine->getPunishSetting(mPlayerName, mRoomId);
    mIsRoomOwner = false;
    mPlayerList = rsp.players;
    if (mCurrentSceneType == SceneCreater::SCENE_GAME) {
        GameScene* game = (GameScene*)mCurrentScene;
        game->callInMainThread(callfunc_selector(GameScene::enterredRoom));
    }
}

void LogicalEngine::onLeaveRoomRsp(const ResponseBase& rsp) {
    CHECK_RSP(rsp);
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
    mCurrentScene->showNotifyDialog(NetTimeOut);
}

void LogicalEngine::onStartRollDice()  {
    if (mCurrentSceneType == SceneCreater::SCENE_GAME) {
        GameScene* game = (GameScene*)mCurrentScene;
        game->callInMainThread(callfunc_selector(GameScene::rollDice));
    }
}

void LogicalEngine::onPlayerJoined(const Player& player)  {
    if (mCurrentSceneType == SceneCreater::SCENE_GAME) {
        mPlayerList.push_back(player);
        GameScene* game = (GameScene*)mCurrentScene;
        game->callInMainThread(callfunc_selector(GameScene::updatePlayerList));
    }
}
    
void LogicalEngine::onPlayerLeft(const string& name)  {
    if (mCurrentSceneType == SceneCreater::SCENE_GAME) {
        bool found = false;
        for (vector<Player>::iterator i = mPlayerList.begin(); i != mPlayerList.end(); i++) {
            if ((*i).name == name) {
                mPlayerList.erase(i);
                found = true;
                break;
            }
        }
        if (found) {
            GameScene* game = (GameScene*)mCurrentScene;
            game->callInMainThread(callfunc_selector(GameScene::updatePlayerList));
        }
    }
}

void LogicalEngine::onPunishSetting(int catId, int typeId) {
    mPunishCatId = (PunishCat)catId;
    mPunishTypeId = (PunishType)typeId;
    if (mCurrentSceneType == SceneCreater::SCENE_GAME) {
        GameScene* game = (GameScene*)mCurrentScene;
        game->callInMainThread(callfunc_selector(GameScene::updatePunishSettings));
    }
}
    
void LogicalEngine::onPlayerDiceNum(const string& name, int num)  {
    if (mCurrentSceneType == SceneCreater::SCENE_GAME) {
        bool found = false;
        for (vector<Player>::iterator i = mPlayerList.begin(); i != mPlayerList.end(); i++) {
            if ((*i).name == name) {
                (*i).diceNum = num;
                found = true;
                break;
            }
        }
        if (found) {
            GameScene* game = (GameScene*)mCurrentScene;
            game->callInMainThread(callfunc_selector(GameScene::updatePlayerList));
        }
    }
}
    
void LogicalEngine::onPunishPlayer(const string& name, const string& punish)  {
    if (mCurrentSceneType == SceneCreater::SCENE_GAME) {
        GameScene* game = (GameScene*)mCurrentScene;
        mPunishPlayerName = name;
        mPunishment = punish;
        game->callInMainThread(callfunc_selector(GameScene::showPunishment));
    }
}

void LogicalEngine::onGameFinished()  {
    if (mCurrentSceneType == SceneCreater::SCENE_GAME) {
        GameScene* game = (GameScene*)mCurrentScene;
        game->callInMainThread(callfunc_selector(GameScene::gameFinished));
    }
}

void LogicalEngine::getPlayerList(vector<Player> & playerList) {
    playerList.clear();
    playerList = mPlayerList;
}

void LogicalEngine::getPunishInfo(string& name, string& punishment) {
    name = mPunishPlayerName;
    punishment = mPunishment;
}

void LogicalEngine::getPunishSetting(PunishCat & cId, PunishType& pId) {
    cId = mPunishCatId;
    pId = mPunishTypeId;
}

