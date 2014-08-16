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
#include "GameScene.h"
#include "RegisterScene.h"


//using namespace cocos2d::extension;
USING_NS_CC;
using namespace CocosDenshion;

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
    GameScene * scene = GameScene::create();
    Director::getInstance()->replaceScene(scene);
}

void LoginLayer::onRegisterClicked(Ref * caller) {
    log(__FUNCTION__);
    RegisterScene * scene = RegisterScene::create();
    Director::getInstance()->replaceScene(scene);
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
    
    Sprite *login = Sprite::create("loginRectBack.png");
    login->setPosition(Vec2(visibleSize.width/2, visibleSize.height/3));
    Vec2 backRectPos = login->getPosition();
    Size backRectSize = login->getContentSize();
    auto loginButton = MenuItemImage::create("loginButtonNormal.png", "loginButtonPressed.png", CC_CALLBACK_1(LoginLayer::onLoginClicked, this));
    loginButton->setPosition(Vec2(backRectSize.width/4, 0));

    auto registerButton = MenuItemImage::create("registerButtonNormal.png", "registerButtonPressed.png", CC_CALLBACK_1(LoginLayer::onRegisterClicked, this));
    registerButton->setPosition(Vec2(backRectSize.width/4 * 3, 0));
    
    auto menu = Menu::create(loginButton, registerButton, nullptr);
    menu->setPosition(Vec2(0, backRectSize.height/4));
    
    login->addChild(menu);
    addChild(login);
    
    
    
    //Size backRectSize = login->getWinSize();
    
    /* 输入用户名，输入框 */
    Size size = Director::getInstance()->getWinSize();
    Scale9Sprite * sacel9SprY=Scale9Sprite::create("editRect.png");
    EditBox * m_InputBox = EditBox::create(Size(280,60), sacel9SprY);
    
    m_InputBox->setText("");
    m_InputBox->setFontColor(Color3B(0, 0, 0));
    m_InputBox->setPlaceHolder("请输入帐号");
    m_InputBox->setMaxLength(12);
    // TODO:
//    m_InputBox->setInputFlag(kEditBoxInputFlagSensitive);
//    m_InputBox->setReturnType(kKeyboardReturnTypeDone);
    m_InputBox->setPosition(Vec2(backRectSize.width/2, backRectSize.height/4 * 3));
    login->addChild(m_InputBox);
    
    /* 输入密码，输入框 */
    Scale9Sprite  * scale9SprG =Scale9Sprite::create("editRect.png");
    EditBox * m_PwdBox = EditBox::create(Size(280, 60), scale9SprG);
    m_PwdBox->setPosition(Vec2(backRectSize.width/2, backRectSize.height/2));
    m_PwdBox->setFontColor(Color3B(0, 0, 0));
    m_PwdBox->setPlaceHolder("输入密码");
    m_PwdBox->setMaxLength(12);
    // TODO:
//    m_PwdBox->setInputFlag(kEditBoxInputFlagPassword);
//    m_PwdBox->setReturnType(kKeyboardReturnTypeGo);
    login->addChild(m_PwdBox);
   
    return true;
}
