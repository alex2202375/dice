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

using namespace std;

USING_NS_CC;

class CommonUtil {
public:
    static void showWaitDialog(string title);
    
    static bool isValidPhone(string phoneNum);
    
    static void setPosAccordSize(Node* node);
    
    static string getDiceImage(int num);
    
    static Vec2 getSceenCenter();
    
};

#endif /* defined(__dice__CommonUtil__) */
