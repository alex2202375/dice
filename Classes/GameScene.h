//
//  GameScene.h
//  dice
//
//  Created by Hetty on 14-8-9.
//
//

#ifndef __dice__GameScene__
#define __dice__GameScene__

#include <iostream>
#include "CCScene.h"
#include "DiceScene.h"

USING_NS_CC;

class GameScene: public DiceScene {
public:
    CREATE_FUNC(GameScene);
    
    virtual bool init() override;

protected:
  LogicalEngine::GameStatus initStatus();
};

#endif /* defined(__dice__GameScene__) */
