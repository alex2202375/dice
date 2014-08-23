//
//  Room.cpp
//  dice
//
//  Created by Hetty on 14-8-10.
//
//
#include "GUI/CCEditBox/CCEditBox.h"
#include "GUI/CCControlExtension/CCScale9Sprite.h"
#include "CCLabelTTF.h"
#include "CCMenuItem.h"
#include "CCMenu.h"

#include "Room.h"
#include "Constants.h"

USING_NS_CC_EXT;

RoomCreateJoin::~RoomCreateJoin() {
    mRoomNumEdit->release();
    mRoomPwdEdit->release();
    mCreateMenuItem->release();
    mJoinMenuItem->release();
}

void RoomCreateJoin::setType(CreateOrJoin type) {
    if (type == CREATE_ROOM) {
        mCreateMenuItem->setVisible(true);
        mJoinMenuItem->setVisible(false);
    }
    else if (type == JOIN_ROOM) {
        mJoinMenuItem->setVisible(true);
        mCreateMenuItem->setVisible(false);
    }
}

RoomCreateJoin::RoomCreateJoin()
: mOkHandler(nullptr), mCancelHandler(nullptr)
{
    
}

RoomCreateJoin::CreateOrJoin RoomCreateJoin::getType() {
    return mType;
}

void RoomCreateJoin::setOnOKClicked(const onOKClickedHandler& handler) {
    mOkHandler = handler;
}

void RoomCreateJoin::setOnCancelClicked(const onCancelClickedHandler& handler) {
    mCancelHandler = handler;
}

void RoomCreateJoin::onOkClicked(Ref* sender) {
    if (mOkHandler) {
        mOkHandler(mRoomNumEdit->getText(), mRoomPwdEdit->getText());
    }
}

void RoomCreateJoin::onCancelClicked(Ref* sender) {
    if (mCancelHandler) {
        mCancelHandler();
    }
}

bool RoomCreateJoin::init(){
    if (!Sprite::initWithFile(RoomCreateBgImg)) {
        return false;
    }
    
    //Room Number edit
    auto numLabel = LabelTTF::create(RoomNumEditTitle, RoomFontName, RoomFontSize);
    numLabel->setColor(RoomFontColor);
    numLabel->setPosition(Vec2(RoomNumEditTitleX, RoomNumEditTitleY));
    
    Scale9Sprite * sacel9SprVcode=Scale9Sprite::create(EditBoxImg);
    mRoomNumEdit = EditBox::create(Size(EditBoxWidth,EditBoxHeight), sacel9SprVcode);
    mRoomNumEdit->setText("");
    mRoomNumEdit->setFontColor(RoomFontColor);
    mRoomNumEdit->setPlaceHolder(RoomNumEditHint.c_str());
    mRoomNumEdit->setMaxLength(RoomEditMaxLength);
    mRoomNumEdit->setInputMode(EditBox::InputMode::NUMERIC);
    mRoomNumEdit->setReturnType(EditBox::KeyboardReturnType::DONE);
    mRoomNumEdit->setPosition(Vec2(numLabel->getPosition().x+ numLabel->getContentSize().width/2 + mRoomNumEdit->getContentSize().width/2, numLabel->getPosition().y));
    mRoomNumEdit->retain();
    
    addChild(numLabel);
    addChild(mRoomNumEdit);
    
    //Room password edit
    auto pwdLabel = LabelTTF::create(RoomPwdEditTitle, RoomFontName, RoomFontSize);
    pwdLabel->setColor(RoomFontColor);
    pwdLabel->setPosition(Vec2(RoomPwdEditTitleX, RoomPwdEditTitleY));
    
    sacel9SprVcode=Scale9Sprite::create(EditBoxImg);
    mRoomPwdEdit = EditBox::create(Size(EditBoxWidth,EditBoxHeight), sacel9SprVcode);
    mRoomPwdEdit->setText("");
    mRoomPwdEdit->setFontColor(RoomFontColor);
    mRoomPwdEdit->setPlaceHolder(RoomPwdEditHint.c_str());
    mRoomPwdEdit->setMaxLength(RoomEditMaxLength);
    mRoomPwdEdit->setInputMode(EditBox::InputMode::ANY);
    mRoomPwdEdit->setInputFlag(EditBox::InputFlag::PASSWORD);
    mRoomPwdEdit->setReturnType(EditBox::KeyboardReturnType::DONE);
    mRoomPwdEdit->setPosition(Vec2(pwdLabel->getPosition().x+ pwdLabel->getContentSize().width/2 + mRoomPwdEdit->getContentSize().width/2, pwdLabel->getPosition().y));
    mRoomPwdEdit->retain();
    addChild(pwdLabel);
    addChild(mRoomPwdEdit);
    
    
    mJoinMenuItem = MenuItemImage::create(RoomJoinNormalImg, RoomJoinPressedImg, CC_CALLBACK_1(RoomCreateJoin::onOkClicked, this));
    Vec2 pos = Vec2(mRoomPwdEdit->getPosition().x - mRoomPwdEdit->getContentSize().width/2 + mJoinMenuItem->getContentSize().width/2, mRoomPwdEdit->getPosition().y - mRoomPwdEdit->getContentSize().height/2 - mJoinMenuItem->getContentSize().height);
    mJoinMenuItem->setPosition(pos);
    mJoinMenuItem->retain();
    
    mCreateMenuItem = MenuItemImage::create(RoomCreateNormalImg, RoomCreatePressedImg, CC_CALLBACK_1(RoomCreateJoin::onOkClicked, this));
    mCreateMenuItem->setPosition(pos);
    mCreateMenuItem->retain();
    
    auto cancel = MenuItemImage::create(RoomCancelNormalImg, RoomCancelPressedImg, CC_CALLBACK_1(RoomCreateJoin::onCancelClicked, this));
    cancel->setPosition(Vec2(pos.x+mCreateMenuItem->getContentSize().width/2 + cancel->getContentSize().width, pos.y));

    
    auto menu = Menu::create(mJoinMenuItem, mCreateMenuItem, cancel, nullptr);
    menu->setPosition(Vec2::ZERO);
    
    addChild(menu);
    
    return true;
}