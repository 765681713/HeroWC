//
// Created by Administrator on 2019/10/8.
//

#include "NewGame.h"
USING_NS_CC;

Scene *NewGame::createScene() {
    return NewGame::create();
}

bool NewGame::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr) {
    } else {
        // position the sprite on the center of the screen
        sprite->setPosition(
                Vec2(100,150));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;
}
