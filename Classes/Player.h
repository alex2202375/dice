//
//  Player.h
//  dice
//
//  Created by Hetty on 14-8-10.
//
//

#ifndef __dice__Player__
#define __dice__Player__

#include <iostream>
#include <string>
#include "CCSprite.h"
#include "Constants.h"
#include "CCLabelTTF.h"


USING_NS_CC;
using namespace std;

class Player {
public:
    string name;
    int picId;
    float winRate;
    int diceNum;
};


class PlayerSprite : public Sprite
{
public:
    static PlayerSprite* create(Player& player);
    
    static PlayerSprite* create(string name, string photo = PlayerPhotoNull, float winRate = 0);

    void showDice(bool show);
    bool isDiceVisible();
    void setDiceNum(int num);
    int getDiceNum();
    
    void setName(string name);
    string getName();
    
    void setPhoto(string photo);
    string getPhoto();
    
protected:
    virtual bool init() override;
    
private:
    void placeSelf();
    PlayerSprite(string name, string photo, float winRate);
    
private:
    string mName;
    LabelTTF* mNameLabel;
    
    string mPhoto;
    Sprite* mPhotoPic;
    
    Sprite* mDice;
    int mDiceNumber;
    
    float mWinRate;
};

#endif /* defined(__dice__Player__) */
