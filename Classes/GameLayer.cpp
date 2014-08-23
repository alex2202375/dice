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
#include "CCLabel.h"
#include "CCAnimation.h"
#include "CCAnimationCache.h"
#include "CCEventListenerTouch.h"
#include "CCEventListenerAcceleration.h"
#include "time.h"
#include "Player.h"

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
    
    mDiceRunning = false;
    
    mRoomMenu = nullptr;
    mRoomCreateJoin = nullptr;
}

GameLayer::~GameLayer() {
    for (Vector<MenuItem*>::iterator it = mPunishTypeMenuItems.begin(); it != mPunishTypeMenuItems.end(); it++) {
        (*it)->release();
    }
    mPunishTypeMenuItems.clear();
    
    for (Vector<PlayerSprite*>::iterator it = mPlayers.begin(); it != mPlayers.end(); it++) {
        (*it)->release();
    }
    mPlayers.clear();
    
    mPunishInfoMenu->release();
    mSelfInfoMenu->release();
    mPunishTypeMenu->release();
    mSelfInfoBox->release();
    mDiceCup->release();
    mRoomMenu->release();
}

void GameLayer::onEnter() {
    Layer::onEnter();
    
    showRoomSelect(true);
}

void GameLayer::onExit() {
    Layer::onExit();
    
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
        MoveTo *action = MoveTo::create(DefaultActionTime, getSelfInfoMenuHidePos());
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
        
        addChild(mSelfInfoBox, 1);
    }
    
    mSelfInfoMenuShown = true;
    MoveTo* action = MoveTo::create(DefaultActionTime, getSelfInfoMenuShowPos());
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
    PunishType type = (PunishType)(item->getTag());
    setSelectedPunishType(type);
    hidePunishInfo();

    log((string(__FUNCTION__)+"Selected type:%d").c_str(), (int)type);
    
}

void GameLayer::setDiceNumber(int num) {
    mDice->setTexture(CommonUtil::getDiceImage(num));
}

void GameLayer::showDiceAnimation() {
    
    if (!mDiceRunning)
    {
        auto animation = Animation::create();
        for( int i=1;i<=DiceRunAnimationSize;i++)
        {
            char szName[100] = {0};
            sprintf(szName, DiceRunAnimationFileNameFormat.c_str(), i);
            animation->addSpriteFrameWithFile(szName);
        }
        
        animation->setDelayPerUnit(0.3f / 6.0f);
        animation->setRestoreOriginalFrame(true);
        
        auto action = Animate::create(animation);
        mDice->runAction(RepeatForever::create(Sequence::create(action, action->reverse(), nullptr)));
        mDiceRunning = true;
    }
}

void GameLayer::hidePunishInfo()
{
    if (mPunishTypeMenu && mPunishTypeMenuShown) {
        mPunishTypeMenuShown = false;
        MoveTo *action = MoveTo::create(DefaultActionTime, getPunishTypeMenuHidePos());
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
            menuItem->setTag((int)(PunishTypeShy+i));
            
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

        addChild(punishInfoBox, 1);
    }
    
    setSelectedPunishType(selectedIndex);

    mPunishTypeMenuShown = true;
    MoveTo* action = MoveTo::create(DefaultActionTime, getPunishTypeMenuShowPos());
    mPunishTypeMenu->stopAllActions();
    mPunishTypeMenu->runAction(action);
    hideSelfInfo();
}

void GameLayer::setSelectedPunishType(PunishType type) {
    for (int i= 0; i < mPunishTypeMenuItems.size() ; i++) {
        MenuItem* item = mPunishTypeMenuItems.at(i);
        if ((PunishType)item->getTag() == type) {
            mPunishTypeMenuItems.at(i)->selected();
        }
        else {
            mPunishTypeMenuItems.at(i)->unselected();
        }
    }
    
    mSelectedPunishType = type;
}


void GameLayer::onGetDiceNum(int num) {
    stopDiceAnimation();
    setDiceNumber(num);
}

void GameLayer::stopDiceAnimation() {
    if (mDiceRunning) {
        mDice->stopAllActions();
        mDiceRunning = false;
    }
}

