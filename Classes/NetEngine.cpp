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
        pc_client_stop(mClient);
        pc_client_join(mClient);
//        pc_client_disconnect(mClient);
//        pc_client_destroy(mClient);
//        mClient = nullptr;
    }
    init();
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

bool NetEngine::isConnected() {
    return mClient && (mClient->state == PC_ST_WORKING || mClient->state ==  PC_ST_CONNECTED);
}

bool NetEngine::init() {
    mClient = pc_client_new();
    if (!mClient) {
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
//    CommonUtil::setValue(msg, "uid", 1);
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

void NetEngine::createRoom(const string& name, int roomId, const string& pwd) {
    json_t *msg = json_object();
    CommonUtil::setValue(msg, NetJsonPlayerNameKey, name);
    CommonUtil::setValue(msg, NetJsonRoomIdKey, roomId);
    CommonUtil::setValue(msg, NetJsonRoomPwdKey, pwd);
    sendRequest(NetReqCreateRoom, msg);
}

void NetEngine::joinRoom(const string& name, int roomId, const string& pwd) {
    json_t *msg = json_object();
    CommonUtil::setValue(msg, NetJsonPlayerNameKey, name);
    CommonUtil::setValue(msg, NetJsonRoomIdKey, roomId);
    CommonUtil::setValue(msg, NetJsonRoomPwdKey, pwd);
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
    
    char* msgStr =json_dumps(resp, JSON_ENCODE_ANY);
    log("onRequestResult:event:%s, data:%s", request.c_str(), msgStr);
    delete msgStr;

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
        if (rsp->result == RSP_OK) {
            //Get owner
            CommonUtil::parseValue(resp, NetJsonRoomOwnerKey, jrRsp->owner, NetJsonRoomOwnerUnknown);

            //Get players
            CommonUtil::parseArray(resp, NetJsonRoomPlayerListKey, jrRsp->players);
        }
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
        if (rsp->result == RSP_OK) {
            //Get category id
            CommonUtil::parseValue(resp, NetJsonPunishmentCateKey, settingRsp->catId, 1);
            //Get type id
            CommonUtil::parseValue(resp, NetJsonPunishmentTypeKey, settingRsp->typeId, 1);
        }
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
    char* msgStr =json_dumps(msg, JSON_ENCODE_ANY);
    log("sendRequest: route:%s, msg:%s", route.c_str(), msgStr);
    free(msgStr);
    pc_request_t *request = pc_request_new();
    if (!isConnected() && !connectServer()) {
        request->route = strdup(route.c_str());
        request->msg = msg;
        json_t* resp = json_object();
        json_t* result = json_integer(1);
        json_object_set(resp, NetJsonResultKey.c_str(), result);
        json_decref(result);
        json_t* resultStr = json_string(NetJsonResultStrConnect.c_str());
        json_object_set(resp, NetJsonResultStrKey.c_str(), resultStr);
        json_decref(resultStr);
        onRequestResult(request, -1, resp);
        return;
    }
    else {
        pc_request(mClient, request, route.c_str(), msg, onRequestResult);
    }
}

void NetEngine::onEvent(pc_client_t *client, const char *event, void *data) {
    NetEngine* engine = NetEngine::getInstance();
    if (!engine->mHandler) {
        return;
    }
    json_t* msg = (json_t*)data;
    string evt = event;
    char* dataStr = msg ? json_dumps(msg, JSON_ENCODE_ANY): strdup("no data");
    log("onEvent:%s, data:%s", evt.c_str(), dataStr);
    delete(dataStr);
    if (evt == PC_EVENT_DISCONNECT) {
        engine->mHandler->onDisconnected();
        //Reset to server ip;
        engine->mConnectIp = NetServerIp;
        engine->mConnectPort = NetServerPort;
    }
    else if (evt == PC_EVENT_TIMEOUT) {
        engine->mHandler->onTimeout();
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
        CommonUtil::parseValue(msg, NetJsonFromKey, name, NetJsonPlayerNameUnknown);
        CommonUtil::parseValue(msg, NetJsonDiceNumberKey, num, NetJsonDiceNumberDefult);
        engine->mHandler->onPlayerDiceNum(name, num);
    }
    else if (evt == NetEventPunishPlayer) {
        string name, punishment;
        CommonUtil::parseValue(msg, NetJsonFromKey, name, NetJsonPlayerNameUnknown);
        CommonUtil::parseValue(msg, NetJsonPunishmentKey, punishment, NetJsonPunishmentDefult);
        engine->mHandler->onPunishPlayer(name, punishment);
    }
    else if (evt == NetEventGameFinished) {
        engine->mHandler->onGameFinished();
    }
    else if (evt == NetEventPunishSetting) {
        int pId, cId;
        CommonUtil::parseValue(msg, NetJsonPunishmentCateKey, pId, (int)NetJsonPunishmentCatDefault);
        CommonUtil::parseValue(msg, NetJsonPunishmentTypeKey, cId, (int)NetJsonPunishmentTypeDefault);
        engine->mHandler->onPunishSetting(cId, pId);
    }
}
