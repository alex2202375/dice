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
    

    /**
     * Json related functions
     */

    //Set functions
    static void setValue(json_t* jsObj, const string& name, const string& value);
    static void setValue(json_t* jsObj, const string& name, const int& value);
    static void setValue(json_t* jsObj, const string& name, const double& value);

    //Parse functions
    static void parseArray(json_t* jsObj, const string& name, list<Player>& result);
    static void parseArray(json_t* jsObj, list<Player>& result);

    static void parseObj(json_t* jsObj, Player & obj);

    static void parseValue(json_t* jsObj, const string& name, string & value, const string & defValue);
    static void parseValue(json_t* jsObj, const string& name, int & value, const int & defValue);
    static void parseValue(json_t* jsObj, const string& name, double & value, const double & defValue);

    static void parseValue(json_t* jsObj, string & value);
    static void parseValue(json_t* jsObj, int & value);
    static void parseValue(json_t* jsObj, double & value);
};

#endif /* defined(__dice__CommonUtil__) */
