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
    
};

#endif /* defined(__dice__CommonUtil__) */
