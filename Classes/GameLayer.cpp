//
//  GameLayer.cpp
//  dice
//
//  Created by Hetty on 14-8-11.
//
//

#include <string>
#include "GameLayer.h"

#include "CCDirector.h"
#include "CCMenuItem.h"
#include "CCSprite.h"
#include "CCMenu.h"
#include "CCActionInterval.h"

#include "CommonUtil.h"
#include "Constants.h"
#include "CCLabelTTF.h"

using namespace std;

GameLayer::GameLayer()
{
    mSelectedPunishType = PunishTypeShy;
    mSelfInfoMenu= nullptr;
    mPunishInfoMenu= nullptr;
    mSelfInfoBox= nullptr;
    mPunishTypeMenu= nullptr;
    mPunishTypeMenuShown = false;
    mSelfInfoMenuShown = false;
    
    mPlayerName = "Hello World";
    mPlayerPic = "";
    mPlayerWinRate = 0;
}

GameLayer::~GameLayer() {
    for (Vector<MenuItem*>::iterator it; it != mPunishTypeMenuItems.end(); it++) {
        (*it)->release();
    }
    
    mPunishInfoMenu->release();
    mSelfInfoMenu->release();
    mPunishTypeMenu->release();
    mSelfInfoBox->release();
}

void GameLayer::onSelfInfoClicked(Ref* sender){
    log(__FUNCTION__);
    //Show self info
    if (mSelfInfoBox != nullptr && mSelfInfoMenuShown) {
        hideSelfInfo();
    }
    else {
        showSelfInfo(mPlayerName, mPlayerPic, mPlayerWinRate);
    }
}

void GameLayer::hideSelfInfo()
{
    if (mSelfInfoBox && mSelfInfoMenuShown) {
        mSelfInfoMenuShown = false;
        MoveTo *action = MoveTo::create(0.5, getSelfInfoMenuHidePos());
        mSelfInfoBox->stopAllActions();
        mSelfInfoBox->runAction(action);
    }
}

void GameLayer::showSelfInfo(string & name, string& photo, float winRate)
{
    if (mSelfInfoBox == nullptr) {
        auto selfInfoBox = Sprite::create("infoBackground.png");
        Size boxSize = selfInfoBox->getContentSize();
        selfInfoBox->setPosition(getSelfInfoMenuHidePos());
        
        Size punishInfoSize = selfInfoBox->getContentSize();
        Vec2 punishInfoPos = selfInfoBox->getPosition();
        
        mSelfInfoBox = selfInfoBox;
        
        auto picBox = Sprite::create(SelfPixBoxImg);
        picBox->setPosition(Vec2(picBox->getContentSize().width/2 +10, boxSize.height- picBox->getContentSize().height/2 - 10));
        
        
        char wr[30] = {0};
        sprintf(wr, "%.2f%%", winRate);
        auto winRateLabel = LabelTTF::create(SelfInfoWinRate+wr, SelfInfoFontName, SelfInfoFontSize);
        winRateLabel->setPosition(Vec2(SelfInfoLineMarginLeft+winRateLabel->getContentSize().width/2, SelfInfoLineHeight*0.5));
        winRateLabel->setColor(SelfInfoFontColor);
        
        auto nameLabel = LabelTTF::create(SelfInfoName+name, SelfInfoFontName, SelfInfoFontSize);
        nameLabel->setColor(SelfInfoFontColor);
        nameLabel->setPosition(Vec2(SelfInfoLineMarginLeft+nameLabel->getContentSize().width/2, SelfInfoLineHeight*(1+0.5)));
        
        mSelfInfoBox->addChild(picBox);
        mSelfInfoBox->addChild(winRateLabel);
        mSelfInfoBox->addChild(nameLabel);
        mSelfInfoBox->retain();
        
        addChild(mSelfInfoBox);
    }
    
    mSelfInfoMenuShown = true;
    MoveTo* action = MoveTo::create(0.5, getSelfInfoMenuShowPos());
    mSelfInfoBox->stopAllActions();
    mSelfInfoBox->runAction(action);
    hidePunishInfo();
}

void GameLayer::onPunishInfoClicked(Ref* sender) {
    log(__FUNCTION__);
    //Show punish info
    if (mPunishTypeMenu != nullptr && mPunishTypeMenuShown) {
        hidePunishInfo();
    }
    else {
        showPunishInfo(mSelectedPunishType);
    }
}

void GameLayer::onPunishTypeSelected(Ref* sender) {
    Node * item = (Node*)sender;
    PunishType type = (PunishType)(int)(item->getUserData());
    setSelectedPunishType(type);
    hidePunishInfo();

    log((string(__FUNCTION__)+"Selected type:%d").c_str(), (int)type);
    
}

void GameLayer::hidePunishInfo()
{
    if (mPunishTypeMenu && mPunishTypeMenuShown) {
        mPunishTypeMenuShown = false;
        MoveTo *action = MoveTo::create(0.5, getPunishTypeMenuHidePos());
        mPunishTypeMenu->stopAllActions();
        mPunishTypeMenu->runAction(action);
    }
}

Vec2 GameLayer::getSelfInfoMenuShowPos()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto boxSize = Sprite::create("infoBackground.png")->getContentSize();
    return Vec2(boxSize.width/2, visibleSize.height-mSelfInfoMenu->getContentSize().height-boxSize.height/2);
}

Vec2 GameLayer::getSelfInfoMenuHidePos()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto boxSize = Sprite::create("infoBackground.png")->getContentSize();
    return Vec2(boxSize.width/2, visibleSize.height-mSelfInfoMenu->getContentSize().height+boxSize.height/2+3);
}

