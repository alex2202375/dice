/*
 * SceneCreater.h
 *
 *  Created on: Aug 25, 2014
 *      Author: root
 */

#ifndef SCENECREATER_H_
#define SCENECREATER_H_

#include "DiceScene.h"

class SceneCreater
{
public:
  enum SceneType{
    SCENE_LOAD,
    SCENE_LOGIN,
    SCENE_REGISTER,
    SCENE_GAME
  };
  static SceneCreater* getInstance();
  virtual ~SceneCreater();

  DiceScene* getScene(SceneType type);

  string sceneName(SceneType type);

private:
  static SceneCreater* sInstance;
  SceneCreater();
};

#endif /* SCENECREATER_H_ */
