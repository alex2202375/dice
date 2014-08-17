//
//  HeadLayer.h
//  dice
//
//  Created by sockyjam on 14-8-17.
//
//

#ifndef __dice__HeadLayer__
#define __dice__HeadLayer__


#include <iostream>
#include "CCLayer.h"
#include "cocos-ext.h"
#include "deprecated/CCDeprecated.h"
using namespace cocos2d;
USING_NS_CC_EXT;

class HeadLayer: public Layer{
public:
    CREATE_FUNC(HeadLayer);
    virtual bool init() override;
    virtual void onEnter() override;
    
    void onPicClicked(Ref* caller);
    void onBackClicked(Ref * caller);
    
    int PicCount;
};


#endif /* defined(__dice__HeadLayer__) */
