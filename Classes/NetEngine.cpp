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
NetEngine* NetEngine::sInstance = NULL;

NetEngine* NetEngine::getInstance() {
    if (!sInstance) {
        sInstance = new NetEngine();
        if (sInstance) {
            if (!sInstance->init()) {
                sInstance->release();
                return nullptr;
            }
            sInstance->retain();
        }
    }
    return sInstance;
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


void NetEngine::canRegister(const string& name, const string& phone) {
    json_t *msg = json_object();
    CommonUtil::setValue(msg, NetJsonPlayerNameKey, name);
    CommonUtil::setValue(msg, NetJsonPlayerPhoneKey, phone);

    sendRequest(NetReqCanRegister, msg);
}

void NetEngine::login(const string& name, const string& passwd) {
    json_t *msg = json_object();
    CommonUtil::setValue(msg, NetJsonPlayerNameKey, name);
    CommonUtil::setValue(msg, NetJsonPlayerPwdKey, passwd);

    sendRequest(NetReqLogin, msg);
}

void NetEngine::getAuthKey(const string& name, const string& phone) {
    json_t *msg = json_object();
    CommonUtil::setValue(msg, NetJsonPlayerNameKey, name);
    CommonUtil::setValue(msg, NetJsonPlayerPhoneKey, phone);

    sendRequest(NetReqGetAuthKey, msg);
}

void NetEngine::registerUser(const string& name, const string& passwd,
                  const string& phone, int imageId, const string& authKey) {
    json_t *msg = json_object();
    CommonUtil::setValue(msg, NetJsonPlayerNameKey, name);
    CommonUtil::setValue(msg, NetJsonPlayerPwdKey, passwd);
    CommonUtil::setValue(msg, NetJsonPlayerPhoneKey, phone);
    CommonUtil::setValue(msg, NetJsonPlayerPicIdKey, imageId);
    CommonUtil::setValue(msg, NetJsonRegisterAuthKey, authKey);
    sendRequest(NetReqRegister, msg);
}

void NetEngine::createRoom(const string& name, int roomId) {
    json_t *msg = json_object();
    CommonUtil::setValue(msg, NetJsonPlayerNameKey, name);
    CommonUtil::setValue(msg, NetJsonRoomIdKey, roomId);
    sendRequest(NetReqCreateRoom, msg);
}

void NetEngine::joinRoom(const string& name, int roomId) {
    json_t *msg = json_object();
    CommonUtil::setValue(msg, NetJsonPlayerNameKey, name);
    CommonUtil::setValue(msg, NetJsonRoomIdKey, roomId);
    sendRequest(NetReqJoinRoom, msg);
}

void NetEngine::getPunishSetting(const string& name, int roomId) {
    json_t *msg = json_object();
    CommonUtil::setValue(msg, NetJsonFromKey, name);
    CommonUtil::setValue(msg, NetJsonRoomIdKey, roomId);
    sendRequest(NetReqGetSetting, msg);
}

void NetEngine::setPunishSetting(const string& name, int roomId, int punishCat, int punishType) {
    json_t *msg = json_object();
    CommonUtil::setValue(msg, NetJsonPunishmentCateKey, punishCat);
    CommonUtil::setValue(msg, NetJsonPunishmentTypeKey, punishType);
    sendRequest(NetReqSetSetting, msg);
}

void NetEngine::sendDiceNum(const string& name, int roomId, int num) {
    json_t *msg = json_object();
    CommonUtil::setValue(msg, NetJsonFromKey, name);
    CommonUtil::setValue(msg, NetJsonRoomIdKey, roomId);
    CommonUtil::setValue(msg, NetJsonDiceNumberKey, num);
    sendRequest(NetReqSendDiceNum, msg);
}

void NetEngine::startGame(const string& name, int roomId) {
    json_t *msg = json_object();
    CommonUtil::setValue(msg, NetJsonFromKey, name);
    CommonUtil::setValue(msg, NetJsonRoomIdKey, roomId);
    sendRequest(NetReqStartGame, msg);
}

void NetEngine::punishFinished(const string& name, int roomId) {
    json_t *msg = json_object();
    CommonUtil::setValue(msg, NetJsonFromKey, name);
    CommonUtil::setValue(msg, NetJsonRoomIdKey, roomId);
    sendRequest(NetReqPunishFinished, msg);
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
    else if (request == NetReqGetSetting) {
        rsp = new GetPunishSettingRsp();
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
    else if (request == NetReqGetSetting) {
        GetPunishSettingRsp *settingRsp = (GetPunishSettingRsp*)rsp;
        //Get category id
        CommonUtil::parseValue(resp, NetJsonPunishmentCateKey, settingRsp->catId, 1);
        //Get type id
        CommonUtil::parseValue(resp, NetJsonPunishmentTypeKey, settingRsp->typeId, 1);
        engine->mHandler->onGetPunishSettingRsp(*settingRsp);
    }
    else if (request == NetReqSetSetting) {
        engine->mHandler->onSetPunishSettingRsp(*rsp);
    }

    // release relative resource with pc_request_t
    json_t *msg = req->msg;
    json_decref(msg);
    pc_request_destroy(req);
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
