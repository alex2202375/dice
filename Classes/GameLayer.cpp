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
#include "LogicalEngine.h"

using namespace std;

GameLayer::GameLayer()
{
    mSelectedPunishCat = PunishCatSmall;
    mPunishCatMenuShown = false;
    mPunishCatMenu = nullptr;
    mPunishCatBox = nullptr;
    
    mSelfInfoMenu= nullptr;
    mSelfInfoBox= nullptr;
    mSelfInfoMenuShown = false;
    
    mSelectedPunishType = PunishTypeShy;
    mPunishTypeMenu= nullptr;
    mPunishTypeBox= nullptr;
    mPunishTypeMenuShown = false;
    
    mPlayerName = "Hello World";
    mPlayerPic = "";
    mPlayerWinRate = 0;
    
    mDiceRunning = false;
    
    mRoomMenu = nullptr;
    mRoomCreateJoin = nullptr;
    
    mStart = nullptr;
    mShakePhone = nullptr;
    
    mPunishment= nullptr;
    mPunishFinished = nullptr;
}

GameLayer::~GameLayer() {
    for (Vector<PlayerSprite*>::iterator it = mPlayers.begin(); it != mPlayers.end(); it++) {
        (*it)->release();
    }
    mPlayers.clear();

    CommonUtil::releaseRef(mSelfInfoMenu);
    CommonUtil::releaseRef(mSelfInfoBox);
    
    //Punish category
    for (Vector<MenuItem*>::iterator it = mPunishCatMenuItems.begin(); it != mPunishCatMenuItems.end(); it++) {
        (*it)->release();
    }
    mPunishCatMenuItems.clear();
    CommonUtil::releaseRef(mPunishCatMenu);
    CommonUtil::releaseRef(mPunishCatBox);
    
    //Punish type
    for (Vector<MenuItem*>::iterator it = mPunishTypeMenuItems.begin(); it != mPunishTypeMenuItems.end(); it++) {
        (*it)->release();
    }
    mPunishTypeMenuItems.clear();
    CommonUtil::releaseRef(mPunishTypeMenu);
    CommonUtil::releaseRef(mPunishTypeBox);
    CommonUtil::releaseRef(mDiceCup);
    CommonUtil::releaseRef(mRoomMenu);
    CommonUtil::releaseRef(mStart);
    CommonUtil::releaseRef(mShakePhone);
    CommonUtil::releaseRef(mPunishment);
    CommonUtil::releaseRef(mPunishFinished);
}

void GameLayer::onEnter() {
    Layer::onEnter();
    
    showRoomSelect(true);
}

void GameLayer::onExit() {
    Layer::onExit();
    
}

void GameLayer::onPunishCatClicked(Ref* sender){
    log(__FUNCTION__);
    //Show cat info
    if (mPunishCatBox != nullptr && mPunishCatMenuShown) {
        hidePunishCat();
    }
    else {
        showPunishCat(mSelectedPunishCat);
    }
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
    if (mPunishTypeBox != nullptr && mPunishTypeMenuShown) {
        hidePunishInfo();
    }
    else {
        showPunishInfo(mSelectedPunishType);
    }
}

void GameLayer::onPunishTypeSelected(Ref* sender) {
    
    if (LogicalEngine::getInstance()->isRoomOwner()) {
        Node * item = (Node*)sender;
        PunishType type = (PunishType)(item->getTag());
        setSelectedPunishType(type);
        hidePunishInfo();
        
        LogicalEngine::getInstance()->setPunishSetting(mSelectedPunishCat, mSelectedPunishType);
        log((string(__FUNCTION__)+"Selected type:%d").c_str(), (int)type);
    }
}

void GameLayer::onPunishCatSelected(Ref* sender) {
    if (LogicalEngine::getInstance()->isRoomOwner()) {
        Node * item = (Node*)sender;
        PunishCat type = (PunishCat)(item->getTag());
        setSelectedPunishCat(type);
        hidePunishCat();
        
        LogicalEngine::getInstance()->setPunishSetting(mSelectedPunishCat, mSelectedPunishType);
        log((string(__FUNCTION__)+"Selected type:%d").c_str(), (int)type);
    }
}

