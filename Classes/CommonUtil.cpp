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
