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
    /**
     *出血买单抉择
     */
    PunishTypeBuy = 5,
    /**
     *无底线型
     */
    PunishTypeNoLimitted = 6,
    /**
     *奔放型
     */
    PunishTypeBold = 7,
    /**
     *闷骚型
     */
    PunishTypeShy = 8,
    /**
     *童真无邪型
     */
    PunishTypeNaive = 9
};

enum PunishCat {
    /**
     *最小者输
     */
    PunishCatSmall = 1,
    /**
     *最大者输
     */
    PunishCatBig = 2,
    /**
     *重复最多者输
     */
    PunishCatSameMost = 3,
    /**
     *重复最少者输
     */
    PunishCatSameLeast = 4
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
//const string NetReqLogin = "gate.gateHandler.queryEntry";
const string NetReqCanRegister = "gate.gateHandler.regcheck";
const string NetReqRegister = "gate.gateHandler.register";
const string NetReqGetAuthKey = "gate.gateHandler.code";
const string NetReqCreateRoom = "connector.entryHandler.create";
const string NetReqJoinRoom = "connector.entryHandler.enter";
const string NetReqSetSetting = "chat.chatHandler.setconfig";
const string NetReqGetSetting = "chat.chatHandler.listconfig";
const string NetReqSendDiceNum = "chat.chatHandler.gamble";
const string NetReqStartGame = "chat.chatHandler.startgamble";
const string NetReqPunishFinished = "chat.chatHandler.punishment";

//Event
const string NetEventRollDice = "onStartGamble";
const string NetEventUserJoined = "onAdd";
const string NetEventUserLeft = "onLeave";
const string NetEventPunishSetting = "onSetconfig";
const string NetEventUserDiceNum = "onGamble";
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
const string NetJsonLoginRspIpKey = "host";
const string NetJsonLoginRspIpInvalid = "";
const string NetJsonLoginRspPortKey = "port";
const int NetJsonLoginRspPortInvalid = -1;
//Room
const string NetJsonRoomOwnerKey = "owner";
const string NetJsonRoomIdKey = "rid";
const string NetJsonRoomPwdKey = "rpwd";
const string NetJsonRoomOwnerUnknown = "未知房主";
const string NetJsonRoomPlayerListKey = "users";
//Player
const string NetJsonPlayerKey = "user";
const string NetJsonPlayerNameKey = "name";
const string NetJsonPlayerNameUnknown = "未知名字";
const string NetJsonPlayerPhoneKey = "phone";
const string NetJsonPlayerPicIdKey = "imgurl";
const string NetJsonPlayerPwdKey = "passwd";
const int NetJsonPlayerPicDefault = 1;
const string NetJsonPlayerPicKey = "pic";
//Dice number
const string NetJsonDiceNumberKey = "rval";
const int NetJsonDiceNumberDefult = 1;
//Punish
const string NetJsonPunishmentKey = "msg";
const string NetJsonPunishmentCateKey = "cid";
const PunishCat NetJsonPunishmentCatDefault = PunishCatSmall;
const string NetJsonPunishmentTypeKey = "pid";
const PunishType NetJsonPunishmentTypeDefault = PunishTypeBuy;
const string NetJsonPunishmentDefult = "未知惩罚";



//Server
const string NetServerIp = "182.92.82.164";
const int NetServerPort = 3014;

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
const string PunishCatBgImg = "punishTypeBg.png";
const string PunishCatSelectedImg = "infoSelected.png";
const string PunishCatNormalImg = "infoNormal.png";
const string PunishCatBigStr = "最大者输";
const string PunishCatSmallStr = "最小者输";
const string PunishCatSameMostStr = "重复最多者输";
const string PunishCatSameLeastStr = "重复最少者输";
const string PunishCatFontName = DefaultFontName;
const int PunishCatFontSize = DefaultFontSize;
const Color3B PunishCatFontColor = DefaultFontColor;
const float PunishCatLineMarginLeft = 15;

//Punish type
const string PunishTypeImg = "punishType.png";
const string PunishTypeBgImg = "punishTypeBg.png";
const string PunishTypeSelectedImg = "infoSelected.png";
const string PunishTypeNormalImg = "infoNormal.png";
const string PunishTypeBuyStr = "出血买单抉择";
const string PunishTypeShyStr = "闷骚型";
const string PunishTypeBoldStr = "奔放型";
const string PunishTypeNoLimitedStr = "无底线型";
const string PunishTypeNaiveStr = "童真无邪型";
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

//Game
const string GameStartImg = "start.png";
const string GameShakePhoneImg = "shakePhone.png";
const float GameShakePhoneActionDeltaX = 5;
const float GameShakePhoneActionDuration = 0.02;
const float GameShakePhoneFinishDuration = 5;
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
//Punishment
const string PunishmentIcon = "punish.png";
const string PunishmentFontName = DefaultFontName;
const int PunishmentFontSize = 30;
const Color3B PunishmentFontColor = Color3B::GRAY;
const int PunishmentLabelY = 200;
const string PunishmentFinishedStr = "当前惩罚结束";

const int NotifyDefaultCloseDelay = 2;
const string NotifyBgImg = "dialogBg.png";
const string NotifyFontName = DefaultFontName;
const int NotifyFontSize = 26;
const float NotifyShowHideDuration = 0.2f;

/**
 * Strings
 */
//Register
const string RegisterNoName = "请输入用户名";
const string RegisterPwdNotSame = "两次输入的密码不一致";
const string RegisterPhoneNotValid = "请输入正确的电话号码";
const string RegisterNoAuthCode = "请输入验证码";
//Login
const string LoginNoName = "请输入用户名";
const string LoginNoPwd = "请输入密码";
//Timeout
const string NetTimeOut = "连接服务器超时";
//Game
const string GameFinished = "本局游戏结束";


//Cocos Event
const string DiceEventSwithTo = "swithTo";

#endif
