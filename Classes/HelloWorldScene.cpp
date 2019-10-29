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

Scene *HelloWorld::createScene() {
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
    // __android_log_print(ANDROID_LOG_ERROR, "problemLoading ", "Error while loading: %s\n",
    //                      filename);
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
    this->addChild(menu, 2);

//    ValueMap valueMap = ValueMapNull;
//    ValueVector valueVector = ValueVectorNull;
//    valueMap["obj"] = man;
//    valueVector.push_back(Value(valueMap));
//    obj->setObjects(valueVector);
    _tileMap = TMXTiledMap::create("qbdt.tmx");
    _tileMap->setAnchorPoint(Vec2::ZERO);
    _tileMap->setPosition3D(Vec3(0, 0, 0));
    _tileMap->setGlobalZOrder(-1);
    _tileMap->setCameraMask(2);
    this->addChild(_tileMap, 2);
    layer2 = _tileMap->getLayer("tuceng2");
    layer2->setVisible(false);

//    man = Sprite::create("lrsc8.png");
//    bg = Sprite::create("qbyuanjhh.jpg");
//    bg->setAnchorPoint(Vec2::ZERO);
//    bg->setPosition3D(Vec3(0, 0, 100));
//    bg->setGlobalZOrder(-1);
//    this->addChild(bg);
    man = Sprite3D::create("Monster Bee@Defend.c3b");
    man->setTexture("Monster Bee - Purple.png");
    man->setScale(0.3);
    man->setCameraMask(2);
    TMXObjectGroup *obj = _tileMap->getObjectGroup("obj1");
    ValueMap objMap = obj->getObject("obj");
    int x = objMap["x"].asInt();
    int y = objMap["y"].asInt();
    man->setPosition3D(Vec3(x, y, 0));
    man->setRotation3D(Vec3(0, 0, 0));
    man->setGlobalZOrder(5);
    this->addChild(man);
//    this->setViewpointCenter(man->getPosition());
    auto animation = Animation3D::create("Monster Bee@Defend.c3b");
    if (animation) {
        auto play = Animate3D::create(animation, 0.f, 1.0f);
//        play->setSpeed(0.1);
        man->runAction(RepeatForever::create(play));//循环播放
    }

//    map->getLayer("tuceng1")->addChild(man,5);
    cameraExample = Camera::createPerspective(60, (GLfloat) visibleSize.width / visibleSize.height, 1, 1000);
    cameraExample->setPosition3D(Vec3(0, 100, -100));
    cameraExample->setRotation3D(Vec3(0, 0, 0));
    cameraExample->lookAt(Vec3(0, 0, 0));
//    摄像机标识
    cameraExample->setCameraFlag(CameraFlag::USER1);
    man->addChild(cameraExample);
    schedule(schedule_selector(HelloWorld::updateTime));

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&](Touch *tTouch, Event *event) {
        beginX = (int) tTouch->getLocation().x;
        beginY = (int) tTouch->getLocation().y;
        MoveTo *moveTo = MoveTo::create(2, Vec3(beginX, beginY, 0));
        man->runAction(moveTo);
        return true;
    };
//    listener->onTouchEnded = [&](Touch *touch, Event *event) {
//
//    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}


void HelloWorld::menuCloseCallback(Ref *pSender) {
    auto director = Director::getInstance();
    director->pushScene(NewGame::createScene());
}

void HelloWorld::updateTime(float f) {
    if (cameraExample) {
        cameraExample->lookAt(Vec3(0, 0, 0), Vec3(0, 1, 0));
    }
}

//void HelloWorld::setViewPointCenter(Point position) {
//    // move Camera
//    float lastEyeX = position.x - 300;
//    Camera *camera = getCamera();
//    float eyeZ = camera->getZEye();
//    camera->setEyeXYZ(lastEyeX, 0, eyeZ);
//    camera->setCenterXYZ(lastEyeX, 0, 0);
//}

void HelloWorld::setViewpointCenter(Point position) {

    // 求出屏幕的范围包括宽和高
    Size winSize = Director::sharedDirector()->getWinSize();
    //显示屏幕中心点的坐标大于屏幕宽和高的一半
    int x = (int) MAX(position.x, winSize.width / 2);
    int y = (int) MAX(position.y, winSize.height / 2);

    //求出的是整个瓦片地图的宽
    //_tileMap->getMapSize().width瓦片地图横向有多少个瓦片
    //_tileMap->getTileSize().width每一个瓦片的宽度
    int mapWidth = (int) (_tileMap->getMapSize().width * _tileMap->getTileSize().width);


    //求出的是整个瓦片地图的高
    //_tileMap->getMapSize().height瓦片地图纵向有多少个瓦片
    //_tileMap->getTileSize().height每一个瓦片的高度

    int mapHeight = (int) (_tileMap->getMapSize().height * _tileMap->getTileSize().height);

    x = (int) MIN(x, mapWidth - winSize.width / 2);
    y = (int) MIN(y, mapHeight - winSize.height / 2);

    //目标点
    Point actualPoint = Point(x, y);

    //屏幕的中心点
    Point viewCenterPoint = Point(winSize.width / 2, winSize.height / 2);
    //计算出重置显示屏幕的中心点
    //ccpSub 返回的是viewCenterPoint.x - actualPoint.x和viewCenterPoint.y - actualPoint.y
    Point viewPoint = viewCenterPoint - actualPoint;
    //重置显示屏幕的中心点
    this->setPosition(viewPoint);

}

