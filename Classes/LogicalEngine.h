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
    void login(const string& name, const string& password, bool rememberInfo);
    virtual void onLoginRsp();
    
    void getAuthKey(const string& phone);
    virtual void onGetAuthKeyRsp(bool rsp);
    
    void registerUser(const string& name, const string& password,
                      const string& phone, const string& authKey);
    virtual void onRegisterUserRsp();
    
    void createRoom();
    virtual void onCreateRoomRsp();

    void joinRoom();
    virtual void onJoinRoomRsp();

    void sendDiceNum(int number);
    virtual void onSendDiceNumRsp();


    /**
     * Notification from server
     */
    virtual void onStartRollDice();
    virtual void onUserJoined();
    virtual void onUserLeft();
    virtual void onPunishUser();
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