void GameLayer::setDiceNumber(int num) {
    mDice->setTexture(CommonUtil::getDiceImage(num));
}

void GameLayer::showDiceAnimation() {
    
    if (!mDiceRunning)
    {
        mDice->setVisible(true);
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
    if (mPunishTypeBox && mPunishTypeMenuShown) {
        mPunishTypeMenuShown = false;
        MoveTo *action = MoveTo::create(DefaultActionTime, getPunishTypeMenuHidePos());
        mPunishTypeBox->stopAllActions();
        mPunishTypeBox->runAction(action);
    }
}

void GameLayer::hidePunishCat()
{
    if (mPunishCatBox && mPunishCatMenuShown) {
        mPunishCatMenuShown = false;
        MoveTo *action = MoveTo::create(DefaultActionTime, getPunishCatMenuHidePos());
        mPunishCatBox->stopAllActions();
        mPunishCatBox->runAction(action);
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
    auto boxSize = Sprite::create(PunishTypeBgImg)->getContentSize();
    return Vec2(visibleSize.width-boxSize.width/2, visibleSize.height-mPunishTypeMenu->getContentSize().height-boxSize.height/2);
}

Vec2 GameLayer::getPunishTypeMenuHidePos()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto boxSize = Sprite::create(PunishTypeBgImg)->getContentSize();
    return Vec2(visibleSize.width-boxSize.width/2, visibleSize.height-mPunishTypeMenu->getContentSize().height+boxSize.height/2+3);
}

void GameLayer::showPunishInfo(PunishType selectedIndex) {
    if (mPunishTypeBox == nullptr) {
        mPunishTypeMenuItems.clear();
        auto punishInfoBox = Sprite::create(PunishTypeBgImg);
        Size boxSize = punishInfoBox->getContentSize();
        punishInfoBox->setPosition(getPunishTypeMenuHidePos());
        
        Size punishInfoSize = punishInfoBox->getContentSize();
        Vec2 punishInfoPos = punishInfoBox->getPosition();
        
        const string typeList[] = {PunishTypeBuyStr, PunishTypeNoLimitedStr, PunishTypeBoldStr, PunishTypeShyStr, PunishTypeNaiveStr};
        
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
            menuItem->setTag((int)(PunishTypeBuy+i));
            
            Vec2 pos(selectedSprite->getContentSize().width/2, selectedSprite->getContentSize().height*(i+0.5));
            menuItem->setPosition(pos);
            menuItem->retain();
            mPunishTypeMenuItems.pushBack(menuItem);
        }
        
        auto punishTypeMenu = Menu::createWithArray(mPunishTypeMenuItems);
        mPunishTypeBox = punishInfoBox;
        punishTypeMenu->setPosition(Vec2::ZERO);
        mPunishTypeBox->addChild(punishTypeMenu);
        mPunishTypeBox->retain();

        addChild(punishInfoBox, 1);
    }
    
    setSelectedPunishType(selectedIndex);

    mPunishTypeMenuShown = true;
    MoveTo* action = MoveTo::create(DefaultActionTime, getPunishTypeMenuShowPos());
    mPunishTypeBox->stopAllActions();
    mPunishTypeBox->runAction(action);
    hidePunishCat();
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


Vec2 GameLayer::getPunishCatMenuShowPos()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto boxSize = Sprite::create(PunishCatBgImg)->getContentSize();
    return Vec2(boxSize.width/2, visibleSize.height-mPunishCatMenu->getContentSize().height-boxSize.height/2);
}

Vec2 GameLayer::getPunishCatMenuHidePos()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto boxSize = Sprite::create(PunishCatBgImg)->getContentSize();
    return Vec2(boxSize.width/2, visibleSize.height-mPunishCatMenu->getContentSize().height+boxSize.height/2+3);
}

