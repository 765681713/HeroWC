//
// Created by Administrator on 2019/10/8.
//

#ifndef PROJ_ANDROID_GAMEONE_H
#define PROJ_ANDROID_GAMEONE_H

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class GameOne : public cocos2d::Scene {
public:
    static cocos2d::Scene *createScene();

    virtual bool init();
    void updateTime(float f);

    // implement the "static create()" method manually
    CREATE_FUNC(GameOne);
private :
    Sprite3D *man;
    float beginX;
    float beginY;
    Camera * cameraExample;
};

#endif //PROJ_ANDROID_GAMEONE_H
