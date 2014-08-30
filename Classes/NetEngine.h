//
//  NetEngine.h
//  dice
//
//  Created by Hetty on 14-8-10.
//
//

#ifndef __dice__NetEngine__
#define __dice__NetEngine__

#include <iostream>

#include "CCRef.h"
#include "pomelo.h"
#include "Player.h"

using namespace std;

USING_NS_CC;

enum ResponseCode {
    RSP_OK,
    RSP_FAIL
};

class ResponseBase {
public:
    ResponseCode result;
    string resultString;
};

class JoinRoomRsp : public ResponseBase {
public:
    string owner;
    vector<Player> players;
};

class GetPunishSettingRsp : public ResponseBase {
public:
    int catId;
    int typeId;
};

class NetEngineHandler {
public:
    //Request response
    virtual void onCanRegisterRsp(const ResponseBase& rsp) = 0;
    virtual void onLoginRsp(const ResponseBase& rsp) = 0;
    virtual void onGetAuthKeyRsp(const ResponseBase& rsp) = 0;
    virtual void onRegisterUserRsp(const ResponseBase& rsp) = 0;
    virtual void onCreateRoomRsp(const ResponseBase& rsp) = 0;
    virtual void onJoinRoomRsp(const JoinRoomRsp& rsp) = 0;
    virtual void onLeaveRoomRsp(const ResponseBase& rsp) = 0;
    virtual void onSendDiceNumRsp(const ResponseBase& rsp) = 0;
    virtual void onStartRsp(const ResponseBase& rsp) = 0;
    virtual void onPunishFinishedRsp(const ResponseBase& rsp) = 0;
    virtual void onGetPunishSettingRsp(const GetPunishSettingRsp& rsp) = 0;
    virtual void onSetPunishSettingRsp(const ResponseBase& rsp) = 0;

    //Event
    virtual void onDisconnected() = 0;
    virtual void onTimeout() = 0;
    virtual void onStartRollDice() = 0;
    virtual void onPlayerJoined(const Player& player) = 0;
    virtual void onPlayerLeft(const string& name) = 0;
    virtual void onPlayerDiceNum(const string& name, int num) = 0;
    virtual void onPunishSetting(int catId, int typeId) = 0;
    virtual void onPunishPlayer(const string& name, const string& punishment) = 0;
    virtual void onGameFinished() = 0;
};

class NetEngine : public Ref{
public:
    static NetEngine* getInstance();
    
    void setHandler(NetEngineHandler* handler);
    NetEngineHandler* getHandler();

    void canRegister(const string& name, const string& phone);
    void login(const string& name, const string& passwd);
    void getAuthKey(const string& name, const string& phone);
    void registerUser(const string& name, const string& passwd,
                      const string& phone, int imageId, const string& authKey);
    void createRoom(const string& name, int roomId, const string& pwd);
    void getPunishSetting(const string& name, int roomId);
    void setPunishSetting(const string& name, int roomId, int punishCat, int punishType);
    void joinRoom(const string& name, int roomId, const string& pwd);
    void leaveRoom(const string& name, int roomId);
    void sendDiceNum(const string& name, int roomId, int num);
    void startGame(const string& name, int roomId);
    void punishFinished(const string& name, int roomId);

private:
    NetEngine();
    
    /**
     * Send request to server
     * @param route The API route, see Constants.h
     * @param msg The JSON object. This msg is freed automatically, the caller can't release it.
     */
    void sendRequest(const string& route, json_t *msg);
    
    bool isConnected();
    void disconnectServer();
    bool connectServer();
    void setServerAddr(const string& ip, int port);
    void getServerAddr(string& ip, int& port);
    bool init();
    static void onRequestResult(pc_request_t* req, int status, json_t *resp);
    static void onEvent(pc_client_t *client, const char *event, void *data);
    
    void setResponseField(ResponseBase& rsp, int status, json_t *resp);
    
private:
    NetEngineHandler *mHandler;
    pc_client_t *mClient;
    string mConnectIp;
    int mConnectPort;
    static NetEngine* sInstance;
};

#endif /* defined(__dice__NetEngine__) */
