//
//  Room.h
//  dice
//
//  Created by Hetty on 14-8-10.
//
//

#ifndef __dice__Room__
#define __dice__Room__

#include <iostream>

#include "CCSprite.h"
#include "GUI/CCEditBox/CCEditBox.h"
#include "CCMenuItem.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;
typedef std::function<void(const string& roomNum, const string & roomPwd)> onOKClickedHandler;
typedef std::function<void(void)> onCancelClickedHandler;

class RoomCreateJoin : public Sprite {
public:
    enum CreateOrJoin {
        CREATE_ROOM,
        JOIN_ROOM
    };
    
    virtual ~RoomCreateJoin();
    
    CREATE_FUNC(RoomCreateJoin);

    void setType(CreateOrJoin type);
    CreateOrJoin getType();
    
    void setOnOKClicked(const onOKClickedHandler& handler);
    void setOnCancelClicked(const onCancelClickedHandler& handler);
    
    
    
protected:
    virtual bool init() override;
    
private:
    RoomCreateJoin();
    void onOkClicked(Ref* sender);
    void onCancelClicked(Ref* sender);
    
private:
    CreateOrJoin mType;
    onOKClickedHandler mOkHandler;
    onCancelClickedHandler mCancelHandler;
    EditBox* mRoomNumEdit;
    EditBox* mRoomPwdEdit;
    
    MenuItem* mCreateMenuItem;
    MenuItem* mJoinMenuItem;
};

#endif /* defined(__dice__Room__) */
