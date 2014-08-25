/*
 * DiceScene.h
 *
 *  Created on: Aug 25, 2014
 *      Author: Alex Liu
 */

#ifndef DICESCENE_H_
#define DICESCENE_H_

#include "cocos2d.h"
#include "CCScene.h"
#include "LogicalEngine.h"

using namespace std;
USING_NS_CC;

class DiceScene : public Scene
{
public:
  virtual ~DiceScene();
  virtual bool init();

  void setStatus(LogicalEngine::GameStatus status);

  /**
   * Show a notify dialog with content.
   * @para content The content shows to user
   * @para closeDelay The auto close delay. if -1, show a OK button, and do not auto close
   */
  void showNotifyDialog(const string& content, int closeDelay = 3);

  CREATE_FUNC(DiceScene);
protected:
  LogicalEngine::GameStatus initStatus() = 0;

private:
  DiceScene();
};

#endif /* DICESCENE_H_ */
