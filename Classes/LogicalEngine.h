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
        //Login
        LOGINING,
        LOGIN_WAIT_RSP,
        LOGINED,
        
        //Register
        REGISTERING,
        REGISTER_WAIT_RSP,
        
        //Room create/join
        ROOM_SELECTING,
        ROOM_CREATING,
        ROOM_CREATE_WAIT_RSP,
        ROOM_CREATED,
        ROOM_JOINING,
        ROOM_JOIN_WAIT_RSP,
        ROOM_JOINED,
        
        //Game
        GAME_READY,
        GAME_START_WAIT_RSP,
        GAME_GENERATING_NUMBER,
        GAME_SENDING_NUMBER_WAIT_RSP,
        GAME_WAITING_RESULT,
        GAME_PUNISHING,
        GAME_FINISHED
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
