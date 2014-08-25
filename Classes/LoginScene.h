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
#include "Constants.h"

class LoginScene : public DiceScene {
public:
    CREATE_FUNC(LoginScene);
    ~LoginScene();
    virtual void onEnter() override;
    
protected:
  GameStatus initStatus();

private:
  LoginScene();
};


#endif /* defined(__dice__LoginScene__) */
