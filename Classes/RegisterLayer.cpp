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
#include "CCLabel.h"
#include "GameScene.h"
#include "RegisterScene.h"
#include "ui/UICheckBox.h"
#include "GUI/CCEditBox/CCEditBox.h"
#include "HeadScene.h"
#include "LoginScene.h"
#include "LogicalEngine.h"
#include "CommonUtil.h"


using namespace cocos2d::extension;
USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;


RegisterLayer::~RegisterLayer() {
    CommonUtil::releaseRef(mUserNameEdit);
    CommonUtil::releaseRef(mUserPwdEdit);
    CommonUtil::releaseRef(mUserPwd2Edit);
    CommonUtil::releaseRef(mUserPhoneEdit);
    CommonUtil::releaseRef(mUserAuthCodeEdit);
}

void RegisterLayer::onEnter() {
    Layer::onEnter();
}

void RegisterLayer::savePlayerInfo() {
        LogicalEngine* engine = LogicalEngine::getInstance();
//    engine->setPlayerName()
}

void RegisterLayer::onHeadPicClicked(Ref* caller) {
    log(__FUNCTION__);
    
    LogicalEngine* engine = LogicalEngine::getInstance();
    engine->switchTo(SceneCreater::SCENE_PIC_SEL);
}

void RegisterLayer::onRegButtonClicked(Ref * caller) {
    log(__FUNCTION__);
    
    LogicalEngine* engine = LogicalEngine::getInstance();
    string name = mUserNameEdit->getText();
    string password = mUserPwdEdit->getText();
    string password2 = mUserPwd2Edit->getText();
    string phone = mUserPhoneEdit->getText();
    int picId = engine->getPlayerPicId();
    string authKey = mUserAuthCodeEdit->getText();
    DiceScene* scene = CommonUtil::getParentScene(this);
    if (!scene) {
        return;
    }

    string errorStr;
    if (!name.size()) {
        errorStr = RegisterNoName;
    }
    else if (password != password2) {
        errorStr = RegisterPwdNotSame;
    }
    else if (!CommonUtil::isValidPhone(phone)) {
        errorStr = RegisterPhoneNotValid;
    }
    else if (!authKey.size()) {
        errorStr = RegisterNoAuthCode;
    }

    if (errorCode.size()) {
        scene->showNotifyDialog(errorStr);
    }
    else {
        engine->registerUser(name, password, phone, picId, authKey);
    }
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

    LogicalEngine* engine = LogicalEngine::getInstance();
    
    // head picture button
    string picImage1 = "registerPicNormal.png";
    string picImage2 = "registerPicPressed.png";
    if (engine->getPlayerPicId() != -1) {
        picImage1 = picImage2 = CommonUtil::getPicture(engine->getPlayerPicId());
    }
    auto HeadPicButton = MenuItemImage::create(picImage1, picImage2, CC_CALLBACK_1(RegisterLayer::onHeadPicClicked, this));
    HeadPicButton->setPosition(Vec2(visibleSize.width/2, 0));
    auto HeadPicMenu = Menu::create(HeadPicButton, nullptr);
    HeadPicMenu->setPosition(Vec2(0, visibleSize.height/12*10));
    this->addChild(HeadPicMenu);
    
    
    /* 输入用户名，输入框 */
    Label* usrLabel = Label::create("用户名","Marker Felt",30);
    usrLabel->setPosition(Vec2(visibleSize.width/8, visibleSize.height/12*8));
    this->addChild(usrLabel);
    
    Scale9Sprite * sacel9Spruser=Scale9Sprite::create("registerEditBox.png");
    mUserNameEdit = EditBox::create(Size(300,50), sacel9Spruser);
    mUserNameEdit->setText(engine->getPlayerName().c_str());
    mUserNameEdit->setFontColor(Color3B(0, 0, 0));
    mUserNameEdit->setPlaceHolder("注册用户名（昵称）");
    mUserNameEdit->setMaxLength(12);
    // TODO:
    //    usr_inputbox->setInputFlag(kEditBoxInputFlagSensitive);
    //    usr_inputbox->setReturnType(kKeyboardReturnTypeDone);
    mUserNameEdit->setPosition(Vec2(visibleSize.width/2, visibleSize.height/12*8));
    mUserNameEdit->retain();
    this->addChild(mUserNameEdit, 0);
    
    
    
    /* password */
    Label* pwdLabel = Label::create("密码","Marker Felt",30);
    pwdLabel->setPosition(Vec2(visibleSize.width/8, visibleSize.height/12*7));
    this->addChild(pwdLabel);
    Scale9Sprite * sacel9SprPwd=Scale9Sprite::create("registerEditBox.png");
    mUserPwdEdit = EditBox::create(Size(300,50), sacel9SprPwd);
    
    mUserPwdEdit->setText(engine->getPlayerPwd().c_str());
    mUserPwdEdit->setFontColor(Color3B(0, 0, 0));
    mUserPwdEdit->setPlaceHolder("请输入密码");
    mUserPwdEdit->setMaxLength(12);
    // TODO:
    mUserPwdEdit->setInputFlag(cocos2d::extension::EditBox::InputFlag::PASSWORD);
    //    pwd_inputbox->setReturnType(kKeyboardReturnTypeDone);
    mUserPwdEdit->setPosition(Vec2(visibleSize.width/2, visibleSize.height/12*7));
    mUserPwdEdit->retain();
    this->addChild(mUserPwdEdit, 0);
    
    /* re-password */
    Label* repwdLabel = Label::create("重复密码","Marker Felt",30);
    repwdLabel->setPosition(Vec2(visibleSize.width/8, visibleSize.height/12*6));
    this->addChild(repwdLabel);
    Scale9Sprite * sacel9SprRePwd=Scale9Sprite::create("registerEditBox.png");
    mUserPwd2Edit = EditBox::create(Size(300,50), sacel9SprRePwd);
    
    mUserPwd2Edit->setText(engine->getPlayerPwd().c_str());
    mUserPwd2Edit->setFontColor(Color3B(0, 0, 0));
    mUserPwd2Edit->setPlaceHolder("请重复输入密码");
    mUserPwd2Edit->setMaxLength(12);
    // TODO:
    mUserPwd2Edit->setInputFlag(cocos2d::extension::EditBox::InputFlag::PASSWORD);
    //    repwd_inputbox->setReturnType(kKeyboardReturnTypeDone);
    mUserPwd2Edit->setPosition(Vec2(visibleSize.width/2, visibleSize.height/12*6));
    mUserPwd2Edit->retain();
    this->addChild(mUserPwd2Edit, 0);
    
    
    /* telephone */
    Label* teleLabel = Label::create("手机号","Marker Felt",30);
    teleLabel->setPosition(Vec2(visibleSize.width/8, visibleSize.height/12*5));
    this->addChild(teleLabel);
    Scale9Sprite * sacel9SprReTele=Scale9Sprite::create("registerEditBox.png");
    mUserPhoneEdit = EditBox::create(Size(300,50), sacel9SprReTele);
    
    mUserPhoneEdit->setText(engine->getPlayerPhone().c_str());
    mUserPhoneEdit->setFontColor(Color3B(0, 0, 0));
    mUserPhoneEdit->setPlaceHolder("手机号");
    mUserPhoneEdit->setMaxLength(12);
    // TODO:
    mUserPhoneEdit->setInputMode(cocos2d::extension::EditBox::InputMode::PHONE_NUMBER);
//    tele_inputbox->setInputFlag(cocos2d::extension::EditBox::InputFlag::);
    //    tele_inputbox->setReturnType(kKeyboardReturnTypeDone);
    mUserPhoneEdit->setPosition(Vec2(visibleSize.width/2, visibleSize.height/12*5));
    mUserPhoneEdit->retain();
    this->addChild(mUserPhoneEdit, 0);
    
    
    
    /* verify code */
    Label* vcodeLabel = Label::create("验证码","Marker Felt",30);
    vcodeLabel->setPosition(Vec2(visibleSize.width/8, visibleSize.height/12*4));
    this->addChild(vcodeLabel);
    Scale9Sprite * sacel9SprVcode=Scale9Sprite::create("registerEditBox.png");
    mUserAuthCodeEdit = EditBox::create(Size(300,50), sacel9SprVcode);
    
    mUserAuthCodeEdit->setText(engine->getAuthCode().c_str());
    mUserAuthCodeEdit->setFontColor(Color3B(0, 0, 0));
    mUserAuthCodeEdit->setPlaceHolder("验证码");
    mUserAuthCodeEdit->setMaxLength(12);
    // TODO:
    //    vcode_inputbox->setInputFlag(kEditBoxInputFlagSensitive);
    //    vcode_inputbox->setReturnType(kKeyboardReturnTypeDone);
    mUserAuthCodeEdit->setPosition(Vec2(visibleSize.width/2, visibleSize.height/12*4));
    mUserAuthCodeEdit->retain();
    this->addChild(mUserAuthCodeEdit, 0);
    
    
    /* agreement */
    Label* agreeLabel = Label::create("我同意该游戏的使用条款","Marker Felt",30);
    agreeLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height/12*3));
    CheckBox* agreeCheck = CheckBox::create();
    agreeCheck->setTouchEnabled(true);
    agreeCheck->loadTextures("checkBox.png", "checkBox.png", "checked.png", "checked.png", "checkBox.png");
    agreeCheck->setPosition(Vec2(visibleSize.width/6, visibleSize.height/12*3));
    this->addChild(agreeLabel);
    this->addChild(agreeCheck);

    
    
    // register button
    auto RegButton = MenuItemImage::create("registerButton2Normal.png", "registerButton2Pressed.png", CC_CALLBACK_1(RegisterLayer::onRegButtonClicked, this));
    RegButton->setPosition(Vec2(visibleSize.width/2, 0));
    auto RegMenu = Menu::create(RegButton, nullptr);
    RegMenu->setPosition(Vec2(0, visibleSize.height/12*1));
    this->addChild(RegMenu);
    
    
    return true;
}