void GameLayer::showPunishCat(PunishCat selectedIndex) {
    if (mPunishCatBox == nullptr) {
        mPunishCatMenuItems.clear();
        auto punishCatBox = Sprite::create(PunishCatBgImg);
        Size boxSize = punishCatBox->getContentSize();
        punishCatBox->setPosition(getPunishCatMenuHidePos());
        
        Size punishCatSize = punishCatBox->getContentSize();
        Vec2 punishCatPos = punishCatBox->getPosition();
        
        const string typeList[] = {PunishCatSmallStr, PunishCatBigStr, PunishCatSameMostStr,
        PunishCatSameLeastStr};
        
        for (int i = 0; i < sizeof(typeList)/sizeof(string); i++) {
            
            auto selectedSprite = Sprite::create(PunishCatSelectedImg);
            auto selectedTop = LabelTTF::create(typeList[i], PunishCatFontName, PunishCatFontSize);
            selectedTop->setColor(PunishCatFontColor);
            selectedTop->setPosition(Vec2(selectedTop->getContentSize().width/2+PunishCatLineMarginLeft, selectedSprite->getContentSize().height/2));
            selectedSprite->addChild(selectedTop);
            
            auto normalSprite = Sprite::create(PunishCatNormalImg);
            auto normalTop = LabelTTF::create(typeList[i], PunishCatFontName, PunishCatFontSize);
            normalTop->setColor(PunishCatFontColor);
            normalTop->setPosition(Vec2(normalTop->getContentSize().width/2+PunishCatLineMarginLeft, normalSprite->getContentSize().height/2));
            normalSprite->addChild(normalTop);
            
            auto menuItem = MenuItemSprite::create(normalSprite, selectedSprite, CC_CALLBACK_1(GameLayer::onPunishCatSelected, this));
            menuItem->setTag((int)(PunishCatSmall+i));
            
            Vec2 pos(selectedSprite->getContentSize().width/2, selectedSprite->getContentSize().height*(i+0.5));
            menuItem->setPosition(pos);
            menuItem->retain();
            mPunishCatMenuItems.pushBack(menuItem);
        }
        
        auto punishCatMenu = Menu::createWithArray(mPunishCatMenuItems);
        mPunishCatBox = punishCatBox;
        punishCatMenu->setPosition(Vec2::ZERO);
        mPunishCatBox->addChild(punishCatMenu);
        mPunishCatBox->retain();
        
        addChild(punishCatBox, 1);
    }
    
    setSelectedPunishCat(selectedIndex);
    
    mPunishCatMenuShown = true;
    MoveTo* action = MoveTo::create(DefaultActionTime, getPunishCatMenuShowPos());
    mPunishCatBox->stopAllActions();
    mPunishCatBox->runAction(action);
    hidePunishInfo();
}

void GameLayer::setSelectedPunishCat(PunishCat type) {
    for (int i= 0; i < mPunishCatMenuItems.size() ; i++) {
        MenuItem* item = mPunishCatMenuItems.at(i);
        if ((PunishCat)item->getTag() == type) {
            mPunishCatMenuItems.at(i)->selected();
        }
        else {
            mPunishCatMenuItems.at(i)->unselected();
        }
    }
    
    mSelectedPunishCat = type;
}

void GameLayer::onGetDiceNum(int num) {
    stopDiceAnimation();
    setDiceNumber(num);
    LogicalEngine::getInstance()->sendDiceNum(num);
}

void GameLayer::stopDiceAnimation() {
    if (mDiceRunning) {
        mDice->stopAllActions();
        mDiceRunning = false;
    }
}

