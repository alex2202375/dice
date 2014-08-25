//
//  LoginScene.h
//  dice
//
//  Created by Hetty on 14-8-9.
//
//

#ifndef __dice__LoginScene__
#define __dice__LoginScene__

#include <iostream>
#include "CCScene.h"
#include "DiceScene.h"


class LoginScene : public DiceScene {
public:
    CREATE_FUNC(LoginScene);
    virtual void onEnter() override;
    
protected:
  LogicalEngine::GameStatus initStatus();

private:
};


#endif /* defined(__dice__LoginScene__) */
