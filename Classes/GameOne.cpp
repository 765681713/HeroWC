//
// Created by Administrator on 2019/10/8.
//

#include "GameOne.h"

USING_NS_CC;

Scene *GameOne::createScene() {
    return GameOne::create();
}

bool GameOne::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    return true;
}