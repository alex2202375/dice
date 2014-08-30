//
//  GameScene.h
//  dice
//
//  Created by Hetty on 14-8-9.
//
//

#ifndef __dice__GameScene__
#define __dice__GameScene__

#include <iostream>
#include "CCScene.h"
#include "DiceScene.h"
#include "Constants.h"
#include "Player.h"
#include "GameLayer.h"

USING_NS_CC;

class GameScene: public DiceScene {
public:
    CREATE_FUNC(GameScene);
    ~GameScene();
    virtual bool init() override;
    
    void enterredRoom();
    void rollDice();
    void showPunishment();
    void updatePunishSettings();
    void updatePlayerList();
    void punishFinished();
    void gameFinished();

protected:
    GameStatus initStatus();

private:
    GameScene();
    GameLayer* mGameLayer;
};

#endif /* defined(__dice__GameScene__) */
