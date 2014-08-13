//
//  GameBackgroundLayer.h
//  dice
//
//  Created by Hetty on 14-8-11.
//
//

#ifndef __dice__GameBackgroundLayer__
#define __dice__GameBackgroundLayer__

#include <iostream>

#include "CCLayer.h"

USING_NS_CC;

class GameBackgroundLayer : public Layer {
public:
    CREATE_FUNC(GameBackgroundLayer);
    virtual bool init() override;
};

#endif /* defined(__dice__GameBackgroundLayer__) */
