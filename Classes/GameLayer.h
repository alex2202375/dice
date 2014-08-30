//
//  GameLayer.h
//  dice
//
//  Created by Hetty on 14-8-11.
//
//

#ifndef __dice__GameLayer__
#define __dice__GameLayer__

#include <iostream>
#include <string>

#include "CCLayer.h"
#include "CCNode.h"
#include "CCMenuItem.h"
#include "CCSprite.h"
#include "CCMenu.h"

#include "Constants.h"
#include "Player.h"
#include "Room.h"


USING_NS_CC;
using namespace std;


class GameLayer : public Layer {
public:
    
    CREATE_FUNC(GameLayer);
    virtual ~GameLayer();
    virtual bool init() override;
    
    void enterredRoom();
    void showPunishment();
    void updatePunishSettings();
    void updatePlayerList();
    void showStart(bool show);
    void rollDice();
    void punishFinished();
    void gameFinished();
    
    void onSelfInfoClicked(Ref* sender);
    void onPunishInfoClicked(Ref* sender);
    void onPunishTypeSelected(Ref* sender);
    
    void onPunishCatClicked(Ref* sender);
    void onPunishCatSelected(Ref* sender);
    
    void hidePunishInfo();
    void showPunishInfo(PunishType selectedIndex);
    void setSelectedPunishType(PunishType type);

    void hidePunishCat();
    void showPunishCat(PunishCat selectedIndex);
    void setSelectedPunishCat(PunishCat type);

    
    void showSelfInfo(string & name, string& photo, float winRate);
    void hideSelfInfo();
    
    void setDiceNumber(int num);
    void onGetDiceNum(int num);
    void onDiceAnimationFinish(float interval);
    
    virtual void onEnter() override;
    virtual void onExit() override;

protected:
    virtual void onAcceleration(Acceleration* acc, Event* unused_event) override;
    
private:
    GameLayer();
    Vec2 getPunishTypeMenuShowPos();
    Vec2 getPunishTypeMenuHidePos();
    Vec2 getPunishCatMenuShowPos();
    Vec2 getPunishCatMenuHidePos();
    Vec2 getSelfInfoMenuShowPos();
    Vec2 getSelfInfoMenuHidePos();
    void showDiceAnimation();
    void shakeHandler(Acceleration* pAccelerationValue, Event*);
    void stopDiceAnimation();
    void placePlayers();
    float getPlayerRadiusToCenter();
    Vec2 getPlayerInitPos();
    void removeAllPlayers();
    void addPlayer(Player &player);
    void showRoomSelect(bool show);
    void onCreateRoomMenuClicked(Ref *sender);
    void onJoinRoomMenuClicked(Ref *sender);
    void showRoomCreateOrJoin(bool create, bool show);
    
    void onCreateRoomOKClicked(const string& roomNum, const string & roomPwd);
    void onJoinRoomOKClicked(const string& roomNum, const string & roomPwd);
    void onJoinRoomCancelClicked();
    void onCreateRoomCancelClicked();
    bool onTouch(Touch* touch, Event* event);
    
    void onStartClicked(Ref* sender);
    void onPunishFinishedClicked(Ref* sender);
    
    void showShakePhone(bool show);
    void finishRollDice(Ref* sender);
    void generateNumber();
    
    void showLeave(bool show);
    void onLeaveClicked(Ref* sender);
    
private:
    Node* mSelfInfoMenu;
    Node* mSelfInfoBox;
    bool mSelfInfoMenuShown;
    
    Node* mPunishCatMenu;
    Node* mPunishCatBox;
    
    Node* mPunishTypeBox;
    Node* mPunishTypeMenu;

    
    //Punish type
    bool mPunishTypeMenuShown;
    Vector<MenuItem *> mPunishTypeMenuItems;
    PunishType mSelectedPunishType;
    
    //Punish category
    bool mPunishCatMenuShown;
    Vector<MenuItem *> mPunishCatMenuItems;
    PunishCat mSelectedPunishCat;
    
    string mPlayerName;
    string mPlayerPic;
    float mPlayerWinRate;
    
    Sprite* mDice;
    bool mDiceRunning;
    
    Sprite* mDiceCup;
    
    Vector<PlayerSprite*> mPlayers;
    
    Menu* mRoomMenu;
    RoomCreateJoin* mRoomCreateJoin;
    
    Menu* mStart;
    Menu* mLeave;
    
    Sprite* mShakePhone;
    
    Sprite* mPunishment;
    Label* mPunishStr;
    Menu* mPunishFinished;
 };


#endif /* defined(__dice__GameLayer__) */
