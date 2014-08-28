//
//  Constants.h
//  dice
//
//  Created by Hetty on 14-8-15.
//
//

#ifndef dice_Constants_h
#define dice_Constants_h

#include <string>
#include "ccTypes.h"

using namespace std;
USING_NS_CC;

enum PunishType {
    PunishTypeShy = 1,
    PunishTypeBold = 2,
    PunishTypeTrueWords = 3,
    PunishTypeRisky = 4
};

enum PunishCat {
    PunishCatSmall = 1,
    PunishCatBig = 2,
    PunishCatSameMost = 3
};


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
 *libpomelo related definition
**/
//Request
const string NetReqLogin = "gate.gateHandler.loginCheck";
const string NetReqCanRegister = "gate.gateHandler.regcheck";
const string NetReqRegister = "gate.gateHandler.register";
const string NetReqGetAuthKey = "gate.gateHandler.code";
const string NetReqCreateRoom = "connector.entryHandler.create";
const string NetReqJoinRoom = "connector.entryHandler.enter";
const string NetReqSetSetting = "chat.chatHandler.setgamble";
const string NetReqGetSetting = "chat.chatHandler.listgambles";
const string NetReqSendDiceNum = "chat.chatHandler.gamble";
const string NetReqStartGame = "chat.chatHandler.startgamble";
const string NetReqPunishFinished = "chat.chatHandler.punishment";

//Event
const string NetEventRollDice = "onStartGamble";
const string NetEventUserJoined = "onAdd";
const string NetEventUserLeft = "onLeave";
const string NetEventUserDiceNum = "onChat";
const string NetEventPunishPlayer = "onPunishment";
const string NetEventGameFinished = "onFinishGamble";

/**
 *Response JSON keys
 */
const int NetJsonResultOk = 1;
const int NetJsonResultFailed = 0;
//Common
const string NetJsonResultKey = "status";
const string NetJsonResultStrUnknown = "未知错误";
const string NetJsonResultStrConnect = "连接服务器失败";
const string NetJsonResultStrKey = "msg";
const string NetJsonFromKey = "from";
const string NetJsonToKey = "target";
//Register
const string NetJsonRegisterAuthKey = "code";
//Login
const string NetJsonLoginRspIpKey = "ip";
const string NetJsonLoginRspIpInvalid = "";
const string NetJsonLoginRspPortKey = "port";
const int NetJsonLoginRspPortInvalid = -1;
//Room
const string NetJsonRoomOwnerKey = "owner";
const string NetJsonRoomIdKey = "rid";
const string NetJsonRoomOwnerUnknown = "未知房主";
const string NetJsonRoomPlayerListKey = "list";
//Player
const string NetJsonPlayerNameKey = "name";
const string NetJsonPlayerNameUnknown = "未知名字";
const string NetJsonPlayerPhoneKey = "phone";
const string NetJsonPlayerPicIdKey = "pid";
const string NetJsonPlayerPwdKey = "password";
const int NetJsonPlayerPicDefault = 1;
const string NetJsonPlayerPicKey = "pic";
//Dice number
const string NetJsonDiceNumberKey = "content";
const int NetJsonDiceNumberDefult = 1;
//Punish
const string NetJsonPunishmentKey = "punish";
const string NetJsonPunishmentDefult = "未知惩罚";



//Server
const string NetServerIp = "192.168.1.1";
const int NetServerPort = 3041;

const float PI = 3.1415926;

const string DefaultFontName = "fonts/zhanghaishan.ttf";
const int DefaultFontSize = 35;
const Color3B DefaultFontColor = Color3B::BLACK;
const float DefaultActionTime = 0.2;

const string DiceCupImg ="diceCup.png";
const string DiceImgFormat = "dice/dice%d.png";
const string DiceMiniImgFormat = "dice/diceM%d.png";
const string HeadImgFormat = "head/head%d.png";

const string DiceRunAnimationName = "diceRunAnimation";
const int DiceRunAnimationSize = 6;
const string DiceRunAnimationFileNameFormat = "dice/diceChange%d.png";
const int DiceRunAnimationDuration = 1;

