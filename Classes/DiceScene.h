/*
 * DiceScene.h
 *
 *  Created on: Aug 25, 2014
 *      Author: Alex Liu
 */

#ifndef __DICESCENE_H_
#define __DICESCENE_H_

#include "cocos2d.h"
#include "CCScene.h"
#include "CCLabel.h"
#include "Constants.h"

using namespace std;
USING_NS_CC;

class DiceScene : public Scene
{
public:
  virtual ~DiceScene();
  virtual bool init();

  void setStatus(GameStatus status);

  /**
   * Show a notify dialog with content.
   * @para content The content shows to user
   * @para closeDelay The auto close delay. if -1, show a OK button, and do not auto close
   */
  void showNotifyDialog(const string& content, int closeDelay = NotifyDefaultCloseDelay);
  void hideNotifyDialog(float delta);

protected:
  virtual GameStatus initStatus() = 0 ;
  DiceScene();

private:
  Node* mNotifyDialog;
  Label* mNotifyLabel;
};

#endif /* _DICESCENE_H_ */
