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
const string NetReqLogin = "login";
const string NetReqRegister = "register";
const string NetReqGetAuthKey = "auth";
const string NetReqCreateRoom = "create_room";
const string NetReqJoinRoom = "join_room";
const string NetReqSendDiceNum = "send_dice";
const string NetReqStartGame = "start";
const string NetReqPunishFinished = "punished";

//Event
const string NetEventRollDice = "roll";
const string NetEventUserJoined = "joined";
const string NetEventUserLeft = "joined";
const string NetEventUserDiceNum = "dice_num";
const string NetEventPunishPlayer = "punish";
const string NetEventGameFinished = "game_finished";

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