Vec2 GameLayer::getPunishTypeMenuShowPos()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto boxSize = Sprite::create("infoBackground.png")->getContentSize();
    return Vec2(visibleSize.width-boxSize.width/2, visibleSize.height-mPunishInfoMenu->getContentSize().height-boxSize.height/2);
}

Vec2 GameLayer::getPunishTypeMenuHidePos()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto boxSize = Sprite::create("infoBackground.png")->getContentSize();
    return Vec2(visibleSize.width-boxSize.width/2, visibleSize.height-mPunishInfoMenu->getContentSize().height+boxSize.height/2+3);
}

void GameLayer::showPunishInfo(PunishType selectedIndex) {
    if (mPunishTypeMenu == nullptr) {
        mPunishTypeMenuItems.clear();
        auto punishInfoBox = Sprite::create("infoBackground.png");
        Size boxSize = punishInfoBox->getContentSize();
//        punishInfoBox->setPosition(Vec2(visibleSize.width-boxSize.width/2, visibleSize.height-mPunishInfoMenu->getContentSize().height-boxSize.height/2));
        punishInfoBox->setPosition(getPunishTypeMenuHidePos());
        
        Size punishInfoSize = punishInfoBox->getContentSize();
        Vec2 punishInfoPos = punishInfoBox->getPosition();
        
        const string typeList[] = {PunishTypeShyStr, PunishTypeBoldStr, PunishTypeTrueWordsStr, PunishTypeRiskyStr};
        
        for (int i = 0; i < sizeof(typeList)/sizeof(string); i++) {
            
            auto selectedSprite = Sprite::create(PunishTypeSelectedImg);
            auto selectedTop = LabelTTF::create(typeList[i], PunishTypeFontName, PunishTypeFontSize);
            selectedTop->setColor(PunishTypeFontColor);
            selectedTop->setPosition(Vec2(selectedTop->getContentSize().width/2+PunishTypeLineMarginLeft, selectedSprite->getContentSize().height/2));
            selectedSprite->addChild(selectedTop);
            
            auto normalSprite = Sprite::create(PunishTypeNormalImg);
            auto normalTop = LabelTTF::create(typeList[i], PunishTypeFontName, PunishTypeFontSize);
            normalTop->setColor(PunishTypeFontColor);
            normalTop->setPosition(Vec2(normalTop->getContentSize().width/2+PunishTypeLineMarginLeft, normalSprite->getContentSize().height/2));
            normalSprite->addChild(normalTop);
            
            auto menuItem = MenuItemSprite::create(normalSprite, selectedSprite, CC_CALLBACK_1(GameLayer::onPunishTypeSelected, this));
            menuItem->setUserData((void*)(int)(PunishTypeShy+i));
            
            Vec2 pos(selectedSprite->getContentSize().width/2, selectedSprite->getContentSize().height*(i+0.5));
            menuItem->setPosition(pos);
            menuItem->retain();
            mPunishTypeMenuItems.pushBack(menuItem);
        }
        
        auto punishTypeMenu = Menu::createWithArray(mPunishTypeMenuItems);
        mPunishTypeMenu = punishInfoBox;
        punishTypeMenu->setPosition(Vec2::ZERO);
        mPunishTypeMenu->addChild(punishTypeMenu);
        mPunishTypeMenu->retain();

        addChild(punishInfoBox);

//        addChild(punishTypeMenu);
    }
    
    setSelectedPunishType(selectedIndex);

    mPunishTypeMenuShown = true;
    MoveTo* action = MoveTo::create(0.5, getPunishTypeMenuShowPos());
    mPunishTypeMenu->stopAllActions();
    mPunishTypeMenu->runAction(action);
    hideSelfInfo();
}

void GameLayer::setSelectedPunishType(PunishType type) {
    for (int i= 0; i < mPunishTypeMenuItems.size() ; i++) {
        MenuItem* item = mPunishTypeMenuItems.at(i);
        if ((PunishType)(int)item->getUserData() == type) {
            mPunishTypeMenuItems.at(i)->selected();
        }
        else {
            mPunishTypeMenuItems.at(i)->unselected();
        }
    }
    
    mSelectedPunishType = type;
}

bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto selfInfoMenuItem = MenuItemImage::create("selfInfo.png", "selfInfo.png", CC_CALLBACK_1(GameLayer::onSelfInfoClicked, this));
    
    Size selfInfoSize = selfInfoMenuItem->getContentSize();
    selfInfoMenuItem->setPosition(Vec2(selfInfoSize.width/2, visibleSize.height-selfInfoSize.height/2));
    
    auto punishTypeMenuItem = MenuItemImage::create("punishType.png", "punishType.png", CC_CALLBACK_1(GameLayer::onPunishInfoClicked, this));
    punishTypeMenuItem->setPosition(Vec2(visibleSize.width-selfInfoSize.width/2, visibleSize.height-selfInfoSize.height/2));
    
    selfInfoMenuItem->retain();
    mSelfInfoMenu = selfInfoMenuItem;
    
    punishTypeMenuItem->retain();
    mPunishInfoMenu = punishTypeMenuItem;
    
    auto menu = Menu::create(selfInfoMenuItem, punishTypeMenuItem, nullptr);
    
    menu->setPosition(Vec2::ZERO);
    
    // add the sprite as a child to this layer
    this->addChild(menu, 1);
    
    Sprite *diceCup = Sprite::create("diceCup.png");
    diceCup->setPosition(Vec2(visibleSize.width/2, (visibleSize.height-punishTypeMenuItem->getContentSize().height)/2));
    this->addChild(diceCup);
    
    return true;
}