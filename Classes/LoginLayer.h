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

using namespace cocos2d;

class LoginLayer: public Layer {
public:
    CREATE_FUNC(LoginLayer);
    virtual bool init() override;
    virtual void onEnter() override;
    
    void onLoginClicked(Ref* caller);
    void onRegisterClicked(Ref * caller);
};

#endif /* defined(__dice__LoginLayer__) */