void GameLayer::onDiceAnimationFinish(float interval)
{
    onGetDiceNum(rand()/DiceRunAnimationSize + 1);
}

bool GameLayer::onTouch(Touch* touch, Event* event) {
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    if (target == mDiceCup) {
        if (CommonUtil::isInRect(target, touch->getLocation())) {
            if (!mRoomCreateJoin || !mRoomCreateJoin->isVisible()) {
                showRoomSelect(true);
            }
            return true;
        }
        return false;
    }
    else if (target == mDice) {
        if (CommonUtil::isInRect(target, touch->getLocation())) {
            static int i = 0;
            Player player;
            char name[20] = {0};
            sprintf(name, "玩家%d", i);
            char photo[50] = {0};
            sprintf(photo, "head/head%d.png", i%6+1);
            player.name = name;
            player.photo = photo;
            player.winRate = i*0.05;
            this->addPlayer(player);
            i++;
            return true;}
        return false;
    }
    return false;
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
    this->addChild(menu, 2);
    
    mDiceCup = Sprite::create(DiceCupImg);
    mDiceCup->setPosition(Vec2(visibleSize.width/2, (visibleSize.height-punishTypeMenuItem->getContentSize().height)/2));
    mDiceCup->retain();
    this->addChild(mDiceCup);
    
    mDice = Sprite::create(CommonUtil::getDiceImage(6));
    mDice->retain();
    mDice->setPosition(Vec2(visibleSize.width/2, (visibleSize.height-punishTypeMenuItem->getContentSize().height)/2));
    mDice->setVisible(false);
    addChild(mDice);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouch, this);
    
    listener->onTouchEnded = [&](Touch*, Event* event) {
     };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, mDiceCup);
    
    auto listener2 = EventListenerTouchOneByOne::create();
    listener2->setSwallowTouches(true);
    listener2->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouch, this);
    
    listener2->onTouchEnded = [&](Touch*, Event* event) {
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, mDice);
    
    //For Shake detect
    setAccelerometerEnabled(true);
    return true;
}

void GameLayer::onAcceleration(Acceleration* pAccelerationValue, Event* event)  {
    static Acceleration lastAcc = *pAccelerationValue;
    const double dCurTimeStamp = pAccelerationValue->timestamp;
    double dX=pAccelerationValue->x - lastAcc.x;
    double dY=pAccelerationValue->y - lastAcc.y;
    double dZ=pAccelerationValue->z - lastAcc.z;
    
    const double dLengthSq = dX*dX + dY*dY + dZ*dZ;
    
    if( dLengthSq > 0.8 ){
        struct timeval now;  // 秒，毫秒
        gettimeofday(&now, NULL);
        static long lLastTime = 0;
        if( now.tv_sec - lLastTime > 0.5 ){
            log("晃动了 %lf , len %lf" , dCurTimeStamp , dLengthSq );
            lLastTime = now.tv_sec;
            this->showDiceAnimation();
            this->schedule(schedule_selector(GameLayer::onDiceAnimationFinish), 0, 0, 4);
        }
    }
    
    lastAcc = *pAccelerationValue;
}

void GameLayer::removeAllPlayers() {
    for (size_t i = 0; i < mPlayers.size(); i++) {
        Sprite* player = mPlayers.at(i);
        player->release();
        removeChild(player);
    }
    mPlayers.clear();
}

void GameLayer::addPlayer(Player &player) {
    PlayerSprite* sprite = PlayerSprite::create(player);
    sprite->retain();
    sprite->setPosition(getPlayerInitPos());
    
    addChild(sprite);
    mPlayers.pushBack(sprite);
    
    placePlayers();
}

Vec2 GameLayer::getPlayerInitPos() {
    Vec2 cupPos = mDiceCup->getPosition();
    return Vec2(cupPos.x, cupPos.y+getPlayerRadiusToCenter());
}


float GameLayer::getPlayerRadiusToCenter() {
    static float r = -1;
    if (r == -1) {
        PlayerSprite* player = PlayerSprite::create(-1, "tmp");
        float cupLength = MAX(mDiceCup->getContentSize().height/2, mDiceCup->getContentSize().width/2);
        float playerLength = MAX(player->getContentSize().height/2, player->getContentSize().width/2);
        r = cupLength+playerLength+PlayerRadiusMargin;
    }
    
    return r;
}



