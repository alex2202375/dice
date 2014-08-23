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
    
    RegisterScene * scene = RegisterScene::create();
    Director::getInstance()->replaceScene(scene);
    
}

void HeadLayer::onBackClicked(Ref * caller) {
    log(__FUNCTION__);
    
}

bool HeadLayer::init() {
    int i;
    
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
    
    
    
    int xnum, ynum;
    for (i = 0; i < HeadPicCount; i ++)
    {
        xnum = i % HeadGridx + 1;
        ynum = i / HeadGridx + 1;
        
//        Button* button = Button::create("playerPicBox.png");
        
//        auto headObj = Sprite::create("playerPicBox.png");
//        Size headPicSize = headObj->getContentSize();

//        auto HeadButton = MenuItemImage::create("playerPicBox.png", "playerPicBox.png", CC_CALLBACK_1(HeadLayer::onPicClicked, this));
//        HeadButton->setPosition(Vec2(visibleSize.width/(HeadGridx+1)*xnum, visibleSize.height/(HeadGridy+1)*ynum));
//        this->addChild(HeadButton);
        
        
        auto HeadButton = MenuItemImage::create("playerPicBox.png", "playerPicBox.png", CC_CALLBACK_1(HeadLayer::onPicClicked, this));
        HeadButton->setPosition(Vec2(visibleSize.width/(HeadGridx+1)*xnum, 0));
        auto HeadMenu = Menu::create(HeadButton, nullptr);
        HeadMenu->setPosition(Vec2(0, visibleSize.height/(HeadGridy+1)*ynum));
        this->addChild(HeadMenu);
    }
    
    
    
    return true;
}
