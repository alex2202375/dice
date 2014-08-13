//
//  GameLayer.cpp
//  dice
//
//  Created by Hetty on 14-8-11.
//
//

#include "GameLayer.h"

#include "CCDirector.h"
#include "CCMenuItem.h"
#include "CCSprite.h"
#include "CCMenu.h"

void GameLayer::onSelfInfoClicked(Ref* sender){
    log(__FUNCTION__);
}

void GameLayer::onPunishInfoClicked(Ref* sender) {
    log(__FUNCTION__);
}

bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto selfInfoMenuItem = MenuItemImage::create("SelfInfo.png", "SelfInfo.png", CC_CALLBACK_1(GameLayer::onSelfInfoClicked, this));
    
    Size selfInfoSize = selfInfoMenuItem->getContentSize();
    selfInfoMenuItem->setPosition(Vec2(selfInfoSize.width/2, visibleSize.height-selfInfoSize.height/2));
    
    auto punishTypeMenuItem = MenuItemImage::create("PunishType.png", "PunishType.png", CC_CALLBACK_1(GameLayer::onPunishInfoClicked, this));
    punishTypeMenuItem->setPosition(Vec2(visibleSize.width-selfInfoSize.width/2, visibleSize.height-selfInfoSize.height/2));
    
    
    auto menu = Menu::create(selfInfoMenuItem, punishTypeMenuItem, nullptr);
    
    menu->setPosition(Vec2::ZERO);
    
    // add the sprite as a child to this layer
    this->addChild(menu);
    
    return true;
}