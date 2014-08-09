//
//  InitBackgroundLayer.h
//  dice
//
//  Created by Hetty on 14-8-8.
//
//

#ifndef __dice__InitBackgroundLayer__
#define __dice__InitBackgroundLayer__

#include <iostream>
#include "CCLayer.h"

using namespace cocos2d;

class InitBackgroundLayer : public Layer {
public:
    CREATE_FUNC(InitBackgroundLayer);
    virtual bool init() override;
//    virtual void onEnter() override;
};

#endif /* defined(__dice__InitBackgroundLayer__) */
