//
//  NetEngine.cpp
//  dice
//
//  Created by Hetty on 14-8-10.
//
//

#include "NetEngine.h"

#include "pomelo.h"
#include "Constants.h"
#include "CommonUtil.h"

NetEngine* NetEngine::getInstance() {
    NetEngine * en = new NetEngine();
    if (en) {
        if (!en->init()) {
            en->release();
            return nullptr;
        }
        en->retain();
    }
    return en;
}

void NetEngine::disconnectServer() {
    if (mClient) {
        pc_client_disconnect(mClient);
    }
    mConnectIp = NetServerIp;
    mConnectPort = NetServerPort;
}

void NetEngine::setServerAddr(const string& ip, int port) {
    mConnectIp = ip;
    mConnectPort = port;
}

void NetEngine::getServerAddr(string& ip, int& port){
    ip = mConnectIp;
    port = mConnectPort;
}

bool NetEngine::connectServer() {
    struct sockaddr_in address;
    if (!mClient) {
        return false;
    }
    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_port = htons(mConnectPort);
    address.sin_addr.s_addr = inet_addr(mConnectIp.c_str());

    // try to connect to server.
    if (pc_client_connect(mClient, &address)) {
        log("Could not connect to server:%s:%d", mConnectIp.c_str(), mConnectPort);
        return false;
    }

    return true;
}

bool NetEngine::init() {
    mClient = pc_client_new();
    if (!mClient) {
        return false;
    }

    if (!connectServer()) {
        return false;
    }

    pc_add_listener(mClient, PC_EVENT_DISCONNECT, onEvent);
    pc_add_listener(mClient, PC_EVENT_TIMEOUT, onEvent);
    pc_add_listener(mClient, PC_EVENT_KICK, onEvent);
    pc_add_listener(mClient, NetEventRollDice.c_str(), onEvent);
    pc_add_listener(mClient, NetEventUserJoined.c_str(), onEvent);
    pc_add_listener(mClient, NetEventUserLeft.c_str(), onEvent);
    pc_add_listener(mClient, NetEventUserDiceNum.c_str(), onEvent);
    pc_add_listener(mClient, NetEventPunishPlayer.c_str(), onEvent);
    pc_add_listener(mClient, NetEventGameFinished.c_str(), onEvent);
    return true;
}

NetEngine::NetEngine(): mHandler(nullptr), mClient(nullptr),
                        mConnectIp(NetServerIp),
                        mConnectPort(NetServerPort) {

}

void NetEngine::setHandler(NetEngineHandler* handler) {
    mHandler = handler;
}

NetEngineHandler* NetEngine::getHandler() {
    return mHandler;
}

void NetEngine::setResponseField(ResponseBase& rsp, int status, json_t *resp) {
    json_t* resJson = json_object_get(resp, NetJsonResultKey.c_str());
    if (status == 0 && resJson && (json_integer_value(resJson) == NetJsonResultOk)) {
        rsp.result = RSP_OK;
    }
    else {
        rsp.result = RSP_FAIL;
        json_t* resStrJson = json_object_get(resp, NetJsonResultStrKey.c_str());
        if (resStrJson) {
            rsp.resultString = json_string_value(resStrJson);
        }
        else {
            rsp.resultString = NetJsonResultStrUnknown;
        }
    }
}

