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
#include "Player.h"

using namespace std;
USING_NS_CC;

class LogicalEngine : public Ref, NetEngineHandler{
public:
    static LogicalEngine * getInstance();
    
    bool isRoomOwner();
    void setPlayerName(const string& name);
    string getPlayerName();
    
    void setPlayerPwd(const string& pwd);
    string getPlayerPwd();
    
    void setAuthCode(const string& code);
    string getAuthCode();
    
    void setPlayerPhone(const string& phone);
    string getPlayerPhone();
    
    int getPlayerPicId();
    void setPlayerPicId(int picId);
    
    /**
     * Send to server
     */
    void getLastLoginInfo(string& name, string& password);
    void canRegister(const string& name, const string& phone);
    void login(const string& name, const string& password, bool rememberInfo);
    void getAuthKey(const string& name, const string& phone);
    void registerUser(const string& name, const string& password,
                      const string& phone, int picId, const string& authKey);
    void createRoom(int roomId);
    void joinRoom(int roomId);
    void startGame();
    void sendDiceNum(int number);
    void getPunishSetting();
    void setPunishSetting(int punishCat, int punishType);
    
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
    virtual void onGetPunishSettingRsp(const GetPunishSettingRsp& rsp) override;
    virtual void onSetPunishSettingRsp(const ResponseBase& rsp) override;
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
    
    //Player info
    string mPlayerName;
    string mPlayerPwd;
    int mPlayerPicId;
    string mPlayerPhone;
    string mAuthCode;
    
    int mRoomId;
    int mPunishTypeId;
    int mPunishCatId;
    bool mIsRoomOwner;
    
    static LogicalEngine* sInstance;
    
};

#endif /* defined(__dice__LogicalEngine__) */
