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
    
    /**
     * Responses handle
     */
    virtual void onCanRegisterRsp(const ResponseBase& rsp) override;
    virtual void onLoginRsp(const ResponseBase& rsp) override;
    virtual void onGetAuthKeyRsp(const ResponseBase& rsp) override;
    virtual void onRegisterUserRsp(const ResponseBase& rsp) override;
    virtual void onCreateRoomRsp(const ResponseBase& rsp) override;
    virtual void onJoinRoomRsp(const JoinRoomRsp& rsp) override;
    virtual void onSendDiceNumRsp(const ResponseBase& rsp) override;
    virtual void onStartRsp(const ResponseBase& rsp) override;
    virtual void onPunishFinishedRsp(const ResponseBase& rsp) override;

    /**
     * Notification from server
     */
    //Event
    virtual void onStartRollDice() override;
    virtual void onPlayerJoined(const Player& player) override;
    virtual void onPlayerLeft(const string& name) override;
    virtual void onPlayerDiceNum(const string& name, int num) override;
    virtual void onPunishPlayer(const string& name, const string& punish) override;
    virtual void onGameFinished() override;
    
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
