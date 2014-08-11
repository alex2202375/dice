//
//  LoginLayer.cpp
//  dice
//
//  Created by Alex Liu on 14-8-8.
//
//

#include "LoginLayer.h"
#include "CCMenuItem.h"
#include "CCDirector.h"
#include "CCLabelTTF.h"
#include "CCSprite.h"
#include "CCMenu.h"


//void LoginLayer::menuCloseCallback(Ref* pSender)
//{
//    Director::getInstance()->end();
//    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//}

void LoginLayer::onEnter() {
    Layer::onEnter();
//    // add "DiceScene" splash screen"
//    auto label = LabelTTF::create("LoginLayer", "fonts/Marker Felt.ttf", 24);
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//    
//    // position the sprite on the center of the screen
//    label->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    
//    // add the sprite as a child to this layer
//    this->addChild(label, 0);

}

void LoginLayer::onLoginClicked(Ref* caller) {
    log(__FUNCTION__);
    
}

void LoginLayer::onRegisterClicked(Ref * caller) {
    log(__FUNCTION__);
}

bool LoginLayer::init() {
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite *login = Sprite::create("Login.png");
    login->setPosition(Vec2(visibleSize.width/2, login->getContentSize().height/2+60));
    
    auto loginButton = MenuItemImage::create("LoginButton.png", "RegisterButton.png", CC_CALLBACK_1(LoginLayer::onLoginClicked, this));
    loginButton->setPosition(Vec2(57, 0));

    auto registerButton = MenuItemImage::create("RegisterButton.png", "LoginButton.png", CC_CALLBACK_1(LoginLayer::onRegisterClicked, this));
    registerButton->setPosition(Vec2(155, 0));
    
    auto menu = Menu::create(loginButton, registerButton, nullptr);
    menu->setPosition(Vec2(0, 24));
    
    login->addChild(menu);
    addChild(login);
    
    return true;
}
