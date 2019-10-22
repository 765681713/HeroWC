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

    image->setAnchorPoint(Vec2(0, 1));
    image->runAction(ScaleTo::create(1, 3));
    Menu *menu = Menu::create(image, nullptr);
    menu->setPosition(Vec2(0, visibleSize.height));

    __android_log_print(ANDROID_LOG_ERROR, "ANDROID_LOG_ERROR ", " visibleSize = %f ,%f", visibleSize.width, visibleSize.height);
    __android_log_print(ANDROID_LOG_ERROR, "ANDROID_LOG_ERROR ", " origin = %f ,%f", origin.x, origin.y);

    this->addChild(menu, 2);
//    Sprite3D *man = Sprite3D::create("dao.c3b");
//    man->setTexture("cike.png");
//    man->setAnchorPoint(Vec2(0.5, 1));
//    man->setPosition(visibleSize / 2);
//    man->setScale(2);
//    this->addChild(man, 3);
//    RotateBy *rotateBy1 = RotateBy::create(10, Vec3(360, 0, 0));
//    RotateBy *rotateBy2 = RotateBy::create(10, Vec3(0, 360, 0));
//    RotateBy *rotateBy3 = RotateBy::create(10, Vec3(0, 0, 360));
//    auto squence = Sequence::create(rotateBy1, rotateBy2, rotateBy3, NULL);
//    man->runAction(squence);
//    auto animation = Animation3D::create("dao.c3b");
//    auto play = Animate3D::create(animation, 0.f, 1.0f);
//    man->runAction(RepeatForever::create(play));//循环播放

    man = Sprite3D::create("Dark/Dark Treant@HeadAttack.c3b");
    man->setTexture("Dark/Dark Treant-Purple.png");
    man->setPosition(visibleSize / 2);
    man->setScale(0.5);
    this->addChild(man, 3);
    auto animation1 = Animation3D::create("Dark/Dark Treant@HeadAttack.c3b");
    auto play1 = Animate3D::create(animation1, 0.f, 2.0f);
    man->runAction(RepeatForever::create(play1));

    auto i = man->getAttachedNodeCount();
//    Sprite3D *manTop = Sprite3D::create("Dark/Dark Treant Seed.c3b");
//    manTop->setTexture("Dark/Dark Treant Seed-Blue.png");
//    manTop->setScale(3);
    ParticleFire *fire = ParticleFire::create();
//    fire->setTexture(Director::getInstance()->getTextureCache()->addImage("Dark/FX-Aura.png"));
    fire->setAnchorPoint(Vec2(0.5, 0));
    fire->setScale(0.4);
    man->getAttachNode("RigHead")->addChild(fire);
    __android_log_print(ANDROID_LOG_ERROR, "ANDROID_LOG_ERROR ", " getAttachedNodeCount = %i", i);
//    manTop->setTexture("Dark/Dark Treant Seed-Blue.png");
//    manTop->setPosition(Vec2(50, visibleSize.height / 2));
//    manTop->setScale(2);
//    this->addChild(manTop, 3);
//    auto animation = Animation3D::create("Dark/Dark Treant Seed.c3b");
//    auto play = Animate3D::create(animation, 0.f, 10.0f);
//    manTop->runAction(RepeatForever::create(play));
//    RotateBy *rotateBy1 = RotateBy::create(10, Vec3(360, 0, 0));
//    RotateBy *rotateBy2 = RotateBy::create(10, Vec3(0, 360, 0));
//    RotateBy *rotateBy3 = RotateBy::create(10, Vec3(0, 0, 360));
//    auto squence = Sequence::create(rotateBy1, rotateBy2, rotateBy3, NULL);
//    man->runAction(squence);
//    auto animation = Animation3D::create("dao.c3b");
//    auto play = Animate3D::create(animation, 0.f, 1.0f);
//    man->runAction(RepeatForever::create(play));//循环播放

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&](Touch *tTouch, Event *event) {
        if (man->getBoundingBox().containsPoint(tTouch->getLocation())) {//判断触摸点是否在目标的范围内
            __android_log_print(ANDROID_LOG_ERROR, "containsPoint = ", "true");
            beginX = tTouch->getLocation().x;
            beginY = tTouch->getLocation().y;
            return true;
        } else {
            __android_log_print(ANDROID_LOG_ERROR, "containsPoint = ", "false");
            return false;
        }
    };
    listener->onTouchMoved = [&](Touch *tTouch, Event *event) {
        float moveX = tTouch->getLocation().x - beginX;
        float moveY = tTouch->getLocation().y - beginY;
        RotateTo *to;
        if (moveX > moveY) {
            float rotate = 360 / 200 * moveX;
            float time = 2 * rotate / 360;
            to = RotateTo::create(time, Vec3(rotate, 0, 0));

        } else {
            float rotate = 360 / 200 * moveY;
            float time = 2 * rotate / 360;
            to = RotateTo::create(time, Vec3(0, rotate, 0));
        }
        man->runAction(to);
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}


void HelloWorld::menuCloseCallback(Ref *pSender) {
    auto director = Director::getInstance();
    director->pushScene(NewGame::createScene());
}
