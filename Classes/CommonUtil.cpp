//
//  CommonUtil.cpp
//  dice
//
//  Created by Hetty on 14-8-10.
//
//
#include <stdio.h>

#include "CommonUtil.h"
#include "Vec2.h"
#include "Constants.h"
#include "CCDirector.h"

void CommonUtil::setPosAccordSize(Node* node)
{
    node->setPosition(Vec2(node->getContentSize().width/2, node->getContentSize().height/2));
}


string CommonUtil::getDiceImage(int num, bool small)
{
    num = num%DiceRunAnimationSize + 1;
    char picName[100] = {0};
    string format = small ? DiceMiniImgFormat: DiceImgFormat;
    sprintf(picName, format.c_str(), num);
    
    return string(picName);
}

Vec2 CommonUtil::getSceenCenter(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    return Vec2(visibleSize.width/2, visibleSize.height/2);
}

bool CommonUtil::isInRect(Sprite* target, const Vec2& pos) {
    // 获取当前点击点所在相对按钮的位置坐标
    Point locationInNode = target->convertToNodeSpace(pos);
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    
    // 点击范围判断检测
    return rect.containsPoint(locationInNode);
}

DiceScene* CommonUtil::getParentScene(Layer* layer)
{
  Node* parent = layer->getParent();
  while (parent) {
      if (dynamic_cast<DiceScene*>(parent)) {
          return (DiceScene*)parent;
      }
      parent = parent->getParent();
  }

  return nullptr;
}


string CommonUtil::getPicture(int picId) {
    char name[50] = {0};
    sprintf(name, HeadImgFormat.c_str(), picId);
    return string(name);
}

int CommonUtil::getPictureId(const string& pic) {
    int id;
    if (sscanf(pic.c_str(), HeadImgFormat.c_str(), &id) == 1) {
        return id;
    }
    else {
        return 1;
    }
}

void CommonUtil::setValue(json_t* jsObj, const string& name, const string& value) {
    json_t *valueJ = json_string(name.c_str());
    json_object_set(jsObj, name.c_str(), valueJ);
    // decref for json object
    json_decref(valueJ);
}

void CommonUtil::setValue(json_t* jsObj, const string& name, const int& value) {
    json_t *valueJ = json_integer(name.c_str());
    json_object_set(jsObj, name.c_str(), valueJ);
    // decref for json object
    json_decref(valueJ);
}

void CommonUtil::setValue(json_t* jsObj, const string& name, const double& value) {
    json_t *valueJ = json_real(name.c_str());
    json_object_set(jsObj, name.c_str(), valueJ);
    // decref for json object
    json_decref(valueJ);
}

void CommonUtil::parseArray(json_t* jsObj, const string& name, list<Player>& result) {
    json_t* obj = json_object_get(jsObj, name.c_str());
    if (obj) {
        parseArray(obj, result);
    }
    else {
        result.clear();
    }
}

void CommonUtil::parseArray(json_t* jsObj, list<Player>& result) {
    size_t count = json_array_size(jsObj);
    for (size_t i = 0; i < count; i++) {
        json_t * objJson = json_array_get(jsObj, i);
        Player obj;
        parseObj(objJson, obj);
        result.push_back(obj);
    }
}

void CommonUtil::parseObj(json_t* jsObj, Player & obj) {
    json_t* name = json_object_get(jsObj, NetJsonPlayerNameKey.c_str());
    obj.name = name ? json_string_value(name) : NetJsonPlayerNameUnknown;
    
    json_t* pic = json_object_get(jsObj, NetJsonPlayerPicKey.c_str());
    obj.picId = pic ? json_integer_value(pic) : NetJsonPlayerPicDefault;
}

#define PARSE_VALUE(jsObj, name, value, defValue) \
        json_t* obj = json_object_get(jsObj, name.c_str()); \
        if (obj) {\
            parseValue(obj, value); \
        } \
        else { \
            value = defValue; \
        } \

void CommonUtil::parseValue(json_t* jsObj, const string& name, string & value, const string & defValue) {
    PARSE_VALUE(jsObj, name, value, defValue);
}

void CommonUtil::parseValue(json_t* jsObj, const string& name, int & value, const int & defValue) {
    PARSE_VALUE(jsObj, name, value, defValue);
}

void CommonUtil::parseValue(json_t* jsObj, const string& name, double & value, const double & defValue) {
    PARSE_VALUE(jsObj, name, value, defValue);
}


void CommonUtil::parseValue(json_t* jsObj, string & value) {
    value = json_string_value(jsObj);
}

void CommonUtil::parseValue(json_t* jsObj, int & value) {
    value = json_integer_value(jsObj);
}

void CommonUtil::parseValue(json_t* jsObj, double & value) {
    value = json_real_value(jsObj);
}
