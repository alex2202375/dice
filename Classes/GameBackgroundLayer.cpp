//
//  GameBackgroundLayer.cpp
//  dice
//
//  Created by Hetty on 14-8-11.
//
//

#include "GameBackgroundLayer.h"

#include "CCDirector.h"
#include "CCMenuItem.h"
#include "CCSprite.h"


bool GameBackgroundLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // add "DiceScene" splash screen"
    auto sprite = Sprite::create("GameBackground.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}