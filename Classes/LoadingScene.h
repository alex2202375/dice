//
//  LoadingScene.h
//  dice
//
//  Created by Hetty on 14-8-9.
//
//

#ifndef __dice__LoadingScene__
#define __dice__LoadingScene__

#include <iostream>
#include "DiceScene.h"

class LoadingScene : public DiceScene {
public:
    CREATE_FUNC(LoadingScene);
    void nextScene(float delta);
    virtual void onEnter() override;
    
protected:
  LogicalEngine::GameStatus initStatus();

private:
};

#endif /* defined(__dice__LoadingScene__) */
