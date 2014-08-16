//
//  RegisterLayer.cpp
//  dice
//
//  Created by sockyjam on 14-8-16.
//
//

#include "RegisterLayer.h"
#include "CCMenuItem.h"
#include "CCDirector.h"
#include "CCLabelTTF.h"
#include "CCSprite.h"
#include "CCMenu.h"
#include "CCLabelTTF.h"
#include "GameScene.h"
#include "RegisterScene.h"
#include "GUI/CCEditBox/CCEditBox.h"


using namespace cocos2d::extension;
USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;



void RegisterLayer::onEnter() {
    Layer::onEnter();

}

void RegisterLayer::onHeadPicClicked(Ref* caller) {
    log(__FUNCTION__);

}

void RegisterLayer::onRegButtonClicked(Ref * caller) {
    log(__FUNCTION__);

}

bool RegisterLayer::init() {
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

    
    
    // head picture button
    auto HeadPicButton = MenuItemImage::create("registerPicNormal.png", "registerPicPressed.png", CC_CALLBACK_1(RegisterLayer::onHeadPicClicked, this));
    HeadPicButton->setPosition(Vec2(visibleSize.width/2, 0));
    auto HeadPicMenu = Menu::create(HeadPicButton, nullptr);
    HeadPicMenu->setPosition(Vec2(0, visibleSize.height/12*10));
    this->addChild(HeadPicMenu);
    
    
    
    
    
    /* 输入用户名，输入框 */
    Scale9Sprite * sacel9Spruser=Scale9Sprite::create("registerEditBox.png");
    EditBox * usr_inputbox = EditBox::create(Size(300,50), sacel9Spruser);
    
    usr_inputbox->setText("");
    usr_inputbox->setFontColor(Color3B(0, 0, 0));
    usr_inputbox->setPlaceHolder("注册用户名（昵称）");
    usr_inputbox->setMaxLength(12);
    // TODO:
    //    usr_inputbox->setInputFlag(kEditBoxInputFlagSensitive);
    //    usr_inputbox->setReturnType(kKeyboardReturnTypeDone);
    usr_inputbox->setPosition(Vec2(visibleSize.width/2, visibleSize.height/12*8));
    this->addChild(usr_inputbox, 0);
    
    
    /* password */
    Scale9Sprite * sacel9SprPwd=Scale9Sprite::create("registerEditBox.png");
    EditBox * pwd_inputbox = EditBox::create(Size(300,50), sacel9SprPwd);
    
    pwd_inputbox->setText("");
    pwd_inputbox->setFontColor(Color3B(0, 0, 0));
    pwd_inputbox->setPlaceHolder("请输入密码");
    pwd_inputbox->setMaxLength(12);
    // TODO:
    pwd_inputbox->setInputFlag(cocos2d::extension::EditBox::InputFlag::PASSWORD);
    //    pwd_inputbox->setReturnType(kKeyboardReturnTypeDone);
    pwd_inputbox->setPosition(Vec2(visibleSize.width/2, visibleSize.height/12*7));
    this->addChild(pwd_inputbox, 0);
    
    /* re-password */
    Scale9Sprite * sacel9SprRePwd=Scale9Sprite::create("registerEditBox.png");
    EditBox * repwd_inputbox = EditBox::create(Size(300,50), sacel9SprRePwd);
    
    repwd_inputbox->setText("");
    repwd_inputbox->setFontColor(Color3B(0, 0, 0));
    repwd_inputbox->setPlaceHolder("请重复输入密码");
    repwd_inputbox->setMaxLength(12);
    // TODO:
    repwd_inputbox->setInputFlag(cocos2d::extension::EditBox::InputFlag::PASSWORD);
    //    repwd_inputbox->setReturnType(kKeyboardReturnTypeDone);
    repwd_inputbox->setPosition(Vec2(visibleSize.width/2, visibleSize.height/12*6));
    this->addChild(repwd_inputbox, 0);
    
    
    /* telephone */
    Scale9Sprite * sacel9SprReTele=Scale9Sprite::create("registerEditBox.png");
    EditBox * tele_inputbox = EditBox::create(Size(300,50), sacel9SprReTele);
    
    tele_inputbox->setText("");
    tele_inputbox->setFontColor(Color3B(0, 0, 0));
    tele_inputbox->setPlaceHolder("请手机号");
    tele_inputbox->setMaxLength(12);
    // TODO:
    tele_inputbox->setInputMode(cocos2d::extension::EditBox::InputMode::PHONE_NUMBER);
//    tele_inputbox->setInputFlag(cocos2d::extension::EditBox::InputFlag::);
    //    tele_inputbox->setReturnType(kKeyboardReturnTypeDone);
    tele_inputbox->setPosition(Vec2(visibleSize.width/2, visibleSize.height/12*5));
    this->addChild(tele_inputbox, 0);
    
    
    
    /* verify code */
    Scale9Sprite * sacel9SprVcode=Scale9Sprite::create("registerEditBox.png");
    EditBox * vcode_inputbox = EditBox::create(Size(300,50), sacel9SprVcode);
    
    vcode_inputbox->setText("");
    vcode_inputbox->setFontColor(Color3B(0, 0, 0));
    vcode_inputbox->setPlaceHolder("请验证码");
    vcode_inputbox->setMaxLength(12);
    // TODO:
    //    vcode_inputbox->setInputFlag(kEditBoxInputFlagSensitive);
    //    vcode_inputbox->setReturnType(kKeyboardReturnTypeDone);
    vcode_inputbox->setPosition(Vec2(visibleSize.width/2, visibleSize.height/12*4));
    this->addChild(vcode_inputbox, 0);
    
    
    
    
    
    
    // register button
    auto RegButton = MenuItemImage::create("registerButton2Normal.png", "registerButton2Pressed.png", CC_CALLBACK_1(RegisterLayer::onRegButtonClicked, this));
    RegButton->setPosition(Vec2(visibleSize.width/2, 0));
    auto RegMenu = Menu::create(RegButton, nullptr);
    RegMenu->setPosition(Vec2(0, visibleSize.height/12*1));
    this->addChild(RegMenu);
    
    
    return true;
}
