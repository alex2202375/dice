//
//  HeadLayer.cpp
//  dice
//
//  Created by sockyjam on 14-8-17.
//
//

#include "HeadLayer.h"

#include "CCMenuItem.h"
#include "CCDirector.h"
#include "CCLabelTTF.h"
#include "CCSprite.h"
#include "CCMenu.h"
#include "CCLabelTTF.h"
#include "CCLabel.h"
#include "GameScene.h"
#include "RegisterScene.h"


using namespace cocos2d::extension;
USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;



void HeadLayer::onEnter() {
    Layer::onEnter();
    
}

void HeadLayer::onPicClicked(Ref* caller) {
    log(__FUNCTION__);
    
}

void HeadLayer::onBackClicked(Ref * caller) {
    log(__FUNCTION__);
    
}

bool HeadLayer::init() {
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // background
    auto background = Sprite::create("registerBackground.png");
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(background, 0);
    
    
    
    return true;
}