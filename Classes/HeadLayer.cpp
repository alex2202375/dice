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
    int i;
    int gridx=4, gridy=5;
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    PicCount  = 24;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // background
    auto background = Sprite::create("registerBackground.png");
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(background, 0);
    
    int xnum, ynum;
    for (i = 0; i < PicCount; i ++)
    {
        xnum = i % gridx + 1;
        ynum = i / gridy;
        auto headObj = Sprite::create("playerPicBox.png");
        headObj->setPosition(Vec2(visibleSize.width/(gridx+1)*xnum, visibleSize.height/(gridy+1)*ynum));
        this->addChild(headObj);
    }
    
    
    
    return true;
}
