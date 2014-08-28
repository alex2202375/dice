//
//  LoginLayer.h
//  dice
//
//  Created by Alex Liu on 14-8-8.
//
//

#ifndef __dice__LoginLayer__
#define __dice__LoginLayer__

#include <iostream>
#include "CCLayer.h"
#include "cocos-ext.h"
#include "deprecated/CCDeprecated.h"
#include <UITextField.h>
#include "GUI/CCEditBox/CCEditBox.h"


using namespace cocos2d::extension;
USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;
USING_NS_CC_EXT;

class LoginLayer: public Layer{
public:
    CREATE_FUNC(LoginLayer);
    virtual bool init() override;
    virtual void onEnter() override;
    
    void onLoginClicked(Ref* caller);
    void onRegisterClicked(Ref * caller);

    virtual ~LoginLayer();
private:
    EditBox* mNameEdit;
    EditBox* mPasswordEdit;
};

#endif /* defined(__dice__LoginLayer__) */
