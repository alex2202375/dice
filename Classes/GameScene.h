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

USING_NS_CC;

class GameScene: public Scene {
public:
    CREATE_FUNC(GameScene);
    
    virtual bool init() override;
};

#endif /* defined(__dice__GameScene__) */
