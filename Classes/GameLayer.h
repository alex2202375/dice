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

#include "CCLayer.h"
#include "CCNode.h"
#include "CCMenuItem.h"
#include "CCSprite.h"
#include <string>

USING_NS_CC;
using namespace std;


class GameLayer : public Layer {
public:
    
    enum PunishType {
        PunishTypeShy = 1,
        PunishTypeBold = 2,
        PunishTypeTrueWords = 3,
        PunishTypeRisky = 4
    };
    
    CREATE_FUNC(GameLayer);
    virtual ~GameLayer();
    virtual bool init() override;
    
    void onSelfInfoClicked(Ref* sender);
    void onPunishInfoClicked(Ref* sender);
    void onPunishTypeSelected(Ref* sender);
    
    void hidePunishInfo();
    void showPunishInfo(PunishType selectedIndex);
    void setSelectedPunishType(PunishType type);
    
    void showSelfInfo(string & name, string& photo, float winRate);
    void hideSelfInfo();

private:
    GameLayer();
    Vec2 getPunishTypeMenuShowPos();
    Vec2 getPunishTypeMenuHidePos();
    Vec2 getSelfInfoMenuShowPos();
    Vec2 getSelfInfoMenuHidePos();
    
private:
    Node* mSelfInfoMenu;
    Node* mPunishInfoMenu;
    Node* mSelfInfoBox;
    Node* mPunishTypeMenu;
    bool mPunishTypeMenuShown;
    bool mSelfInfoMenuShown;
    Vector<MenuItem *> mPunishTypeMenuItems;
    PunishType mSelectedPunishType;
    
    string mPlayerName;
    string mPlayerPic;
    float mPlayerWinRate;
 };


#endif /* defined(__dice__GameLayer__) */
