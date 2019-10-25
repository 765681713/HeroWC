//
// Created by Administrator on 2019/10/8.
//

#include "GameOne.h"

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

    // __android_log_print(ANDROID_LOG_ERROR, "ANDROID_LOG_ERROR ", " visibleSize = %f ,%f", visibleSize.width, visibleSize.height);
    // __android_log_print(ANDROID_LOG_ERROR, "ANDROID_LOG_ERROR ", " origin = %f ,%f", origin.x, origin.y);



//    Camera *cameraExample = Camera::createPerspective(30, (GLfloat) visibleSize.width / visibleSize.height, 10, 200);
//    cameraExample->setPosition3D(Vec3(-100, 100, -50));
//    cameraExample->lookAt(Vec3(-100, 0, -50), Vec3(0, 1, 0));
//    //摄像机标识
//    cameraExample->setCameraFlag(CameraFlag::USER1);
//    this->addChild(cameraExample);
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
    man->setTexture("Dark/Dark Treant-Purple.psd");
    man->setPosition3D(Vec3(visibleSize.width / 2, visibleSize.height / 2, 0));
    man->setScale(0.5);
    this->addChild(man, 3);

    cameraExample = Camera::createPerspective(60, (GLfloat) visibleSize.width / visibleSize.height, 1, 500);
    cameraExample->setPosition3D(Vec3(0, 20, -20));
    cameraExample->lookAt(man->getPosition3D());
    //摄像机标识
    cameraExample->setCameraFlag(CameraFlag::USER1);
    man->addChild(cameraExample);
    schedule(schedule_selector(GameOne::updateTime));

    DirectionLight *light = DirectionLight::create(Vec3(-1, -1, 0), Color3B(255, 255, 255));
    light->setCameraMask(2);
    light->setEnabled(true);
    this->addChild(light);
    //-1受所有光照 0不受任何光照
    man->setLightMask(-1);
//    auto animation1 = Animation3D::create("Dark/Dark Treant@HeadAttack.c3b");
//    auto play1 = Animate3D::create(animation1, 0.f, 2.0f);
//    man->runAction(RepeatForever::create(play1));
//    man->setCameraMask(2);

    auto i = man->getAttachedNodeCount();
//    Sprite3D *manTop = Sprite3D::create("Dark/Dark Treant Seed.c3b");
//    manTop->setTexture("Dark/Dark Treant Seed-Blue.png");
//    manTop->setScale(3);
    ParticleFire *fire = ParticleFire::create();
//    fire->setTexture(Director::getInstance()->getTextureCache()->addImage("Dark/FX-Aura.png"));
    fire->setAnchorPoint(Vec2(0.5, 0));
    fire->setScale(0.4);
    man->getAttachNode("RigHead")->addChild(fire);
    auto mCount = man->getMeshCount();
    if (mCount > 0) {
        Mesh *ms = man->getMeshByIndex(0);
        std::string name = ms->getName();
        //      __android_log_print(ANDROID_LOG_ERROR, "ANDROID_LOG_ERROR ", " ms->getName() = %s", name.c_str());
    }
    //   __android_log_print(ANDROID_LOG_ERROR, "ANDROID_LOG_ERROR ", " getAttachedNodeCount = %i", i);
    //  __android_log_print(ANDROID_LOG_ERROR, "ANDROID_LOG_ERROR ", " getMeshCount = %i", mCount);
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
//        if (man->getBoundingBox().containsPoint(tTouch->getLocation())) {//判断触摸点是否在目标的范围内
//            __android_log_print(ANDROID_LOG_ERROR, "containsPoint = ", "true");
//
//            return true;
//        } else {
//            __android_log_print(ANDROID_LOG_ERROR, "containsPoint = ", "false");
//            return false;
//        }
        beginX = tTouch->getLocation().x;
        beginY = tTouch->getLocation().y;
        return true;
    };
    listener->onTouchMoved = [&](Touch *tTouch, Event *event) {
        float moveX = tTouch->getLocation().x - beginX;
        float moveY = tTouch->getLocation().y - beginY;
        RotateBy *to;
        if (moveX > moveY) {
            float rotate = 360 / 200 * moveX;
            float time = 2 * rotate / 360;
            to = RotateBy::create(time, Vec3(0, rotate, 0));
            //         __android_log_print(ANDROID_LOG_ERROR, "ANDROID_LOG_ERROR ", " rotate = %f", rotate);
        } else {
            float rotate = 360 / 200 * moveY;
            float time = 2 * rotate / 360;
            to = RotateBy::create(time, Vec3(0, 0, rotate));
            //         __android_log_print(ANDROID_LOG_ERROR, "ANDROID_LOG_ERROR ", " rotate = %f", rotate);
        }
        man->runAction(to);
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void GameOne::updateTime(float f) {
    if (cameraExample) {
        cameraExample->setPosition3D(Vec3(0, 20, -20));
        cameraExample->lookAt(man->getPosition3D(), Vec3(0, 1, 0));
    }
}