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

USING_NS_CC;

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

private:
    GameLayer();
    Vec2 getPunishTypeMenuShowPos();
    Vec2 getPunishTypeMenuHidePos();
    
private:
    Node* mSelfInfoMenu;
    Node* mPunishInfoMenu;
    Node* mSelfInfoBox;
    Node* mPunishTypeMenu;
    bool mPunishTypeMenuShown;
    Vector<MenuItem *> mPunishTypeMenuItems;
    PunishType mSelectedPunishType;
 };


#endif /* defined(__dice__GameLayer__) */
