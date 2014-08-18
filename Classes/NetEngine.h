//
//  NetEngine.h
//  dice
//
//  Created by Hetty on 14-8-10.
//
//

#ifndef __dice__NetEngine__
#define __dice__NetEngine__

#include <iostream>

#include "CCRef.h"

USING_NS_CC;

class NetEngine : public Ref{
public:
    static NetEngine* getInstance();
    
private:
    NetEngine();
    bool init();
};

#endif /* defined(__dice__NetEngine__) */