// Head Picture Count for chose
const int HeadPicCount = 20;
const int HeadGridx = 4;
const int HeadGridy = 5;

//Punish category
const string PunishCatImg = "punishCategory.png";
const string PunishCatBgImg = "punishCatBg.png";
const string PunishCatSelectedImg = "infoSelected.png";
const string PunishCatNormalImg = "infoNormal.png";
const string PunishCatBigStr = "点数最大";
const string PunishCatSmallStr = "点数最小";
const string PunishCatSameStr = "相同最多";
const string PunishCatFontName = DefaultFontName;
const int PunishCatFontSize = DefaultFontSize;
const Color3B PunishCatFontColor = DefaultFontColor;
const float PunishCatLineMarginLeft = 15;

//Punish type
const string PunishTypeImg = "punishType.png";
const string PunishTypeBgImg = "punishTypeBg.png";
const string PunishTypeSelectedImg = "infoSelected.png";
const string PunishTypeNormalImg = "infoNormal.png";
const string PunishTypeShyStr = "腼腆型";
const string PunishTypeBoldStr = "豪放型";
const string PunishTypeTrueWordsStr = "真心话";
const string PunishTypeRiskyStr = "大冒险";
const string PunishTypeFontName = DefaultFontName;
const int PunishTypeFontSize = DefaultFontSize;
const Color3B PunishTypeFontColor = DefaultFontColor;
const float PunishTypeLineMarginLeft = 15;

const string SelfPixBoxImg = "selfPicBox.png";
const string SelfNameBoxImg = "nickyName.png";
const string SelfWinRateImg = "winRate.png";
const string SelfInfoName = "昵称：";
const string SelfInfoWinRate= "胜率：";
const float SelfInfoLineHeight = 80;
const float SelfInfoLineMarginLeft = 10;
const float SelfInfoLineMarginTop = 10;
const string SelfInfoFontName = DefaultFontName;
const int SelfInfoFontSize = DefaultFontSize;
const Color3B SelfInfoFontColor = DefaultFontColor;

//Player
const string PlayerBgImg = "playerPicBox.png";
const string PlayerPhotoNull = "playerPicBox.png";
const string PlayerFontName = DefaultFontName;
const int PlayerFontSize = 26;
const Color3B PlayerFontColor = DefaultFontColor;
const int PlayerDiceDefaultNum = 6;
const int PlayerLineMarginTop = 0;
const float PlayerRadiusMargin = 16;
const float PlayerPlaceDuration = 0.2;

const string EditBoxImg = "registerEditBox.png";
const float EditBoxWidth = 300;
const float EditBoxHeight = 50;

//ROOM
const string RoomCreateRoomNormalImg = "createRoomNormal.png";
const string RoomCreateRoomPressedImg = "createRoomPressed.png";
const string RoomJoinRoomNormalImg = "joinRoomNormal.png";
const string RoomJoinRoomPressedImg = "joinRoomPressed.png";
const string RoomCreateNormalImg = "createNormal.png";
const string RoomCreatePressedImg = "createPressed.png";
const string RoomJoinNormalImg = "joinNormal.png";
const string RoomJoinPressedImg = "joinPressed.png";
const string RoomCancelNormalImg = "cancelNormal.png";
const string RoomCancelPressedImg = "cancelPressed.png";
const string RoomCreateBgImg = "createRoomBg.png";
const string RoomNumEditBgImg = "roomNumEditBg.png";
const string RoomNumEditTitle = "房间号码:";
const float  RoomNumEditTitleX = 86;
const float RoomNumEditTitleY = 200;
const string RoomNumEditHint = "请输入房间号码";
const string RoomPwdEditBgImg = "passwordEditBg.png";
const string RoomPwdEditTitle = "房间密码:";
const float RoomPwdEditTitleX = RoomNumEditTitleX;
const float RoomPwdEditTitleY = RoomNumEditTitleY - 50;
const string RoomPwdEditHint = "请输入房间密码";
const string RoomFontName = DefaultFontName;
const int RoomFontSize = 35;
const Color3B RoomFontColor = Color3B::GRAY;
const int RoomEditMaxLength = 12;

#endif
