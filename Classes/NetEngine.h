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

class NetEngine {
public:
    static NetEngine* getInstance();
    
private:
    NetEngine();
};

#endif /* defined(__dice__NetEngine__) */
