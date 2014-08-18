//
//  NetEngine.cpp
//  dice
//
//  Created by Hetty on 14-8-10.
//
//

#include "NetEngine.h"

#include "pomelo.h"

NetEngine* NetEngine::getInstance() {
    NetEngine * en = new NetEngine();
    if (en) {
        en->init();
    }
    return en;
}

bool NetEngine::init() {
    
}
