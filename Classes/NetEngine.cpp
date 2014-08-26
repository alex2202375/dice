//
//  NetEngine.cpp
//  dice
//
//  Created by Hetty on 14-8-10.
//
//

#include "NetEngine.h"

#include "pomelo.h"

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
    pc_add_listener(mClient, NetEventPunishFinished.c_str(), onEvent);
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

void NetEngine::onRequestResult(pc_request_t* req, int status, json_t *resp) {
    NetEngine* engine = NetEngine::getInstance();
    if (!mHandler) {
        return;
    }

    string request = req->route;
    if (request == NetReqLogin) {
        mHandler->onLoginRsp();
    }
    else if (request == NetReqRegister) {
        mHandler->onRegisterUserRsp();
    }
    else if (request == NetReqGetAuthKey) {
        mHandler->onGetAuthKeyRsp();
    }
    else if (request == NetReqCreateRoom) {
        mHandler->onCreateRoomRsp();
    }
    else if (request == NetReqJoinRoom) {
        mHandler->onJoinRoomRsp();
    }
    else if (request == NetReqSendDiceNum) {
        mHandler->onSendDiceNumRsp();
    }
    else if (request == NetReqStartGame) {
        mHandler->onStartRsp();
    }
    else if (request == NetReqPunishFinished) {
        mHandler->onPunishFinishedRsp();
    }
}

void NetEngine::onEvent(pc_client_t *client, const char *event, void *data) {
    NetEngine* engine = NetEngine::getInstance();
    if (!mHandler) {
        return;
    }
    string evt = event;
    if (evt == PC_EVENT_DISCONNECT) {

    }
    else if (evt == PC_EVENT_TIMEOUT) {

    }
    else if (evt == PC_EVENT_KICK) {

    }
    else if (evt == NetEventRollDice) {

    }
    else if (evt == NetEventUserJoined) {

    }
    else if (evt == NetEventUserLeft) {

    }
    else if (evt == NetEventUserDiceNum) {
        mHandler->on
    }
    else if (evt == NetEventPunishPlayer) {
        mHandler->onPunishUser();
    }
    else if (evt == NetEventPunishFinished) {
        mHandler->onPunishFinished();
    }
    else if (evt == NetEventGameFinished) {
        mHandler->onGameFinished();
    }
}
