/*
 * DiceScene.cpp
 *
 *  Created on: Aug 25, 2014
 *      Author: root
 */

#include "DiceScene.h"
#include "LogicalEngine.h"

DiceScene::DiceScene()
{
}

DiceScene::~DiceScene()
{
}

bool DiceScene::init() {
  if (!Scene::init()) {
      return false;
  }

  LogicalEngine* engine = LogicalEngine::getInstance();
  engine->setStatus(initStatus());

  return true;
}

void DiceScene::setStatus(GameStatus status)
{
  LogicalEngine* engine = LogicalEngine::getInstance();
  engine->setStatus(status);
}

void DiceScene::showNotifyDialog(const string& content, int closeDelay)
{

}