void GameLayer::placePlayers() {
    size_t count = mPlayers.size();
    float degree = 2*PI / count;
    Vec2 initPos = getPlayerInitPos();

    for (int i = 0; i < mPlayers.size(); i++) {
        PlayerSprite* player = mPlayers.at(i);
        Vec2 newPos = initPos.rotateByAngle(mDiceCup->getPosition(), degree*i);
        player->runAction(MoveTo::create(PlayerPlaceDuration, newPos));
    }
}

void GameLayer::showRoomSelect(bool show)
{
    if (mRoomMenu == nullptr) {
        auto createRoom = MenuItemImage::create(RoomCreateRoomNormalImg, RoomCreateRoomPressedImg, CC_CALLBACK_1(GameLayer::onCreateRoomMenuClicked, this));
        
        Vec2 cupPos = mDiceCup->getPosition();
        Size cupSize = mDiceCup->getContentSize();
        createRoom->setPosition(Vec2(cupPos.x, cupPos.y + cupSize.height/2 + createRoom->getContentSize().height/2));
        
        auto joinRoom = MenuItemImage::create(RoomJoinRoomNormalImg, RoomJoinRoomPressedImg, CC_CALLBACK_1(GameLayer::onJoinRoomMenuClicked, this));
        joinRoom->setPosition(Vec2(cupPos.x, cupPos.y - cupSize.height/2 - joinRoom->getContentSize().height/2));
        
        mRoomMenu = Menu::create(createRoom, joinRoom, nullptr);
        mRoomMenu->setPosition(Vec2::ZERO);
        mRoomMenu->retain();
        addChild(mRoomMenu, 2);
    }
    
    if (mRoomMenu) {
        mRoomMenu->setVisible(show);
    }
}

void GameLayer::onCreateRoomMenuClicked(Ref*sender) {
    showRoomCreateOrJoin(true, true);
    showRoomSelect(false);
}

void GameLayer::onJoinRoomMenuClicked(Ref*sender) {
    showRoomCreateOrJoin(false, true);
    showRoomSelect(false);
}

void  GameLayer::onCreateRoomOKClicked(const string& roomNum, const string & roomPwd) {
    mRoomCreateJoin->setVisible(false);
    removeAllPlayers();
    mDice->setVisible(true);
}

void  GameLayer::onJoinRoomOKClicked(const string& roomNum, const string & roomPwd) {
    mRoomCreateJoin->setVisible(false);
    removeAllPlayers();
    mDice->setVisible(true);
}

void  GameLayer::onJoinRoomCancelClicked() {
    mRoomCreateJoin->setVisible(false);
}

void  GameLayer::onCreateRoomCancelClicked() {
    mRoomCreateJoin->setVisible(false);
}

void GameLayer::showRoomCreateOrJoin(bool create, bool show) {
    if (mRoomCreateJoin == nullptr) {
        mRoomCreateJoin = RoomCreateJoin::create();
        mRoomCreateJoin->setPosition(mDiceCup->getPosition());
        mRoomCreateJoin->retain();
        addChild(mRoomCreateJoin, 2);
    }
    if (create) {
        mRoomCreateJoin->setType(RoomCreateJoin::CreateOrJoin::CREATE_ROOM);
        mRoomCreateJoin->setOnOKClicked(CC_CALLBACK_2(GameLayer::onCreateRoomOKClicked, this));
        mRoomCreateJoin->setOnCancelClicked(CC_CALLBACK_0(GameLayer::onCreateRoomCancelClicked, this));
    }
    else {
        mRoomCreateJoin->setType(RoomCreateJoin::CreateOrJoin::JOIN_ROOM);
        mRoomCreateJoin->setOnOKClicked(CC_CALLBACK_2(GameLayer::onJoinRoomOKClicked, this));
        mRoomCreateJoin->setOnCancelClicked(CC_CALLBACK_0(GameLayer::onJoinRoomCancelClicked, this));
    }
    
    mRoomCreateJoin->setVisible(show);
}