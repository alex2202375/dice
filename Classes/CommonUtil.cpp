//
//  CommonUtil.cpp
//  dice
//
//  Created by Hetty on 14-8-10.
//
//

#include "CommonUtil.h"
#include "Vec2.h"
#include "Constants.h"
#include "CCDirector.h"

void CommonUtil::setPosAccordSize(Node* node)
{
    node->setPosition(Vec2(node->getContentSize().width/2, node->getContentSize().height/2));
}


string CommonUtil::getDiceImage(int num)
{
    num = num%DiceRunAnimationSize + 1;
    char picName[100] = {0};
    sprintf(picName, DiceImgFormat.c_str(), num);
    
    return string(picName);
}

Vec2 CommonUtil::getSceenCenter(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    return Vec2(visibleSize.width/2, visibleSize.height/2);
}