void NetEngine::onRequestResult(pc_request_t* req, int status, json_t *resp) {
    NetEngine* engine = NetEngine::getInstance();
    if (!engine->mHandler) {
        return;
    }
    string request = req->route;

    ResponseBase* rsp;
    if (request == NetReqJoinRoom) {
        rsp = new JoinRoomRsp();
    }
    else {
        rsp = new ResponseBase();
    }
    engine->setResponseField(*rsp, status, resp);
    

    if (request == NetReqLogin) {
        if (rsp->result == RSP_OK) {
            string ip;
            int port;
            CommonUtil::parseValue(resp, NetJsonLoginRspIpKey, ip, NetJsonLoginRspIpInvalid);
            CommonUtil::parseValue(resp, NetJsonLoginRspPortKey, port, NetJsonLoginRspPortInvalid);
            if (ip == NetJsonLoginRspIpInvalid || NetJsonLoginRspPortInvalid == port) {
                rsp->result = RSP_FAIL;
                rsp->resultString = NetJsonResultStrUnknown;
            }
            else {
                engine->disconnectServer();
                engine->setServerAddr(ip, port);
                if (!engine->connectServer()) {
                    rsp->result = RSP_FAIL;
                    rsp->resultString = NetJsonResultStrConnect;
                }
            }
        }
        engine->mHandler->onLoginRsp(*rsp);
    }
    else if (request == NetReqRegister) {
        engine->mHandler->onRegisterUserRsp(*rsp);
    }
    else if (request == NetReqGetAuthKey) {
        engine->mHandler->onGetAuthKeyRsp(*rsp);
    }
    else if (request == NetReqCreateRoom) {
        engine->mHandler->onCreateRoomRsp(*rsp);
    }
    else if (request == NetReqJoinRoom) {
        JoinRoomRsp *jrRsp = (JoinRoomRsp*)rsp;
        //Get owner
        CommonUtil::parseValue(resp, NetJsonRoomOwnerKey, jrRsp->owner, NetJsonRoomOwnerUnknown);
        
        //Get players
        CommonUtil::parseArray(resp, NetJsonRoomPlayerListKey, jrRsp->players);
        
        engine->mHandler->onJoinRoomRsp(*jrRsp);
    }
    else if (request == NetReqSendDiceNum) {
        engine->mHandler->onSendDiceNumRsp(*rsp);
    }
    else if (request == NetReqStartGame) {
        engine->mHandler->onStartRsp(*rsp);
    }
    else if (request == NetReqPunishFinished) {
        engine->mHandler->onPunishFinishedRsp(*rsp);
    }
}

void NetEngine::sendRequest(const string& route, json_t *msg) {
    pc_request_t *request = pc_request_new();
    pc_request(mClient, request, route.c_str(), msg, onRequestResult);
}

void NetEngine::onEvent(pc_client_t *client, const char *event, void *data) {
    NetEngine* engine = NetEngine::getInstance();
    if (!engine->mHandler) {
        return;
    }
    json_t* msg = (json_t*)data;
    string evt = event;
    if (evt == PC_EVENT_DISCONNECT) {

    }
    else if (evt == PC_EVENT_TIMEOUT) {

    }
    else if (evt == PC_EVENT_KICK) {

    }
    else if (evt == NetEventRollDice) {
        engine->mHandler->onStartRollDice();
    }
    else if (evt == NetEventUserJoined) {
        Player player;
        CommonUtil::parseObj(msg, player);
        engine->mHandler->onPlayerJoined(player);
    }
    else if (evt == NetEventUserLeft) {
        string name;
        CommonUtil::parseValue(msg, NetJsonPlayerNameKey, name, NetJsonPlayerNameUnknown);
        engine->mHandler->onPlayerLeft(name);
    }
    else if (evt == NetEventUserDiceNum) {
        string name;
        int num;
        CommonUtil::parseValue(msg, NetJsonPlayerNameKey, name, NetJsonPlayerNameUnknown);
        CommonUtil::parseValue(msg, NetJsonDiceNumberKey, num, NetJsonDiceNumberDefult);
        engine->mHandler->onPlayerDiceNum(name, num);
    }
    else if (evt == NetEventPunishPlayer) {
        string name, punishment;
        CommonUtil::parseValue(msg, NetJsonPlayerNameKey, name, NetJsonPlayerNameUnknown);
        CommonUtil::parseValue(msg, NetJsonPunishmentKey, punishment, NetJsonPunishmentDefult);
        engine->mHandler->onPunishPlayer(name, punishment);
    }
    else if (evt == NetEventGameFinished) {
        engine->mHandler->onGameFinished();
    }
}
