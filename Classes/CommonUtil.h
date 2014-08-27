//
//  CommonUtil.h
//  dice
//
//  Created by Hetty on 14-8-10.
//
//

#ifndef __dice__CommonUtil__
#define __dice__CommonUtil__

#include <iostream>
#include "CCNode.h"
#include "CCSprite.h"
#include "DiceScene.h"
#include "jansson.h"
#include "Player.h"

using namespace std;

USING_NS_CC;

class CommonUtil {
public:
    static void showWaitDialog(string title);
    
    static bool isValidPhone(string phoneNum);
    
    static void setPosAccordSize(Node* node);
    
    static string getDiceImage(int num, bool small = false);
    
    static Vec2 getSceenCenter();
    
    static bool isInRect(Sprite* target, const Vec2& pos);
    
    static DiceScene* getParentScene(Layer* layer);
    
    static string getPicture(int picId);
    
    static int getPictureId(const string& pic);
    
    static string parseStr(json_t* jsObj, const string& defValue = "");
    
    static int parseInt(json_t* jsObj, int defValue = -1);
    
    template <typename T>
    static void parseArray(json_t* jsObj, const string& name, list<T>& result);
    
    template <typename T>
    static void parseArray(json_t* jsObj, list<T>& result);
    
    template <typename T>
    static void parseObj(json_t* jsObj, T & obj);
    
    template <typename T>
    static void parseValue(json_t* jsObj, const string& name, T & value, const T & defValue);
    
    template <typename T>
    static void parseValue(json_t* jsObj, T & value);
};

#endif /* defined(__dice__CommonUtil__) */
