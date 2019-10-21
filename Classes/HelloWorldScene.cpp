/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "NewGame.h"
#include <android/log.h>

USING_NS_CC;

Scene *HelloWorld::createScene() {
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
    __android_log_print(ANDROID_LOG_ERROR, "problemLoading ", "Error while loading: %s\n", filename);
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    const std::string nor = "CloseNormal.png";
    const std::string cls = "CloseSelected.png";
    MenuItemImage *image = MenuItemImage::create(nor, cls, CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    image->setAnchorPoint(Vec2::ZERO);
    image->runAction(ScaleTo::create(1, 3));
    Menu *menu = Menu::create(image, nullptr);
    menu->setPosition(visibleSize / 2);

    __android_log_print(ANDROID_LOG_ERROR, "ANDROID_LOG_ERROR ", " visibleSize = %f ,%f", visibleSize.width, visibleSize.height);
    __android_log_print(ANDROID_LOG_ERROR, "ANDROID_LOG_ERROR ", " origin = %f ,%f", origin.x, origin.y);

    this->addChild(menu, 2);

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr) {
        problemLoading("'fonts/Marker Felt.ttf'");
    } else {
        label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr) {
        problemLoading("'HelloWorld.png'");
    } else {
        sprite->setAnchorPoint(Vec2::ZERO);
        sprite->setPosition(Vec2(0, 0) + origin);
        this->addChild(sprite, 2);
    }
    return true;
}


void HelloWorld::menuCloseCallback(Ref *pSender) {
    auto director = Director::getInstance();
    director->pushScene(NewGame::createScene());
}
