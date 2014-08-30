/*
 * DiceScene.h
 *
 *  Created on: Aug 25, 2014
 *      Author: Alex Liu
 */

#ifndef __DICESCENE_H_
#define __DICESCENE_H_

#include <vector>
#include "cocos2d.h"
#include "CCScene.h"
#include "CCLabel.h"
#include "Constants.h"
#include "CCEventCustom.h"
#include "SceneCreater.h"

using namespace std;
USING_NS_CC;


class DiceScene : public Scene
{
public:
    virtual ~DiceScene();
    virtual bool init();
    virtual void update(float delta);
    void setStatus(GameStatus status);
    
    /**
     * Show a notify dialog with content.
     * @para content The content shows to user
     * @para closeDelay The auto close delay. if -1, show a OK button, and do not auto close
     */
    void showNotifyDialog(const string& content, int closeDelay = NotifyDefaultCloseDelay);
    void hideNotifyDialog(float delta);
    
    void callInMainThread(SEL_CallFunc cb);
    void switchTo(SceneCreater::SceneType type);
    
protected:
    virtual GameStatus initStatus() = 0 ;
    DiceScene();
    void switchToHandler(EventCustom* event);
    void callCbTimeout(float delta);
    void _showNotifyDialog();
    void _swithTo();
    
private:
    Node* mNotifyDialog;
    Label* mNotifyLabel;
    vector<SEL_CallFunc> mCallBackList;
    string mNotifyMessage;
    int mNotifyCloseDelay;
    SceneCreater::SceneType mNextScene;
};

#endif /* _DICESCENE_H_ */
