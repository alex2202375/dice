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

class NetEngineHandler {
public:
    virtual void onLoginRsp() = 0;
    virtual void onGetAuthKeyRsp(bool rsp) = 0;
    virtual void onRegisterUserRsp() = 0;
    virtual void onCreateRoomRsp() = 0;
    virtual void onJoinRoomRsp() = 0;
    virtual void onSendDiceNumRsp() = 0;
    virtual void onStartRollDice() = 0;
    virtual void onUserJoined() = 0;
    virtual void onUserLeft() = 0;
    virtual void onPunishUser() = 0;
    virtual void onGameFinished() = 0;
};

class NetEngine : public Ref{
public:
    static NetEngine* getInstance();
    
    void setHandler(NetEngineHandler* handler);
    NetEngineHandler* getHandler();
    
private:
    NetEngine();
    bool init();
    void onRequestResult(pc_request_t* req, int status, json_t *resp);
    void onEvent(pc_client_t *client, const char *event, void *data);
    
private:
    NetEngineHandler *mHandler;
};

#endif /* defined(__dice__NetEngine__) */
