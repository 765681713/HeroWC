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

    LabelAtlas *diceCount = LabelAtlas::create("1500", "n_15.png", 18, 24, ',');
    diceCount->setAnchorPoint(Vec2::ZERO);
    diceCount->setPosition(100, 150);
    this->addChild(diceCount, 2);

    return true;
}