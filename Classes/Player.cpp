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
    return create(player.name, CommonUtil::getPicture(player.picId), player.winRate);
}

PlayerSprite* PlayerSprite::create(string name, string photo, float winRate) {
    PlayerSprite *sprite = new (std::nothrow) PlayerSprite(name, photo, winRate);
    if (sprite && sprite->init())
    {
        sprite->autorelease();
        
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void PlayerSprite::placeSelf(){
    Size pSize = getTextureRect().size;
    mNameLabel->setPosition(Vec2(pSize.width/2, -5));
    
    mDice->setPosition(Vec2(pSize.width/2, pSize.height+mDice->getContentSize().height/2+PlayerLineMarginTop));
    
    mPhotoPic->setPosition(getContentSize().width/2, getContentSize().height/2);
    
//    setContentSize(Size(pSize.width, pSize.height+mNameLabel->getContentSize().height + mDice->getContentSize().height + 2*PlayerLineMarginTop));
}

bool PlayerSprite::init() {
    if (!Sprite::initWithFile(PlayerBgImg)) {
        return false;
    }
    
    mNameLabel = LabelTTF::create(mName, PlayerFontName, PlayerFontSize);
    mNameLabel->retain();
    mNameLabel->setVisible(true);
    addChild(mNameLabel);
    
    mPhotoPic = Sprite::create(mPhoto);
    mPhotoPic->retain();
    addChild(mPhotoPic);
    
    mDice = Sprite::create(CommonUtil::getDiceImage(PlayerDiceDefaultNum, true));
    mDice->retain();
    mDice->setVisible(true);
    addChild(mDice);
    
    placeSelf();
    return true;
}

PlayerSprite::PlayerSprite(string name, string photo, float winRate)
: mName(name), mPhoto(photo), mWinRate(winRate){
    
}

void PlayerSprite::showDice(bool show) {
    mDice->setVisible(show);
}

bool PlayerSprite::isDiceVisible() {
    return mDice->isVisible();
}

void PlayerSprite::setDiceNum(int num) {
    mDiceNumber = num;
    mDice->setTexture(CommonUtil::getDiceImage(num, true));
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
    mPhotoPic->setTexture(photo);
    placeSelf();
}

string PlayerSprite::getPhoto() {
    return mPhoto;
}