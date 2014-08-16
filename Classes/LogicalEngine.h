//
//  LogicalEngine.h
//  dice
//
//  Created by Hetty on 14-8-10.
//
//

#ifndef __dice__LogicalEngine__
#define __dice__LogicalEngine__

#include <iostream>
#include <list>
#include "CCRef.h"

using namespace std;
USING_NS_CC;

class LogicalEngine {
public:
    static LogicalEngine * getInstance();
    
    enum GameStatus {
        LOGIN,
        REGISTER,
        ST
    };
    
    // Logical Functions
    void login(string name, string password, bool rememberInfo);
    
    void getAuthKey(string phone);
    
    void registerUser(string name, string password, string phone, string authKey);
    
    typedef std::function<void(Ref *, list<int>)> roomListCB;
    void getRoomList(roomListCB callBack);
    
    void createRoom();
    
    // Switch Functions
private:
    LogicalEngine();
    
};

#endif /* defined(__dice__LogicalEngine__) */
