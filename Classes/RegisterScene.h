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
#include "DiceScene.h"

USING_NS_CC;

class RegisterScene: public DiceScene {
public:
    CREATE_FUNC(RegisterScene);
    virtual void onEnter() override;

protected:
  LogicalEngine::GameStatus initStatus();

};



#endif /* defined(__dice__RegisterScene__) */
