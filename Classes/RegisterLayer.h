//
//  RegisterLayer.h
//  dice
//
//  Created by sockyjam on 14-8-16.
//
//

#ifndef __dice__RegisterLayer__
#define __dice__RegisterLayer__

#include <iostream>
#include "CCLayer.h"
#include "cocos-ext.h"
#include "deprecated/CCDeprecated.h"
using namespace cocos2d;
USING_NS_CC_EXT;

class RegisterLayer: public Layer{
public:
    CREATE_FUNC(RegisterLayer);
    virtual ~RegisterLayer();
    virtual bool init() override;
    virtual void onEnter() override;
    
    void onHeadPicClicked(Ref* caller);
    void onRegButtonClicked(Ref * caller);
    
private:
    void savePlayerInfo();
private:
    EditBox * mUserNameEdit;
    EditBox * mUserPwdEdit;
    EditBox * mUserPwd2Edit;
    EditBox * mUserPhoneEdit;
    EditBox * mUserAuthCodeEdit;
};


#endif /* defined(__dice__RegisterLayer__) */
