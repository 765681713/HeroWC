//
// Created by Administrator on 2019/10/8.
//

#include "NewGame.h"
#include "GameOne.h"

Scene *NewGame::createScene() {
    return NewGame::create();
}

bool NewGame::init() {
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    sprite = Sprite::create("HelloWorld.png");
//    CCASSERT(!sprite, "view = 123456789");
    if (sprite != nullptr) {
        sprite->setAnchorPoint(Vec2(1, 0));
        sprite->setPosition(Vec2(visibleSize.width, 0) + origin);
        Rect r = sprite->getCenterRect();
        __android_log_print(ANDROID_LOG_ERROR, "r.size", "%f,%f", r.size.width, r.size.height);
        __android_log_print(ANDROID_LOG_ERROR, "r.origin", "%f,%f", r.origin.x, r.origin.y);
        this->addChild(sprite, 2);
    }
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(NewGame::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(NewGame::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(NewGame::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
    return true;
}

bool NewGame::onTouchBegan(Touch *tTouch, Event *eEvent) {
    __android_log_print(ANDROID_LOG_ERROR, NEWGAME, " tTouch.x = %f", tTouch->getLocation().x);
    __android_log_print(ANDROID_LOG_ERROR, NEWGAME, " tTouch.y = %f", tTouch->getLocation().y);
    __android_log_print(ANDROID_LOG_ERROR, NEWGAME, " sprite->getBoundingBox().size.width = %f", sprite->getBoundingBox().size.width);
    __android_log_print(ANDROID_LOG_ERROR, NEWGAME, "sprite->getBoundingBox().size.height = %f", sprite->getBoundingBox().size.height);
    if (sprite->getBoundingBox().containsPoint(tTouch->getLocation())) {//判断触摸点是否在目标的范围内
        __android_log_print(ANDROID_LOG_ERROR, "containsPoint = ", "true");
        return true;
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "containsPoint = ", "false");
        return false;
    }
}

void NewGame::onTouchMoved(Touch *tTouch, Event *eEvent) {

}

void NewGame::onTouchEnded(Touch *tTouch, Event *eEvent) {
    Director::getInstance()->replaceScene(GameOne::createScene());
}
