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
    list<Player> players;
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
    virtual void onSendDiceNumRsp(const ResponseBase& rsp) = 0;
    virtual void onStartRsp(const ResponseBase& rsp) = 0;
    virtual void onPunishFinishedRsp(const ResponseBase& rsp) = 0;

    //Event
    virtual void onStartRollDice() = 0;
    virtual void onPlayerJoined(const string& name, int picId) = 0;
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
    
    /**
     * Send request to server
     * @param route The API route, see Constants.h
     * @param msg The JSON object. This msg is freed automatically, the caller can't release it.
     */
    void sendRequest(const string& route, json_t *msg);
    
    void disconnectServer();
    bool connectServer();
    void setServerAddr(const string& ip, int port);
    void getServerAddr(string& ip, int& port);

private:
    NetEngine();
    bool init();
    static void onRequestResult(pc_request_t* req, int status, json_t *resp);
    static void onEvent(pc_client_t *client, const char *event, void *data);
    
    void setResponseField(ResponseBase& rsp, int status, json_t *resp);
    
private:
    NetEngineHandler *mHandler;
    pc_client_t *mClient;
    string mConnectIp;
    int mConnectPort;
};

#endif /* defined(__dice__NetEngine__) */
