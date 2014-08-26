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

class NetEngineHandler {
public:
    //Request response
    virtual void onLoginRsp(const ResponseBase& rsp) = 0;
    virtual void onGetAuthKeyRsp(const ResponseBase& rsp) = 0;
    virtual void onRegisterUserRsp(const ResponseBase& rsp) = 0;
    virtual void onCreateRoomRsp(const ResponseBase& rsp) = 0;
    virtual void onJoinRoomRsp(const ResponseBase& rsp) = 0;
    virtual void onSendDiceNumRsp(const ResponseBase& rsp) = 0;
    virtual void onStartRsp(const ResponseBase& rsp) = 0;
    virtual void onPunishFinishedRsp(const ResponseBase& rsp) = 0;

    //Event
    virtual void onStartRollDice() = 0;
    virtual void onPlayerJoined(const string& name) = 0;
    virtual void onPlayerLeft(const string& name) = 0;
    virtual void onPlayerDiceNum(const string& name, int num) = 0;
    virtual void onPunishPlayer(const string& name, const string& punish) = 0;
    virtual void onGameFinished() = 0;
};

class NetEngine : public Ref{
public:
    static NetEngine* getInstance();
    
    void setHandler(NetEngineHandler* handler);
    NetEngineHandler* getHandler();
    
    void disconnectServer();
    bool connectServer();
    void setServerAddr(const string& ip, int port);
    void getServerAddr(string& ip, int& port);

private:
    NetEngine();
    bool init();
    static void onRequestResult(pc_request_t* req, int status, json_t *resp);
    static void onEvent(pc_client_t *client, const char *event, void *data);
    
private:
    NetEngineHandler *mHandler;
    pc_client_t *mClient;
    string mConnectIp;
    int mConnectPort;
};

#endif /* defined(__dice__NetEngine__) */
