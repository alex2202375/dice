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

const string DefaultFontName = "fonts/HKYuanMini.ttf";
const int DefaultFontSize = 35;
const Color3B DefaultFontColor = Color3B::BLACK;
const float DefaultActionTime = 0.2;

const string DiceCupImg ="diceCup.png";
const char* DiceImgFormat ="dice/dice%d.png";

const string DiceRunAnimationName = "diceRunAnimation";
const int DiceRunAnimationSize = 6;
const char* DiceRunAnimationFileNameFormat = "dice/diceChange%d.png";
const int DiceRunAnimationDuration = 1;

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

#endif