void GameLayer::onDiceAnimationFinish(float interval)
{
    onGetDiceNum(rand()%DiceRunAnimationSize + 1);
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
            player.name = name;
            player.picId = i%6+1;
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
    
    //Punish Category
    auto punishCatMenuItem = MenuItemImage::create(PunishCatImg, PunishCatImg, CC_CALLBACK_1(GameLayer::onPunishCatClicked, this));
    Size punishCatSize = punishCatMenuItem->getContentSize();
    punishCatMenuItem->setPosition(Vec2(punishCatSize.width/2, visibleSize.height-punishCatSize.height/2));
    punishCatMenuItem->retain();
    mPunishCatMenu = punishCatMenuItem;
    
    
    //Punish Type
    auto punishTypeMenuItem = MenuItemImage::create(PunishTypeImg, PunishTypeImg, CC_CALLBACK_1(GameLayer::onPunishInfoClicked, this));
    Size punishTypeSize = punishTypeMenuItem->getContentSize();
    punishTypeMenuItem->setPosition(Vec2(visibleSize.width-punishTypeSize.width/2, visibleSize.height-punishTypeSize.height/2));
    punishTypeMenuItem->retain();
    mPunishTypeMenu = punishTypeMenuItem;
    
    auto menu = Menu::create(punishCatMenuItem, punishTypeMenuItem, nullptr);
    
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
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, mDiceCup);
    
    auto listener2 = EventListenerTouchOneByOne::create();
    listener2->setSwallowTouches(true);
    listener2->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouch, this);
    
    listener2->onTouchEnded = [&](Touch*, Event* event) {
    };
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, mDice);
    
    //For Shake detect
    setAccelerometerEnabled(true);
    return true;
}

void GameLayer::onAcceleration(Acceleration* pAccelerationValue, Event* event)  {
    static Acceleration lastAcc = *pAccelerationValue;
    
    if (mShakePhone && mShakePhone->isVisible()) {
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
                this->showShakePhone(false);
                generateNumber();
            }
        }
        
        lastAcc = *pAccelerationValue;
    }
}

