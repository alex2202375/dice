//
//  Player.cpp
//  dice
//
//  Created by Hetty on 14-8-10.
//
//

#include "Player.h"
#include "CCLabelTTF.h"
#include "CommonUtil.h"

PlayerSprite* PlayerSprite::create(Player& player) {
    return create(player.id, player.name, player.photo, player.winRate);
}

PlayerSprite* PlayerSprite::create(int id, string name, string photo, float winRate) {
    PlayerSprite *sprite = new (std::nothrow) PlayerSprite(id, name, photo, winRate);
    if (sprite && sprite->init())
    {
        sprite->autorelease();
        
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void PlayerSprite::setId(int id) {
    mId = id;
}

int PlayerSprite::getId() {
    return mId;
}

void PlayerSprite::placeSelf(){
    Size pSize = getTextureRect().size;
    mNameLabel->setPosition(Vec2(pSize.width/2, -mNameLabel->getContentSize().height/2-PlayerLineMarginTop));
    
    mDice->setPosition(Vec2(pSize.width/2, pSize.height+mDice->getContentSize().height/2+PlayerLineMarginTop));
    
    mPhotoPic->setPosition(Vec2(mPhotoPic->getContentSize().width/2, mPhotoPic->getContentSize().height/2));
    
//    setContentSize(Size(pSize.width, pSize.height+mNameLabel->getContentSize().height + mDice->getContentSize().height + 2*PlayerLineMarginTop));
}

bool PlayerSprite::init() {
    if (!Sprite::initWithFile(PlayerBgImg)) {
        return false;
    }
    
    mNameLabel = LabelTTF::create(mName, PlayerFontName, PlayerFontSize);
    mNameLabel->retain();
    mNameLabel->setVisible(false);
    addChild(mNameLabel);
    
    mPhotoPic = Sprite::create(mPhoto);
    mPhotoPic->retain();
    addChild(mPhotoPic);
    
    mDice = Sprite::create(CommonUtil::getDiceImage(PlayerDiceDefaultNum));
    mDice->retain();
    mDice->setVisible(false);
    addChild(mDice);
    
    placeSelf();
    return true;
}

PlayerSprite::PlayerSprite(int id, string name, string photo, float winRate)
: mId(id), mName(name), mPhoto(photo), mWinRate(winRate){
    
}

void PlayerSprite::showDice(bool show) {
    mDice->setVisible(show);
}

bool PlayerSprite::isDiceVisible() {
    return mDice->isVisible();
}

void PlayerSprite::setDiceNum(int num) {
    mDiceNumber = num;
    mDice->setTexture(CommonUtil::getDiceImage(num));
    placeSelf();
}

int PlayerSprite::getDiceNum() {
    return mDiceNumber;
}

void PlayerSprite::setName(string name) {
    mNameLabel->setString(name);
    placeSelf();
}

string PlayerSprite::getName() {
    return mName;
}

void PlayerSprite::setPhoto(string photo) {
    setTexture(photo);
    placeSelf();
}

string PlayerSprite::getPhoto() {
    return mPhoto;
}