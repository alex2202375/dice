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
#include "Constants.h"

class LoadingScene : public DiceScene {
public:
    CREATE_FUNC(LoadingScene);

    ~LoadingScene();
    void nextScene(float delta);
    virtual void onEnter() override;
    
protected:
  GameStatus initStatus();

private:
  LoadingScene();
};

#endif /* defined(__dice__LoadingScene__) */
