//
//  LogicalEngine.h
//  dice
//
//  Created by Hetty on 14-8-10.
//
//

#ifndef __dice__LogicalEngine__
#define __dice__LogicalEngine__

#include <iostream>
#include <list>
#include "CCRef.h"
#include "DiceScene.h"
#include "SceneCreater.h"
#include "Constants.h"
#include "NetEngine.h"

using namespace std;
USING_NS_CC;

class LogicalEngine : public Ref, NetEngineHandler{
public:
    static LogicalEngine * getInstance();
    
    /**
     * Send to server
     */
    void getLastLoginInfo(string& name, string& password);
    void canRegister(const string& name, const string& phone);
    void login(const string& name, const string& password, bool rememberInfo);
    void getAuthKey(const string& phone);
    void registerUser(const string& name, const string& password,
                      const string& phone, const string& authKey);
    void createRoom();
    void joinRoom();
    void sendDiceNum(int number);
    
    virtual void onCanRegisterRsp(const ResponseBase& rsp);
    virtual void onLoginRsp(const ResponseBase& rsp);
    virtual void onGetAuthKeyRsp(const ResponseBase& rsp);
    virtual void onRegisterUserRsp(const ResponseBase& rsp);
    virtual void onCreateRoomRsp(const ResponseBase& rsp);
    virtual void onJoinRoomRsp(const JoinRoomRsp& rsp);
    virtual void onSendDiceNumRsp(const ResponseBase& rsp);
    virtual void onStartRsp(const ResponseBase& rsp);
    virtual void onPunishFinishedRsp(const ResponseBase& rsp);

    /**
     * Notification from server
     */
    //Event
    virtual void onStartRollDice();
    virtual void onPlayerJoined(const Player& player);
    virtual void onPlayerLeft(const string& name);
    virtual void onPlayerDiceNum(const string& name, int num);
    virtual void onPunishPlayer(const string& name, const string& punish);
    virtual void onGameFinished();
    
    /**
     * Utilities
     */
    GameStatus getStatus();
    void setStatus(GameStatus status);

    void switchTo(SceneCreater::SceneType sceneType);\
    SceneCreater::SceneType currentScene();

    virtual ~LogicalEngine();
private:
    LogicalEngine();
    void setCurrentScene(DiceScene* scene, SceneCreater::SceneType sceneType);

private:
    GameStatus mStatus;
    DiceScene* mCurrentScene;
    SceneCreater::SceneType mCurrentSceneType;
    NetEngine* mNetEngine;
    
    static LogicalEngine* sInstance;
};

#endif /* defined(__dice__LogicalEngine__) */
