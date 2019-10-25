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

    mySprite = Sprite3D::create("Lich1.c3b");
    mySprite->setTexture("Lich-Cyan.png");
//    mySprite->setColor(Color3B(255,0,255));

    Texture2D *newTexture = Director::getInstance()->getTextureCache()->addImage("FIL8365.JPG");

//    auto shader = GLProgram::createWithFilenames("fog.vert", "fog.frag");
//    auto shader = GLProgram::createWithFilenames("text1.vert", "text1.frag");
    auto shader = GLProgram::createWithFilenames("text2.vert", "text2.frag");
    GLProgramState *_state = GLProgramState::create(shader);
    _state->setUniformTexture("u_Texture", newTexture);
//    _state->setUniformVec4("u_fogColor", Vec4(0.5, 0.5, 0.5, 1.0));
//    _state->setUniformFloat("u_fogStart", 10);
//    _state->setUniformFloat("u_fogEnd", 60);
//    _state->setUniformInt("u_fogEquation", 0);
//    _state->setUniformFloat("u_fogDensity", 0.03f);
    _state->applyUniforms();
    mySprite->setGLProgramState(_state);

//    int i = mySprite->getMeshCount();

//    ParticleFire *fire = ParticleFire::create();
//    fire->setScale(0.2);
//    fire->setColor(Color3B(255, 0, 0));
//    fire->setCameraMask(1);
//    fire->setPosition3D(Vec3(0, 0, 0));
//    fire->setAnchorPoint(Vec2(0, 0));
//    fire->setTexture(Director::getInstance()->getTextureCache()->addImage("fire.png"));
//    mySprite->getNode("Rig")->addChild(fire);
//    mySprite->addChild(fire);
//    __android_log_print(ANDROID_LOG_ERROR, "mySprite getAttachedNodeCount = ", "%i",
//                        mySprite->getAttachedNodeCount());
//    AttachNode *node = mySprite->getAttachNode("Rig");
//    mySprite->getMeshByIndex(1)->setTexture("Lich-Lime.png");
//    mySprite->addChild(fire);
//    __android_log_print(ANDROID_LOG_ERROR, "mySprite getMeshCount = ", "%i", i);
//    Mesh *mesh = mySprite->getMeshByIndex(1);
//    __android_log_print(ANDROID_LOG_ERROR, "Mesh getName = ", "%s",
//                        mesh->getName().c_str());
//    __android_log_print(ANDROID_LOG_ERROR, "Mesh getIndexCount = ", "%i",
//                        mesh->getIndexCount());
//    for (int j = 0; j < i; j++) {
//        Mesh *mesh = mySprite->getMeshByIndex(j);
//
//        __android_log_print(ANDROID_LOG_ERROR, "Mesh getName = ", "%s",
//                            mesh->getName().c_str());
//    }
//    AttachNode *attachNode = mySprite->getAttachNode("Rig");

    mySprite->setPosition3D(Vec3(visibleSize.width / 2, visibleSize.height / 2, 0));
    mySprite->setCameraMask(1);
    mySprite->setScale(0.5);
    this->addChild(mySprite, 3);
//    auto animation = Animation3D::create("shiliaoyuan.c3b");
//    if (animation) {
//        auto play = Animate3D::create(animation, 0.f, 1.0f);
//        mySprite->runAction(RepeatForever::create(play));//循环播放
//    }

    RotateBy *rotateBy1 = RotateBy::create(10, Vec3(360, 0, 0));
    mySprite->runAction(RepeatForever::create(rotateBy1));
    Camera *cameraExample = Camera::createPerspective(30, (GLfloat) visibleSize.width / visibleSize.height, 10, 500);
    cameraExample->setPosition3D(Vec3(-10, 10, -10));
    cameraExample->lookAt(mySprite->getPosition3D(), Vec3(0, 1, 0));
    //摄像机标识
    cameraExample->setCameraFlag(CameraFlag::USER1);
    this->addChild(cameraExample);
    sprite = Sprite::create("HelloWorld.png");
//    CCASSERT(!sprite, "view = 123456789");
    if (sprite != nullptr) {
        sprite->setAnchorPoint(Vec2(1, 0));
        sprite->setPosition(Vec2(visibleSize.width, 0) + origin);
        Rect r = sprite->getCenterRect();
        // __android_log_print(ANDROID_LOG_ERROR, "r.size", "%f,%f", r.size.width, r.size.height);
        //   __android_log_print(ANDROID_LOG_ERROR, "r.origin", "%f,%f", r.origin.x, r.origin.y);
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
    // __android_log_print(ANDROID_LOG_ERROR, NEWGAME, " tTouch.x = %f", tTouch->getLocation().x);
    //  __android_log_print(ANDROID_LOG_ERROR, NEWGAME, " tTouch.y = %f", tTouch->getLocation().y);
    //  __android_log_print(ANDROID_LOG_ERROR, NEWGAME, " sprite->getBoundingBox().size.width = %f",
    //                     sprite->getBoundingBox().size.width);
    //  __android_log_print(ANDROID_LOG_ERROR, NEWGAME, "sprite->getBoundingBox().size.height = %f",
    //                     sprite->getBoundingBox().size.height);
    if (sprite->getBoundingBox().containsPoint(tTouch->getLocation())) {//判断触摸点是否在目标的范围内
        //     __android_log_print(ANDROID_LOG_ERROR, "containsPoint = ", "true");
        return true;
    } else {
        //     __android_log_print(ANDROID_LOG_ERROR, "containsPoint = ", "false");
        return false;
    }
}

void NewGame::onTouchMoved(Touch *tTouch, Event *eEvent) {

}

void NewGame::onTouchEnded(Touch *tTouch, Event *eEvent) {
    Director::getInstance()->replaceScene(GameOne::createScene());
}
