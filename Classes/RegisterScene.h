//
//  RegisterScene.h
//  dice
//
//  Created by Hetty on 14-8-9.
//
//

#ifndef __dice__RegisterScene__
#define __dice__RegisterScene__

#include <iostream>
#include "CCScene.h"

USING_NS_CC;

class RegisterScene: public Scene {
public:
    CREATE_FUNC(RegisterScene);
    virtual void onEnter() override;
};



#endif /* defined(__dice__RegisterScene__) */
