//
//  GameLayer.h
//  dice
//
//  Created by Hetty on 14-8-11.
//
//

#ifndef __dice__GameLayer__
#define __dice__GameLayer__

#include <iostream>

#include "CCLayer.h"

USING_NS_CC;

class GameLayer : public Layer {
public:
    CREATE_FUNC(GameLayer);
    virtual bool init() override;
    
    void onSelfInfoClicked(Ref* sender);
    void onPunishInfoClicked(Ref* sender);
};


#endif /* defined(__dice__GameLayer__) */
