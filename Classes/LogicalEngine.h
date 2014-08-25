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

using namespace std;
USING_NS_CC;

class LogicalEngine : public Ref{
public:
    static LogicalEngine * getInstance();
    enum GameStatus {
        //Load
        LOADING,

        //Login
        LOGINING,
        LOGIN_WAIT_RSP,
        LOGINED,
        
        //Register
        REGISTERING,
        REGISTER_WAIT_RSP,
        
        //Room create/join
        ROOM_SELECTING,
        ROOM_CREATING,
        ROOM_CREATE_WAIT_RSP,
        ROOM_CREATED,
        ROOM_JOINING,
        ROOM_JOIN_WAIT_RSP,
        ROOM_JOINED,
        
        //Game
        GAME_READY,
        GAME_START_WAIT_RSP,
        GAME_GENERATING_NUMBER,
        GAME_SENDING_NUMBER_WAIT_RSP,
        GAME_WAITING_RESULT,
        GAME_PUNISHING,
        GAME_FINISHED
    };
    
    /**
     * Send to server
     */
    void getLastLoginInfo(string& name, string& password);
    void login(const string& name, const string& password, bool rememberInfo);
    void onLoginRsp();
    
    void getAuthKey(const string& phone);
    void onGetAuthKeyRsp(bool rsp);
    
    void registerUser(const string& name, const string& password,
                      const string& phone, const string& authKey);
    void onRegisterUserRsp();
    
    void createRoom();
    void onCreateRoomRsp();

    void joinRoom();
    void onJoinRoomRsp();

    void sendDiceNum(int number);
    void onSendDiceNumRsp();


    /**
     * Notification from server
     */
    void onStartRollDice();
    void onUpdateRoomStatus();

    
    /**
     * Utilities
     */
    GameStatus getStatus();
    void setStatus(GameStatus status);

    void switchTo(SceneCreater::SceneType sceneType);\
    SceneCreater::SceneType currentScene();

    ~LogicalEngine();
private:
    LogicalEngine();
    void setCurrentScene(DiceScene* scene, SceneCreater::SceneType sceneType);

private:
    GameStatus mStatus;
    DiceScene* mCurrentScene;
    SceneCreater::SceneType mCurrentSceneType;

    static LogicalEngine* sInstance;
};

#endif /* defined(__dice__LogicalEngine__) */