void GameLayer::removeAllPlayers() {
    for (int i = mPlayers.size()-1; i >= 0; i--) {
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
        PlayerSprite* player = PlayerSprite::create("tmp");
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
    LogicalEngine::getInstance()->createRoom(atoi(roomNum.c_str()), roomPwd);
    removeAllPlayers();

}

void  GameLayer::onJoinRoomOKClicked(const string& roomNum, const string & roomPwd) {
    mRoomCreateJoin->setVisible(false);
    removeAllPlayers();
    LogicalEngine::getInstance()->joinRoom(atoi(roomNum.c_str()), roomPwd);
}

void  GameLayer::onJoinRoomCancelClicked() {
    mRoomCreateJoin->setVisible(false);
    mRoomMenu->setVisible(true);
}

void  GameLayer::onCreateRoomCancelClicked() {
    mRoomCreateJoin->setVisible(false);
    mRoomMenu->setVisible(true);
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

void GameLayer::enterredRoom() {
    //Hide room create
    showRoomCreateOrJoin(true, false);
    showStart(LogicalEngine::getInstance()->isRoomOwner());
    updatePlayerList();
}

void GameLayer::showStart(bool show) {
    if (!mStart) {
        auto menuItem = MenuItemImage::create(GameStartImg, GameStartImg, CC_CALLBACK_1(GameLayer::onStartClicked, this));
        Size visibleSize = Director::getInstance()->getVisibleSize();

        menuItem->setPosition(Vec2(visibleSize.width/2, menuItem->getContentSize().height));
        
        mStart = Menu::create(menuItem, nullptr);
        mStart->setPosition(Vec2::ZERO);
        mStart->retain();
        addChild(mStart, 2);
    }
    
    mStart->setVisible(show);
}

void GameLayer::onStartClicked(Ref* sender) {
    LogicalEngine::getInstance()->startGame();
}

void GameLayer::onPunishFinishedClicked(Ref* sender) {
    LogicalEngine::getInstance()->punishFinished();
}


void GameLayer::showPunishment() {
    string name, punishment;
    LogicalEngine* engine = LogicalEngine::getInstance();
    engine->getPunishInfo(name, punishment);
    if (!mPunishment) {
        mPunishment = Sprite::create(PunishmentIcon);
        mPunishment->retain();
        mPunishStr = Label::create(punishment, PunishmentFontName, PunishmentFontSize);
        mPunishStr->setPosition(Vec2(mPunishment->getContentSize().width/2, PunishmentLabelY));
        mPunishment->addChild(mPunishStr);
        mPunishment->setPosition(mDiceCup->getPosition());
        addChild(mPunishment, 2);
        
        auto menuItem = MenuItemImage::create(GameStartImg, GameStartImg, CC_CALLBACK_1(GameLayer::onPunishFinishedClicked, this));
        Size visibleSize = Director::getInstance()->getVisibleSize();
        menuItem->setPosition(Vec2(visibleSize.width/2, menuItem->getContentSize().height));
        mPunishFinished = Menu::create(menuItem, nullptr);
        mPunishFinished->setPosition(Vec2::ZERO);
        mPunishFinished->retain();
        addChild(mPunishFinished, 2);
        mPunishFinished->setVisible(false);
    }
    
    mPunishStr->setString(punishment);
    mPunishment->setVisible(true);
    if (engine->isRoomOwner()) {
        mPunishFinished->setVisible(true);
    }
}

void GameLayer::punishFinished() {
    DiceScene* scene = CommonUtil::getParentScene(this);
    scene->showNotifyDialog(PunishmentFinishedStr);
    if (mPunishment) {
        mPunishment->setVisible(false);
    }
}

void GameLayer::updatePunishSettings() {
    LogicalEngine::getInstance()->getPunishSetting(mSelectedPunishCat, mSelectedPunishType);
}

void GameLayer::updatePlayerList() {
    vector<Player> playerList;
    LogicalEngine::getInstance()->getPlayerList(playerList);
    
    //Update exist and remove none exists
    for (int i = mPlayers.size() - 1; i >= 0 ; i--) {
        bool found = false;
        for (int j = 0; j < playerList.size(); j++) {
            if (mPlayers.at(i)->getName() == playerList.at(j).name) {
                mPlayers.at(i)->setDiceNum(playerList.at(j).diceNum);
                found = true;
                break;
            }
        }
        if (!found) {
            Sprite* player = mPlayers.at(i);
            player->release();
            removeChild(player);
            mPlayers.erase(i);
        }
    }
    
    //Add new
    for (int i = 0; i < playerList.size(); i++) {
        bool found = false;
        for (int j = 0 ; j < mPlayers.size(); j++) {
            if (playerList.at(i).name == mPlayers.at(j)->getName()) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            addPlayer(playerList.at(i));
        }
    }
}

void GameLayer::showShakePhone(bool show) {
    if (!mShakePhone) {
        mShakePhone = Sprite::create(GameShakePhoneImg);
        mShakePhone->setPosition(mDiceCup->getPosition());
        mShakePhone->retain();
        addChild(mShakePhone, 2);
    }
    
    mShakePhone->stopAllActions();
    if (show) {
        auto action = MoveBy::create(GameShakePhoneActionDuration, Vec2(GameShakePhoneActionDeltaX, 0));
        
        auto action2 = MoveBy::create(GameShakePhoneActionDuration, Vec2(-GameShakePhoneActionDeltaX, 0));
        auto oneShake = Sequence::create(action, action->reverse(), action2, action2->reverse(), NULL);
        auto wholeShake = Repeat::create(oneShake, GameShakePhoneFinishDuration/(4*GameShakePhoneActionDuration));
        auto wholeAction = Sequence::create(wholeShake, CallFuncN::create(CC_CALLBACK_1(GameLayer::finishRollDice, this)), NULL);
        mShakePhone->runAction(wholeAction);
    }
    
    mShakePhone->setVisible(show);
}
                         
void GameLayer::finishRollDice(Ref* sender) {
    showShakePhone(false);
    generateNumber();
}

void GameLayer::rollDice() {
    showStart(false);
    showShakePhone(true);
}

void GameLayer::generateNumber() {
    showDiceAnimation();
    schedule(schedule_selector(GameLayer::onDiceAnimationFinish), 0, 0, 4);
}

void GameLayer::gameFinished() {
    DiceScene* scene = CommonUtil::getParentScene(this);
    scene->showNotifyDialog(GameFinished);
    mRoomMenu->setVisible(false);
    mRoomCreateJoin->setVisible(false);
    mStart->setVisible(false);
    mPunishFinished->setVisible(false);
    mDice->setVisible(false);
    mPunishment->setVisible(false);
    if (LogicalEngine::getInstance()->isRoomOwner()) {
        mStart->setVisible(true);
    }
//    removeAllPlayers();
}