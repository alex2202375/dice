//
//  CommonUtil.cpp
//  dice
//
//  Created by Hetty on 14-8-10.
//
//

#include "CommonUtil.h"
#include "Vec2.h"

void CommonUtil::setPosAccordSize(Node* node)
{
    node->setPosition(Vec2(node->getContentSize().width/2, node->getContentSize().height/2));
}