//
//  headchose.h
//  dice
//
//  Created by sockyjam on 14-8-17.
//
//

#ifndef __dice__headscene__
#define __dice__headscene__

#include <iostream>
#include "DiceScene.h"

USING_NS_CC;

class HeadScene: public DiceScene {
public:
    CREATE_FUNC(HeadScene);
    virtual void onEnter() override;

protected:
    GameStatus initStatus();
};


#endif /* defined(__dice__headscene__) */
